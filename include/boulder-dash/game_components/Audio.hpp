// Szymon Golebiowski
// Boulder Dash

#ifndef BD_AUDIO_HPP
#define BD_AUDIO_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/game_components/Engine.hpp"

namespace bd {

class Audio : virtual public Engine {
  public:
    Audio(sf::RenderWindow &_window,
          const ResourceHandler<sf::SoundBuffer> &_sounds_handler);

  protected:
    void initialiseAudio();

    void processAudioOperations();

    void finaliseAudio();

  private:
    const ResourceHandler<sf::SoundBuffer> &sounds_handler_;

    sf::Sound music_;
    std::map<resources::Sounds, sf::Sound> sounds_;

    bool previous_pause_;
};

} // namespace bd

#endif