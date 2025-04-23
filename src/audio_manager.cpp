#include "audio_manager.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/memory.hpp>

using namespace godot;

void AudioManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play", "sound_name", "position"),  &AudioManager::play);
    ClassDB::bind_method(D_METHOD("clean_up_all_players"),            &AudioManager::clean_up_all_players);
}

AudioManager::~AudioManager() {
    clean_up_all_players();
}

void AudioManager::_ready() {

    struct AudioInfo { const char *name; const char *path; };
    static const AudioInfo AUDIO_FILES[] = {
        { "SpiderStep",  "res://Audio/SFX/spider_step.mp3"   },
        { "SpiderHurt",  "res://Audio/SFX/spider_hurt.wav"   },
        { "SpiderDeath", "res://Audio/SFX/spider_death.wav"  },
        { "PlayerHurt",  "res://Audio/SFX/player_hurt.mp3"   },
        { "Win",         "res://Audio/SFX/win.mp3"           },
        { "PlayerDeath", "res://Audio/SFX/player_death.wav"  },
        { "OutOfAmmo",   "res://Audio/SFX/outofammo.wav"     },
        { "PlayerShoot", "res://Audio/SFX/player_shoot.wav"  },
        { "SpiderShoot", "res://Audio/SFX/spider_shoot.wav"  },
        { "BackgroundMusic", "res://Audio/SFX/bg_music.wav"  },
    };

    ResourceLoader *loader = ResourceLoader::get_singleton();

    for (const AudioInfo &info : AUDIO_FILES) {
        AudioStreamPlayer3D *player = memnew(AudioStreamPlayer3D);
        add_child(player);

        Ref<AudioStream> stream = loader->load(info.path);
        player->set_stream(stream);

        // original fall-off & gain settings
        player->set_unit_size(20.0f);
        player->set_max_distance(60.0f);
        player->set_attenuation_model(AudioStreamPlayer3D::ATTENUATION_DISABLED);
        player->set_volume_db(2.0f);

        audio_players[info.name] = player;
    }
}

void AudioManager::play(const String &sound_name, const Vector3 &position) {
    auto it = audio_players.find(sound_name);
    if (it != audio_players.end() && it->second) {
        AudioStreamPlayer3D *player = it->second;
        player->set_position(position);
        player->play();
    } else {
        UtilityFunctions::printerr("Sound '", sound_name, "' not found!");
    }
}

void AudioManager::clean_up_all_players() {
    // for (auto &pair : audio_players) {
    //     if (pair.second) {
    //         pair.second->stop();
    //         pair.second->queue_free();
    //     }
    // }
    // audio_players.clear();
}
