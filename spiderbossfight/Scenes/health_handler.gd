extends Node

var audio_manager : AudioManager

signal health_changed(current_HP)

@export var enemyHealth = 15.0
@export var enemyMaxHealth = 15.0

signal death

func _ready():
	audio_manager = get_node("/root/Root/AudioManager")

func updateHealth(hpDelta: float):
	print("enemy taken damage: ", hpDelta)
	enemyHealth += hpDelta
	
	health_changed.emit(enemyHealth)

	if (enemyHealth <= 0):
		die();
	else:
		if (enemyHealth > enemyMaxHealth):
			enemyHealth = enemyMaxHealth;
			

func die() -> void:
	emit_signal("death")
