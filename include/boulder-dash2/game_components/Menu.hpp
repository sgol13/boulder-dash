#ifndef BD2_MENU_HPP
#define BD2_MENU_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Player.hpp"

namespace bd {

class Menu {
  public:
    Menu(sf::RenderWindow &_window,
         const ResourceHandler<sf::Texture> &_textures_handler,
         const ResourceHandler<sf::Font> &_fonts_handler,
         const ResourceHandler<sf::SoundBuffer> &_sounds_handler,
         const int _levels_num);

    int open();

  private:
    void handleEvents();

    void handleKeyPressed(const sf::Event::KeyEvent &key);

    void setPlayerPosition();

    sf::View getMenuView();

    sf::RenderWindow &window_;
    const ResourceHandler<sf::Texture> &textures_handler_;
    const ResourceHandler<sf::Font> &fonts_handler_;
    const ResourceHandler<sf::SoundBuffer> &sounds_handler_;
    const int levels_num_;

    bool exit_menu_;
    int current_menu_option_;

    sf::Text game_name_text_;
    std::vector<sf::Text> options_texts_;
    Player player_;
    sf::Sound change_option_sound_;
    sf::Vector2u menu_size_;

    sf::Clock clock_;
};

} // namespace bd

#endif