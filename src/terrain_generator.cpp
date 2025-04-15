#include "terrain_generator.h"
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void TerrainGenerator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_resolution", "res"), &TerrainGenerator::set_resolution);
    ClassDB::bind_method(D_METHOD("get_resolution"), &TerrainGenerator::get_resolution);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resolution"), "set_resolution", "get_resolution");

    ClassDB::bind_method(D_METHOD("set_terrain_size", "size"), &TerrainGenerator::set_terrain_size);
    ClassDB::bind_method(D_METHOD("get_terrain_size"), &TerrainGenerator::get_terrain_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "terrain_size"), "set_terrain_size", "get_terrain_size");

    ClassDB::bind_method(D_METHOD("set_terrain_max_height", "height"), &TerrainGenerator::set_terrain_max_height);
    ClassDB::bind_method(D_METHOD("get_terrain_max_height"), &TerrainGenerator::get_terrain_max_height);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "terrain_max_height"), "set_terrain_max_height", "get_terrain_max_height");

    ClassDB::bind_method(D_METHOD("set_noise_offset", "offset"), &TerrainGenerator::set_noise_offset);
    ClassDB::bind_method(D_METHOD("get_noise_offset"), &TerrainGenerator::get_noise_offset);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "noise_offset"), "set_noise_offset", "get_noise_offset");
}

void TerrainGenerator::_ready() {
    generate_terrain();
}

void TerrainGenerator::_process(double delta) {
    //dynamic regeneration if needed
}

void TerrainGenerator::generate_terrain() {
    Ref<ArrayMesh> a_mesh = memnew(ArrayMesh);
    Ref<SurfaceTool> surf_tool = memnew(SurfaceTool);
    Ref<FastNoiseLite> noise = memnew(FastNoiseLite);

    noise->set_noise_type(FastNoiseLite::TYPE_PERLIN);
    noise->set_frequency(0.1);

    surf_tool->begin(Mesh::PRIMITIVE_TRIANGLES);

    int count = resolution + 1;
    for (int z = 0; z < count; z++) {
        for (int x = 0; x < count; x++) {
            Vector2 percent = Vector2(x, z) / float(resolution);
            Vector3 point = Vector3((percent.x - 0.5f), 0, (percent.y - 0.5f)) * terrain_size;
            point.y = noise->get_noise_2d(point.x * noise_offset, point.z * noise_offset) * terrain_max_height;
            surf_tool->set_uv(percent);
            surf_tool->add_vertex(point);
        }
    }

    for (int z = 0; z < resolution; z++) {
        for (int x = 0; x < resolution; x++) {
            int vert = z * (resolution + 1) + x;
            surf_tool->add_index(vert + 0);
            surf_tool->add_index(vert + 1);
            surf_tool->add_index(vert + resolution + 1);

            surf_tool->add_index(vert + resolution + 1);
            surf_tool->add_index(vert + 1);
            surf_tool->add_index(vert + resolution + 2);
        }
    }

    surf_tool->generate_normals();
    a_mesh = surf_tool->commit();
    set_mesh(a_mesh);

    UtilityFunctions::print("Mesh generated.");
}

void TerrainGenerator::set_resolution(int p_res) { resolution = p_res; }
int TerrainGenerator::get_resolution() const { return resolution; }

void TerrainGenerator::set_terrain_size(int p_size) { terrain_size = p_size; }
int TerrainGenerator::get_terrain_size() const { return terrain_size; }

void TerrainGenerator::set_terrain_max_height(float p_height) { terrain_max_height = p_height; }
float TerrainGenerator::get_terrain_max_height() const { return terrain_max_height; }

void TerrainGenerator::set_noise_offset(float p_offset) { noise_offset = p_offset; }
float TerrainGenerator::get_noise_offset() const { return noise_offset; }