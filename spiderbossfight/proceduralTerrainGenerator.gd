@tool
extends MeshInstance3D

#Credit: https://www.youtube.com/watch?v=XOLac92RS64
#Procedural Terrain Generator in Godot 4.1

@export_range(20, 400, 1) var Terrain_Size := 100
@export_range(1, 100, 1) var resolution := 30

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
			vertex.y = n.get_noise_2d(vertex.x * noiseOffset, vertex.z * noiseOffset) * Terrain_Max_Height
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
	print("mesh generated")
	update_shader()
	

func update_shader():
	var mat = get_active_material(0)
	if mat:
		mat.set_shader_parameter("min_height", min_height)
		mat.set_shader_parameter("max_height", max_height)

var last_res = 0
var last_size = 0
var last_height = 0
var last_offset = 0

func _process(delta: float) -> void:
	if (resolution != last_res || Terrain_Size != last_size || Terrain_Max_Height != last_height || noiseOffset != last_offset):
		generate_terrain()
		last_res = resolution
		last_size = Terrain_Size
		last_height = Terrain_Max_Height
		last_offset = noiseOffset
	
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
