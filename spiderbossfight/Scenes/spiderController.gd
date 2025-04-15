extends CharacterBody3D

@export var jump_velocity: float = 10.0
@export var move_speed: float = 5.0

func _physics_process(delta: float) -> void:
	# Apply gravity
	if not is_on_floor():
		velocity += get_gravity() * delta
	else :
		print("On floor")

	# Handle jump.
	if Input.is_action_just_pressed("Space") and is_on_floor():
		velocity.y = jump_velocity

	# Optional movement (W/S or Up/Down keys)
	var input_direction = Vector3(
		Input.get_action_strength("R(ALT)") - Input.get_action_strength("L(ALT)"),
		0,
		Input.get_action_strength("Down(ALT)") - Input.get_action_strength("Up(ALT)")
	).normalized()

	# Move in local space
	var direction = global_transform.basis * input_direction
	velocity.x = direction.x * move_speed
	velocity.z = direction.z * move_speed

	move_and_slide()
