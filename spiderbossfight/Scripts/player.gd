extends CharacterBody3D


const SPEED = 5.0
const JUMP_VELOCITY = 4.5
const MOUSE_SENSITIVITY = 0.2

@export var projectile : PackedScene = preload("res://Scenes/playerProjectile.tscn")
@onready var camera = $Camera3D
@onready var HPlabel = $HP
@onready var ammolabel = $Ammo
@onready var velocityLabel = $Velocity

var yaw = 0  # Horizontal rotation (left-right)
var pitch = 0  # Vertical rotation (up-down)

#Player variables
var playerHP = 0
var HPmax = 20
var curAmmo = 20
var maxAmmo = 20
var playerDMG = 10

var shortReloadCooldown = 0.5
var longReloadCooldown = 0.75
var cooldown = 1
var curcooldown = 0

var currentSpeed
var speedModifier


func _ready() -> void:
	updateHealth(HPmax)
	currentSpeed = SPEED
	set_speed_mod(5.0)
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED

func _input(event):
	# Handle mouse movement for looking around
	if event is InputEventMouseMotion && Input.mouse_mode == Input.MOUSE_MODE_CAPTURED:
		yaw -= event.relative.x * MOUSE_SENSITIVITY
		pitch -= event.relative.y * MOUSE_SENSITIVITY
		pitch = clamp(pitch, -90, 90)  # Prevents looking too far up/down
		
		# Apply rotations
		rotation_degrees.y = yaw  # Rotate character left/right
		camera.rotation_degrees.x = pitch  # Rotate camera up/down

func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity += get_gravity() * delta

	# Handle jump.
	if Input.is_action_just_pressed("Space") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	
	if Input.is_action_just_pressed("Esc"):
		Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
	
	if Input.is_action_just_pressed("Lclick") && Input.mouse_mode == Input.MOUSE_MODE_VISIBLE:
		Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
	
	if Input.is_action_just_pressed("Lclick") && Input.mouse_mode == Input.MOUSE_MODE_CAPTURED:
		shoot()

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var input_dir := Input.get_vector("Left", "Right", "Up", "Down")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)
	
	updateVellabel(velocity)
	updateCooldown(delta)
	move_and_slide()
	

#cooldown methods
func startCooldown():
	curcooldown = cooldown

func updateCooldown(delta: float):
	if curcooldown > 0:
		curcooldown -= delta
	else:
		curcooldown = 0

#Health based methods
func die():
	queue_free()

func updateHealth(deltaHP: float) -> void:
	if playerHP + deltaHP <= 0:
		playerHP = 0
		die()
	elif playerHP + deltaHP > HPmax:
		playerHP = HPmax
	else:
		playerHP += deltaHP
	updateHPlabel()

func take_damage(DMG: float):
	updateHealth(-DMG)

#Label methods
func updateHPlabel():
	HPlabel.text = str("Health: ", playerHP)

func updateAmmolabel():
	ammolabel.text = str("Ammo: ", curAmmo)

func updateVellabel(velocity: Vector3):
	velocityLabel.text = str("Velocity: ", velocity)

#Get + Set methods
func set_speed_mod(modifier: float):
	speedModifier = modifier

func get_speed_mod() -> float:
	return speedModifier

#Combat Methods
func shoot():
	if curAmmo <= 0:
		reloadWeapon()
	elif canShoot():
		if projectile:
			var proj = projectile.instantiate()
			#Need to decouple player position and fireball position
			proj.set_damage(playerDMG)
			proj.set_playerRef(self)
			#Need to pair players facing direction to direction of attack
			get_tree().current_scene.add_sibling(proj)
			
			var muzzle_offset = camera.global_transform.basis.z.normalized() * -1  # forward
			proj.global_position = camera.global_transform.origin + muzzle_offset * 1.5
			
			var direction = camera.global_transform.basis.z.normalized() * -1
			if proj.has_method("set_velocity"):
				proj.set_velocity(direction * 20)
				curAmmo -= 1
				startCooldown()
	
	updateAmmolabel()

func reloadWeapon():
	curAmmo = maxAmmo

#Boolean methods
func canShoot():
	return curcooldown == 0
