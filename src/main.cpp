#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/resources.hpp"
//#include "boulder-dash2/game_components/Game.hpp"

int main() {

    //===========================================================================
    // LOADING RESOURCES
    //===========================================================================

    bd2::ResourceHandler<sf::Texture> textures_handler;
    bd2::ResourceHandler<sf::Font> fonts_handler;
    bd2::ResourceHandler<bd2::Level> levels_handler;

    textures_handler.loadResources(bd2::resources::texture_files,
                                   bd2::resources::texture_files_num,
                                   BD2_GRAPHIC_RESOURCES_DIR);

    fonts_handler.loadResources(bd2::resources::font_files,
                                bd2::resources::font_files_num,
                                BD2_FONT_RESOURCES_DIR);

    levels_handler.loadResources(bd2::resources::level_files,
                                 bd2::resources::level_files_num,
                                 BD2_LEVEL_RESOURCES_DIR);

    //=========================================================================
    // CREATING WINDOW

    /*     auto video_mode = sf::VideoMode::getDesktopMode();
        video_mode.width *= INI_WINDOW_SCREEN_RATIO_X;
        video_mode.height *= INI_WINDOW_SCREEN_RATIO_Y;

        sf::RenderWindow window(video_mode, WINDOW_NAME);
        window.setPosition(sf::Vector2i(INI_WINDOW_POS_X, INI_WINDOW_POS_Y));
        window.setVerticalSyncEnabled(true);

        bd2::Game game(window, textures_handler);
        game.play(levels_handler.getResource("level1")); */

    return 0;
}