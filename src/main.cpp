#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"

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


    std::cout << BD2_GRAPHIC_RESOURCES_DIR << "\n";
    std::cout << BD2_FONT_RESOURCES_DIR << "\n";
    std::cout << BD2_LEVEL_RESOURCES_DIR << "\n";

    return 0;
}