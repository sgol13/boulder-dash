#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Game.hpp"
#include "boulder-dash2/game_components/Menu.hpp"
#include "boulder-dash2/game_components/Ranking.hpp"
#include "boulder-dash2/resources.hpp"

int main() {

    srand(static_cast<unsigned int>(time(0)));

    //===========================================================================
    // LOADING RESOURCES
    //===========================================================================

    bd2::ResourceHandler<sf::Texture> textures_handler;
    bd2::ResourceHandler<sf::Font> fonts_handler;
    bd2::ResourceHandler<sf::SoundBuffer> sounds_handler;
    bd2::ResourceHandler<bd2::Level> levels_handler;

    textures_handler.loadResources(bd2::resources::texture_files,
                                   bd2::resources::texture_files_num,
                                   BD2_GRAPHIC_RESOURCES_DIR);

    fonts_handler.loadResources(bd2::resources::font_files,
                                bd2::resources::font_files_num,
                                BD2_FONT_RESOURCES_DIR);

    sounds_handler.loadResources(bd2::resources::sound_files,
                                 bd2::resources::sound_files_num,
                                 BD2_AUDIO_RESOURCES_DIR);

    levels_handler.loadResources(bd2::resources::level_files,
                                 bd2::resources::level_files_num,
                                 BD2_LEVEL_RESOURCES_DIR);

    //=========================================================================
    // CREATING WINDOW
    //=========================================================================

    auto window_mode = sf::VideoMode::getDesktopMode();
    window_mode.width = static_cast<unsigned int>(
        static_cast<float>(window_mode.width) * INI_WINDOW_SCREEN_RATIO_X);

    window_mode.height = static_cast<unsigned int>(
        static_cast<float>(window_mode.height) * INI_WINDOW_SCREEN_RATIO_Y);

    sf::RenderWindow window(window_mode, WINDOW_NAME);
    window.setPosition(sf::Vector2i(INI_WINDOW_POS_X, INI_WINDOW_POS_Y));
    window.setVerticalSyncEnabled(true);

    if (auto icon_texture = textures_handler[bd2::resources::Textures::ICON]) {

        auto icon_image = icon_texture->copyToImage();
        auto icon_size = icon_image.getSize();
        window.setIcon(icon_size.x, icon_size.y, icon_image.getPixelsPtr());
    }

    bd2::Menu menu(window, textures_handler, fonts_handler, sounds_handler,
                   bd2::resources::level_files_num);
    bd2::Ranking ranking(window, fonts_handler);
    bd2::Game game(window, textures_handler, fonts_handler, sounds_handler);

    while (window.isOpen()) {

        int menu_option = menu.open();

        if (menu_option == 0) {
            window.close();
            break;
        }

        auto level_label = bd2::resources::level_files[menu_option - 1].first;
        auto level = levels_handler[level_label];
        int score = game.play(level);

        if (score > 0) {
            ranking.open(*level, menu_option, score);
        }
    }

    return 0;
}