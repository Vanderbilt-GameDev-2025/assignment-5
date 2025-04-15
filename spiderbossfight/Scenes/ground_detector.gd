extends RayCast3D

var grounded = false
var altitude = 0.0

@onready var hitMarker = $MeshInstance3D

func _physics_process(delta: float) -> void:
	var hit_point = get_collision_point()
	if hit_point:
		hitMarker.global_position = hit_point
		grounded = true
	else:
		grounded = false
	
	if isGrounded():
		altitude = hit_point.y

func isGrounded() -> bool:
	return grounded

func getHitAltitude() -> float:
	return altitude

func needsLowering() -> bool:
	return (self.global_position.y - getHitAltitude() > 2.0)

func needsLift() -> bool:
	return (self.global_position.y - getHitAltitude() < 1.75)
