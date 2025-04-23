extends Node

# UI nodes
var ui_startMenu
var ui_outOfAmmo
var ui_dead
var ui_win
var ui_spiderHealth

var fullscreen = false

# --- Ready and process ---

func _ready() -> void:
	ui_startMenu = get_node("../UI/StartMenu")
	ui_outOfAmmo = get_node("../UI/OutOfAmmo")
	ui_dead = get_node("../UI/Dead")
	ui_win = get_node("../UI/Win")
	ui_spiderHealth = get_node("../UI/SpiderHealth")
	
	var healthHandler = get_node("/root/Root/spiderBoss/SpiderHitbox/HealthHandler")
	healthHandler.connect("health_changed", _on_update_spider_health)

#func _process(delta: float) -> void:
#	pass


# --- Input handling ---

func _unhandled_input(event: InputEvent) -> void:
	if Input.is_action_just_pressed("Esc"):
		get_tree().quit()
		
	if Input.is_action_just_pressed("Restart"):
		get_tree().reload_current_scene()
		
	if Input.is_action_just_pressed("Fullscreen"):
		if (!fullscreen):
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
			fullscreen = true
		else:
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)
			fullscreen = false


# --- Signals ---

func _on_timer_timeout() -> void:
	ui_startMenu.visible = false

func _on_player_ammo_empty() -> void:
	ui_outOfAmmo.visible = true

func _on_player_death() -> void:
	ui_dead.visible = true

func _on_spider_death() -> void:
	ui_win.visible = true

func _on_update_spider_health(spiderHP: float):
	ui_spiderHealth.text = str("Spider Health: ", spiderHP)
