// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Game.hpp"
#include "boulder-dash2/game_components/Menu.hpp"
#include "boulder-dash2/game_components/Ranking.hpp"
#include "boulder-dash2/resources.hpp"

int main() {

    //===========================================================================
    // LOADING RESOURCES
    //===========================================================================

    bd::ResourceHandler<sf::Texture> textures_handler;
    bd::ResourceHandler<sf::Font> fonts_handler;
    bd::ResourceHandler<sf::SoundBuffer> sounds_handler;
    bd::ResourceHandler<bd::Level> levels_handler;

    bool loading_flag1 = textures_handler.loadResources(
        bd::resources::texture_files, bd::resources::texture_files_num,
        BD2_GRAPHIC_RESOURCES_DIR);

    bool loading_flag2 = fonts_handler.loadResources(bd::resources::font_files,
                                                     bd::resources::font_files_num,
                                                     BD2_FONT_RESOURCES_DIR);

    bool loading_flag3 = sounds_handler.loadResources(bd::resources::sound_files,
                                                      bd::resources::sound_files_num,
                                                      BD2_AUDIO_RESOURCES_DIR);

    bool loading_flag4 = levels_handler.loadResources(bd::resources::level_files,
                                                      bd::resources::level_files_num,
                                                      BD2_LEVEL_RESOURCES_DIR);

    if (!loading_flag1 || !loading_flag2 || !loading_flag3 || !loading_flag4) {

        auto all_missing_resources = {textures_handler.getMissingResources(),
                                      fonts_handler.getMissingResources(),
                                      sounds_handler.getMissingResources(),
                                      levels_handler.getMissingResources()};

        std::cerr << "ERROR - missing resources:\n";

        for (auto &missing_resources : all_missing_resources) {
            for (auto &resource : missing_resources) {
                std::cerr << resource << std::endl;
            }
        }

        return 1;
    }

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

    if (auto icon_texture = textures_handler[bd::resources::Textures::PROGRAM_ICON]) {

        auto icon_image = icon_texture->copyToImage();
        auto icon_size = icon_image.getSize();
        window.setIcon(icon_size.x, icon_size.y, icon_image.getPixelsPtr());
    }

    //=========================================================================
    // STARTING THE GAME
    //=========================================================================

    bd::Game game(window, textures_handler, fonts_handler, sounds_handler);
    bd::Menu menu(window, textures_handler, fonts_handler, sounds_handler,
                  bd::resources::level_files_num);
    bd::Ranking ranking(window, fonts_handler);

    while (window.isOpen()) {

        int menu_option = menu.open();

        if (menu_option == 0) {
            window.close();
            break;
        }

        auto level_label = bd::resources::level_files[menu_option - 1].first;
        auto level = levels_handler[level_label];

        int score = game.play(level);

        if (score > 0) {
            ranking.open(*level, menu_option, score);
        }
    }

    return 0;
}