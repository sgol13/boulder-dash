#include "boulder-dash2/game_components/Engine.hpp"

bd2::Engine::Engine(sf::RenderWindow &_window,
                    const ResourceHandler<sf::Texture> &_textures_handler)
    : window_(_window), textures_handler_(_textures_handler), exit_(false) {}


void bd2::Engine::processEngineOperations() {}

void bd2::Engine::initialiseLevel(const std::shared_ptr<const Level> level) {

    // set map dimensions
    n_rows_ = level->getNumRows();
    n_columns_ = level->getNumRows();

    map_.resize(n_rows_, std::vector<std::shared_ptr<MapElement>>(n_columns_));

    // create initial map elements
    auto level_map = level->getMap();

    for (int i = 0; i < n_rows_; i++) {
        for (int j = 0; j < n_columns_; j++) {
            addMapElement(level_map[i][j], i, j);
        }
    }
}

void bd2::Engine::addMapElement(MapElement::Type type, int pos_i, int pos_j) {

    std::shared_ptr<MapElement> new_element = nullptr;

    switch (type) {
    case MapElement::Type::Wall: // 1
        new_element = std::make_shared<MapElement>(MapElement::Type::Wall);
        break;

    case MapElement::Type::Exit: // 2
        new_element = std::make_shared<MapElement>(MapElement::Type::Exit);
        break;

    case MapElement::Type::Ground: // 3
        new_element = std::make_shared<MapElement>(type);
        break;

    default:
        new_element = nullptr;
        break;
    }

    map_[pos_i][pos_j] = new_element;
    drawable_objects_.insert(new_element);
}