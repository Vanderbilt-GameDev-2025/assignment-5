#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>     // NEW – ensures AudioStream is a complete type
#include <godot_cpp/core/class_db.hpp>

#include <map>

namespace godot {

class AudioManager : public Node3D {
    GDCLASS(AudioManager, Node3D);

private:
    // changed unordered_map → map to avoid the missing std::hash<String> problem
    std::map<String, AudioStreamPlayer3D *> audio_players;

protected:
    static void _bind_methods();

public:
    AudioManager() = default;
    ~AudioManager() override;

    void _ready() override;

    void play(const String &sound_name, const Vector3 &position);
    void clean_up_all_players();
};

} // namespace godot

#endif /* AUDIO_MANAGER_H */
