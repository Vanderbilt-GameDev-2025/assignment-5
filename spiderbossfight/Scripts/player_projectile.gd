extends Area3D

var velocity = Vector3.ZERO
var speed = 50.0
var dmg = 0.0
var playerRef

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

func explode():
	#play explosion animation + deal explosive damage
	queue_free()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if velocity != Vector3.ZERO:
		position += velocity * delta

func _on_body_entered(body: Node3D) -> void:
	#When collides with an enemy layer, run the take damage on the enemy
	print("Boom")
	if body.has_method("take_damage"):
		body.take_damage(dmg)
	explode()

func set_damage(damage: float):
	if dmg == damage:
		pass
	else:
		dmg = damage

func set_playerRef(body: Node3D):
	playerRef = body

func set_velocity(dir: Vector3):
	velocity = dir.normalized() * speed

func spider_shoot(damage: float, target_pos: Vector3):
	print("Shoot")
	set_damage(damage)
	var direction = self.global_position.direction_to(target_pos)
	set_velocity(direction * speed)
