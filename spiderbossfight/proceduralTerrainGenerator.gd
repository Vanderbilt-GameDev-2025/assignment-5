@tool
extends MeshInstance3D

#Credit: https://www.youtube.com/watch?v=XOLac92RS64
#Procedural Terrain Generator in Godot 4.1

@export_range(20, 400, 1) var Terrain_Size := 100
@export_range(1, 100, 1) var resolution := 30

@export_range(0, 100, 1) var noise_zoom:= 0.0  # Zoom level of noise (higher = more zoomed-in detail)
@export_range(-100.0, 100.0, 1.0) var noise_focus_x: float = 0.0
@export_range(-100.0, 100.0, 1.0) var noise_focus_y: float = 0.0

const centerOffset := 0.5
@export var Terrain_Max_Height = 5
@export var noiseOffset = 0.5
@export var create_collision = false
@export var remove_collision = false

var min_height = 0
var max_height = 1

func _ready():
	generate_terrain()

func generate_terrain():
	var a_mesh = ArrayMesh.new()
	var surfTool = SurfaceTool.new()
	var n = FastNoiseLite.new()
	n.noise_type = FastNoiseLite.TYPE_PERLIN
	n.frequency = 0.1
	surfTool.begin(Mesh.PRIMITIVE_TRIANGLES)
	
	for z in resolution+1:
		for x in resolution+1:
			var percent = Vector2(x,z)/resolution
			var pointOnMesh = Vector3((percent.x - centerOffset), 0, (percent.y - centerOffset))
			var vertex = pointOnMesh * Terrain_Size
			var noise_x = (vertex.x * noiseOffset + get_noise_focus().x) * (noise_zoom / 100)
			var noise_z = (vertex.z * noiseOffset + get_noise_focus().y) * (noise_zoom / 100)
			vertex.y = n.get_noise_2d(noise_x, noise_z) * Terrain_Max_Height
			var uv = Vector2()
			uv.x = percent.x
			uv.y = percent.y
			surfTool.set_uv(uv)
			surfTool.add_vertex(vertex)
	var vert = 0
	for z in resolution:
		for x in resolution:
			surfTool.add_index(vert+0)
			surfTool.add_index(vert+1)
			surfTool.add_index(vert+resolution+1)
			surfTool.add_index(vert+resolution+1)
			surfTool.add_index(vert+1)
			surfTool.add_index(vert+resolution+2)
			vert+=1
		vert+=1
	surfTool.generate_normals()
	a_mesh = surfTool.commit()
	
	mesh = a_mesh
	update_shader()
	_update_collision(a_mesh)
	

func update_shader():
	var mat = get_active_material(0)
	if mat:
		mat.set_shader_parameter("min_height", min_height)
		mat.set_shader_parameter("max_height", max_height)

var last_res = 0
var last_size = 0
var last_height = 0
var last_offset = 0
var last_zoom = 0
var last_focus = Vector2.ZERO

func _process(delta: float) -> void:
	if (resolution != last_res || Terrain_Size != last_size || Terrain_Max_Height != 
	last_height || noiseOffset != last_offset || noise_zoom != last_zoom || get_noise_focus() != last_focus):
		generate_terrain()
		last_res = resolution
		last_size = Terrain_Size
		last_height = Terrain_Max_Height
		last_offset = noiseOffset
		last_zoom = noise_zoom
		last_focus = get_noise_focus()
	
	if remove_collision:
		clear_collision()
		remove_collision = false
	if create_collision:
		create_trimesh_collision()
		create_collision = false
	
func generate_collision():
	clear_collision()
	create_trimesh_collision()
	
func clear_collision():
	if get_child_count() > 0:
		for i in get_children():
			i.free()

func get_noise_focus() -> Vector2:
	return Vector2(noise_focus_x, noise_focus_y)

func _update_collision(meshData: ArrayMesh) -> void:
	var static_body = $StaticBody3D
	if static_body && static_body is StaticBody3D:
		var shape = meshData.create_trimesh_shape()
		var collider = static_body.get_node("CollisionShape3D") if static_body.has_node("CollisionShape3D") else null
		if collider && collider is CollisionShape3D:
			collider.shape = shape
