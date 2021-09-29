#include "boulder-dash2/game_components/Engine.hpp"

bd2::Engine::Engine(sf::RenderWindow &_window) : window_(_window), exit_(false) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

    // set map dimensions
    map_size_ = level->getMapSize();

    map_.resize(map_size_.r,
                std::vector<std::shared_ptr<MapElement>>(map_size_.c, nullptr));

    // create initial map elements
    auto level_map = level->getMap();

    for (int i = 0; i < map_size_.r; i++) {
        for (int j = 0; j < map_size_.c; j++) {
            addMapElement(level_map[i][j], {i, j});
        }
    }
}

void bd2::Engine::processEngineOperations() {

    // clear newly created map elements from the previous turn
    new_objects_.clear();
}

void bd2::Engine::addMapElement(MapElement::Type type, MapCoordinates position) {

    /* if a tile is empty - do nothing (map_[row][column]
    is defaultly set to nullptr) */
    if (MapElement::Type::Empty == type)
        return;

    // allocate a new element
    std::shared_ptr<MapElement> new_element;
    //=       std::make_shared<MapElement>(type, row, column);

    /*     if (type == MapElement::Type::Wall || type == MapElement::Type::Exit ||
            type == MapElement::Type::Ground) { // 1
        } */
    switch (type) {
    case MapElement::Type::Wall:     // 1
    case MapElement::Type::Exit:     // 2
    case MapElement::Type::Ground: { // 3

        new_element = std::make_shared<MapElement>(type, position);

    } break;
    case MapElement::Type::Boulder: { // 4
    } break;

    case MapElement::Type::Diamond: { // 5
    } break;

    case MapElement::Type::Butterfly: { // 6
    } break;

    case MapElement::Type::Firefly: { // 7
    } break;

    case MapElement::Type::Player: { // 8
    } break;

    case MapElement::Type::Explosion: { // 9
    } break;

    default:
        break;
    }

    // put a pointer to a new element onto the map
    map_[position.r][position.c] = new_element;

    // add a new element to the list of elements created during the current turn
    new_objects_.push_back(new_element);
}