extends StaticBody3D

@onready var HealthSystem = $HealthHandler

func take_damage(hpDelta: float):
	print("Ouch")
	if HealthSystem:
		if HealthSystem.has_method("updateHealth"):
			HealthSystem.updateHealth(-hpDelta)
		else:
			print("updateHealth not achieved")
	else:
		print("Health system not active")
	
