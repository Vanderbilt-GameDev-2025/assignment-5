extends Node

@export var enemyHealth = 15.0
@export var enemyMaxHealth = 15.0

signal death

func updateHealth(hpDelta: float):
	print("enemy taken damage: ", hpDelta)
	enemyHealth += hpDelta

	if (enemyHealth <= 0):
		die();
	else:
		if (enemyHealth > enemyMaxHealth):
			enemyHealth = enemyMaxHealth;
			

func die() -> void:
	emit_signal("death")
