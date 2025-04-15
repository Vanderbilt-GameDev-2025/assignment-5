#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/fast_noise_lite.hpp>

namespace godot {

class TerrainGenerator : public MeshInstance3D {
    GDCLASS(TerrainGenerator, MeshInstance3D)

private:
    int resolution = 30;
    int terrain_size = 100;
    float terrain_max_height = 5.0;
    float noise_offset = 0.5;

    float min_height = 0.0;
    float max_height = 1.0;

    void generate_terrain();
    void update_shader();

protected:
    static void _bind_methods();

public:
    TerrainGenerator() = default;

    void _ready() override;
    void _process(double delta) override;

    void set_resolution(int p_res);
    int get_resolution() const;

    void set_terrain_size(int p_size);
    int get_terrain_size() const;

    void set_terrain_max_height(float p_height);
    float get_terrain_max_height() const;

    void set_noise_offset(float p_offset);
    float get_noise_offset() const;
};

}

#endif // TERRAIN_GENERATOR_H