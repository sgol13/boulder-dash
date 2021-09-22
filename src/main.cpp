#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"

using namespace std;

int main() {

    //=========================================================================
    // LOADING RESOURCES

    bd2::ResourceHandler<sf::Texture> textures_handler;
    bd2::ResourceHandler<sf::Font> fonts_handler;
    bd2::ResourceHandler<bd2::Level> levels_handler;

    textures_handler.loadResources(GRAPHIC_RESOURCES_LIST, GRAPHIC_RESOURCES_NUM,
                                   BD2_GRAPHIC_RESOURCES_DIR);
    fonts_handler.loadResources(FONT_RESOURCES_LIST, FONT_RESOURCES_NUM,
                                BD2_FONT_RESOURCES_DIR);
    levels_handler.loadResources(LEVEL_RESOURCES_LIST, LEVEL_RESOURCES_NUM,
                                 BD2_LEVEL_RESOURCES_DIR);

    //=========================================================================
    // CREATING WINDOW

    auto video_mode = sf::VideoMode::getDesktopMode();
    video_mode.width *= INI_WINDOW_SCREEN_RATIO_X;
    video_mode.height *= INI_WINDOW_SCREEN_RATIO_Y;

    sf::RenderWindow window(video_mode, WINDOW_NAME);
    window.setPosition(sf::Vector2i(INI_WINDOW_POS_X, INI_WINDOW_POS_Y));
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}