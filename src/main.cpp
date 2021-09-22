#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"

int main() {

    // LOADING RESOURCES
    bd2::ResourceHandler<sf::Texture> textures_handler;
    bd2::ResourceHandler<sf::Font> fonts_handler;

    textures_handler.loadResources(GRAPHIC_RESOURCES_LIST, GRAPHIC_RESOURCES_NUM);

    auto ptr = textures_handler.getResource("exit.png");

    auto a = textures_handler.getMissingResources();

    return 0;
}