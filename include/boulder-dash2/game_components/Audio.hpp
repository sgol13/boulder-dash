#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"

namespace bd2 {

class Audio : virtual public Engine {
  public:
    Audio(sf::RenderWindow &_window,
          const ResourceHandler<sf::SoundBuffer> &_sounds_handler);

  protected:
    void initialiseAudio();

    void processAudioOperations();

  private:
    const ResourceHandler<sf::SoundBuffer> &sounds_handler_;

    sf::Sound music_;

    std::map<resources::Sounds, sf::Sound> sounds_;
};

} // namespace bd2

#endif