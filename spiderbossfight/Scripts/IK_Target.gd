@tool
extends Marker3D

@export var step_target: Node3D
@export var step_height: float = 0.5
@export var step_duration: float = 0.05
var is_stepping := false

func step():
	if is_stepping or step_target == null:
		return
	
	is_stepping = true
	
	var target_pos = step_target.global_position
	var half_way = (global_position + target_pos) / 2 + Vector3.UP * step_height
	
	var tween = get_tree().create_tween()
	tween.set_trans(Tween.TRANS_SINE).set_ease(Tween.EASE_IN_OUT)
	tween.tween_property(self, "global_position", half_way, step_duration / 2)
	tween.tween_property(self, "global_position", target_pos, step_duration / 2)
	tween.tween_callback(func(): is_stepping = false)
	
	
