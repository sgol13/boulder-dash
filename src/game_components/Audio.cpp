#include "boulder-dash2/game_components/Audio.hpp"

bd2::Audio::Audio(sf::RenderWindow &_window,
                  const ResourceHandler<sf::SoundBuffer> &_sounds_handler)
    : Engine(_window), sounds_handler_(_sounds_handler), previous_pause_(false) {

    music_.setBuffer(*sounds_handler_[resources::Sounds::MUSIC]);
    music_.setLoop(true);
    music_.setVolume(MUSIC_VOLUME);

    for (int i = 0; i < resources::sound_files_num; i++) {

        sounds_[resources::sound_files[i].first].setBuffer(
            *sounds_handler_[resources::sound_files[i].first]);
    }
}

void bd2::Audio::initialiseAudio() { music_.play(); }

void bd2::Audio::processAudioOperations() {

    for (auto &sound_to_play : sounds_to_play_) {

        auto sound_it = sounds_.find(sound_to_play);
        if (sound_it != sounds_.end()) {
            sound_it->second.play();
        }
    }

    if (pause_ && !previous_pause_) {

        music_.pause();
        for (auto &sound : sounds_) {
            if (sound.second.getStatus() == sf::Sound::Status::Playing) {
                sound.second.pause();
            }
        }
        previous_pause_ = true;

    } else if (!pause_ && previous_pause_) {

        music_.play();
        for (auto &sound : sounds_) {
            if (sound.second.getStatus() == sf::Sound::Status::Paused) {
                sound.second.play();
            }
        }
        previous_pause_ = false;
    }

    if (end_game_) {
        music_.stop();
    }
}