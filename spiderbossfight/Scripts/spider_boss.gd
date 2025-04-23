extends Node3D

# Audio Manager
var audio_manager : AudioManager

# signals
signal spider_death

var game_active : bool

@export var is_player_controlled := true
@export var is_player_position_known := true
@export var spiderProjectile : PackedScene = preload("res://Scenes/spider_projectile.tscn")

var target
var _startFlag := false

var enemy_damage_m = 20.0
var enemy_damage_r = 10.0

var curShootCooldown = 0.0
var shootCooldown = 1.0

@export var playerTargetRef : CharacterBody3D

@export var move_speed: float = 5.0

@export var rotation_speed: float = TAU * 2
var _theta : float
var _direction : Vector3
var facingTarget : bool = false


@export var groundOffset: float = 1.0
@onready var groundDetector = $GroundDetector
@onready var projOriginPoint = $projectileOrigin

@onready var FrontL_Trgt = $FrontL_IK_Trgt
@onready var FrontR_Trgt = $FrontR_IK_Trgt
@onready var BackR_Trgt = $BackR_IK_Trgt
@onready var BackL_Trgt = $BackL_IK_Trgt

var timeAcc = 0.0
var timeCooldown = 5.0

func _ready() -> void:
	audio_manager = get_node("/root/Root/AudioManager")
	
	game_active = false
	
	if is_player_position_known:
		target = playerTargetRef
	else:
		target = null

func move(direction: Vector3):
	_direction = Vector3(-direction.x, direction.y, -direction.z)

func _process(delta: float) -> void:
	if !_startFlag:
		return
	
	if (!game_active):
		return
	
	if (timeAcc >= timeCooldown):
		var player2DpositionVec = Vector2(playerTargetRef.global_position.x, playerTargetRef.global_position.z)
		var spider2DpositionVec = Vector2(self.global_position.x, self.global_position.z)
		#found that global rotation changes with the rotation of the spider
		#If we control the rotation so that it rotates until player lies within a delta, 
		#We should be able to have a simple move forward method until the player is within attack range
		#or moves outside of the direction it faces
		
		#Spiders global rotation is consistent with the rotation of the model. Even on walls
		#the spiders global rotation of Y is the same. 
		timeAcc = 0.0
	else:
		timeAcc += delta
	
	if is_player_controlled:
		_processPlayer(delta)
	else:
		_processAI(delta)
	
	updateShootCooldown(delta)

func _processPlayer(delta: float) -> void:
	_alignToGround(delta)
	
	var adir := Input.get_axis("R(ALT)", "L(ALT)")
	var dir := Input.get_axis("Down(ALT)", "Up(ALT)")
	face_target(delta)
	_handleMovements(delta, Vector2(adir, dir))
	if Input.is_action_just_pressed("Lclick"):
		shoot()

func _processAI(delta: float) -> void:
	_alignToGround(delta)
	var ai_direction: Vector2
	if target:
		move(self.global_position.direction_to(target.global_position))
		if isFacingTarget():
			ai_direction = determinAIdirection()
			_handleMovements(delta, ai_direction)
			shoot()
		else:
			face_target(delta)

func _alignToGround(delta: float) -> void:
	var p1 = Plane(BackL_Trgt.global_position, FrontL_Trgt.global_position, 
	FrontR_Trgt.global_position)
	var p2 = Plane(FrontR_Trgt.global_position, BackR_Trgt.global_position, 
	BackL_Trgt.global_position)
	var avg_normal = ((p1.normal + p2.normal) / 2).normalized()
	
	var target_basis = _basis_from_normal(avg_normal)
	transform.basis = lerp(transform.basis, target_basis, move_speed * delta).orthonormalized()
	
	var avg = (FrontL_Trgt.position + FrontR_Trgt.position + BackL_Trgt.position + BackR_Trgt.position) / 4
	var target_pos = avg + transform.basis.y * groundOffset
	var distance = transform.basis.y.dot(target_pos - position)
	position = lerp(position, position + transform.basis.y * distance, move_speed * delta)

func _handleMovements(delta: float, direction: Vector2) -> void:
	#translate(Vector3(0, 0, -direction.y) * move_speed * delta)
	#rotate_object_local(Vector3.UP, direction.x * rotation_speed * delta)
	
	var move = Vector3(0, 0, -direction.y) + Vector3(direction.x, 0, 0)
	#var move = (-transform.basis.z * -direction.y) + (transform.basis.x * direction.x)
	translate(move.normalized() * move_speed * delta)
	#face_vector2_direction(direction, delta)
	

func _basis_from_normal(normal: Vector3) -> Basis:
	var result = Basis()
	result.x = normal.cross(transform.basis.z)
	result.y = normal
	result.z = transform.basis.x.cross(normal)
	
	result = result.orthonormalized()
	result.x *= scale.x
	result.y *= scale.y
	result.z *= scale.z
	
	return result

func face_target(delta: float) -> void:
	if _direction:
		_theta = wrapf(atan2(_direction.x, _direction.z) - self.rotation.y, -PI, PI)
		rotate_object_local(Vector3.UP, clamp(rotation_speed * delta, 0, abs(_theta)) * sign(_theta))

func _on_health_handler_death() -> void:
	_die()

func _die() -> void:
	audio_manager.play("SpiderDeath", global_position)
	audio_manager.play("Win", global_position)
	spider_death.emit()
	queue_free()


func _on_detection_field_body_entered(body: Node3D) -> void:
	if !is_player_position_known:
		target = body


func _on_detection_field_body_exited(body: Node3D) -> void:
	if !is_player_position_known:
		target = null
		

func determinAIdirection() -> Vector2:
	var AIdirection = Vector2(_direction.x, -_direction.z)
	return AIdirection

func _start():
	_startFlag = true

func _on_timer_timeout() -> void:
	game_active = true
	_start()

func isFacingTarget() -> bool:
	if _direction:
		_theta = wrapf(atan2(_direction.x, _direction.z) - self.rotation.y, -PI, PI)
		return abs(_theta) < 0.01
	else:
		return false

func shoot() -> void:
	if !canShoot():
		return
	
	if spiderProjectile == null:
		print("Cannot spawn venomball: Scene is null!")
		return
		
	var venomBall = spiderProjectile.instantiate()
	if venomBall == null:
		print("venomBall instantiation failed!")
		return

	if target == null:
		print("No valid target for venomBall!")
		return
	
	if venomBall.has_method("spider_shoot"):
		get_tree().current_scene.add_sibling(venomBall)  # Or use add_sibling(fireball) if needed
		venomBall.global_transform.origin = projOriginPoint.global_position   # 3D position
		venomBall.call("spider_shoot", enemy_damage_r, target.global_transform.origin)
		
		audio_manager.play("SpiderShoot", global_position)
		startShootCooldown()
		

func updateShootCooldown(delta :float):
	if curShootCooldown <= 0.0:
		return
	else:
		curShootCooldown -= delta

func startShootCooldown():
	curShootCooldown = shootCooldown

func canShoot() -> bool:
	if curShootCooldown <= 0.0:
		return true
	
	return false

func _on_game_end() -> void:
	game_active = false
