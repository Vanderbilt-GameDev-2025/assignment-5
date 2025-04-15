extends Node3D

@export var is_player_controlled := true

var target

@export var move_speed: float = 5.0
@export var turn_speed: float = 1.0
@export var groundOffset: float = 1.0
@onready var groundDetector = $GroundDetector

@onready var FrontL_Trgt = $FrontL_IK_Trgt
@onready var FrontR_Trgt = $FrontR_IK_Trgt
@onready var BackR_Trgt = $BackR_IK_Trgt
@onready var BackL_Trgt = $BackL_IK_Trgt

func _process(delta: float) -> void:
	if is_player_controlled:
		_processPlayer(delta)
	else:
		_processAI(delta)

func _processPlayer(delta: float) -> void:
	_alignToGround(delta)
	
	var dir := Vector2(Input.get_axis("L(ALT)", "R(ALT)"), 
	Input.get_axis("Down(ALT)", "Up(ALT)"))
	_handleMovements(delta, dir)

func _processAI(delta: float) -> void:
	_alignToGround(delta)
	
	var ai_direction: Vector2
	if target:
		var targetDir = self.global_position.direction_to(target.global_position)
		ai_direction = Vector2(targetDir.x, targetDir.z).normalized()
	else:
		ai_direction = Vector2.ZERO
	
	_handleMovements(delta, ai_direction)

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
	var move = Vector3(0, 0, -direction.y) + Vector3(direction.x, 0, 0)
	translate(move.normalized() * move_speed * delta)
	face_vector2_direction(direction, delta)

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

func face_vector2_direction(direction: Vector2, delta: float) -> void:
	if direction.length() < 0.01:
		return # Too small to matter
	
	direction = direction.normalized()
	
	# Get the angle the Vector2 is pointing to (in radians)
	var angle = atan2(direction.x, direction.y)
	
	# Apply that angle as rotation around the Y axis (Yaw)
	self.rotate_y(-angle * delta)


func _on_health_handler_death() -> void:
	_die()

func _die() -> void:
	queue_free()


func _on_detection_field_body_entered(body: Node3D) -> void:
	print("entered")
	target = body


func _on_detection_field_body_exited(body: Node3D) -> void:
	print("exited")
	target = null
