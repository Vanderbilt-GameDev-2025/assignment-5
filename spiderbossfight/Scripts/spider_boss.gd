extends Node3D

@export var move_speed: float = 5.0
@export var turn_speed: float = 1.0

func _process(delta: float) -> void:
	var dir = Input.get_axis("Down(ALT)", "Up(ALT)")
	translate(Vector3(0, 0, -dir) * move_speed * delta)
	
	var a_dir = Input.get_axis("R(ALT)", "L(ALT)")
	rotate_object_local(Vector3.UP, a_dir * turn_speed * delta)
	
