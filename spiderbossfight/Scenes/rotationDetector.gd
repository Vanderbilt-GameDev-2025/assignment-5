extends RayCast3D

var grounded = false
var hit_point

func _physics_process(delta: float) -> void:
	hit_point = get_collision_point()
	if hit_point:
		grounded = true
	else:
		grounded = false

func isGrounded() -> bool:
	return grounded

func getHitLocation() -> Vector3:
	return hit_point

func needsLowering() -> bool:
	return (self.global_position.distance_to(hit_point) > 2.25)

func needsLift() -> bool:
	return (self.global_position.distance_to(hit_point) < 1.75)
