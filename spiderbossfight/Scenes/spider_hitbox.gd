extends StaticBody3D

var audio_manager : AudioManager

@onready var HealthSystem = $HealthHandler

func _ready():
	audio_manager = get_node("/root/Root/AudioManager")

func take_damage(hpDelta: float):
	print("Ouch")
	audio_manager.play("SpiderHurt", global_position)
	if HealthSystem:
		if HealthSystem.has_method("updateHealth"):
			HealthSystem.updateHealth(-hpDelta)
		else:
			print("updateHealth not achieved")
	else:
		print("Health system not active")
	
