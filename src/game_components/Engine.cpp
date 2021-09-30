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

    auto elapsed_time = clock_.restart();

    for (auto &weak_object : simulated_objects_) {

        if (auto object = weak_object.lock()) {

            object->simulate(elapsed_time);
        }
    }

    // clear newly created map elements from the previous turn
    new_objects_.clear();
}

void bd2::Engine::addMapElement(MapElement::Type type, MapCoordinates position) {

    // allocate a new element
    std::shared_ptr<MapElement> new_element = nullptr;

    switch (type) {
    case MapElement::Type::Empty: // 0 - EMPTY
        break;

    case MapElement::Type::Wall:     // 1 - WALL
    case MapElement::Type::Exit:     // 2 - EXIT
    case MapElement::Type::Ground: { // 3 - GROUND

        new_element = std::make_shared<MapElement>(type, position);

    } break;
    case MapElement::Type::Boulder: { // 4 - BOULDER

    } break;

    case MapElement::Type::Diamond: { // 5 - DIAMOND
    } break;

    case MapElement::Type::Butterfly: { // 6 - BUTTERFLY
    } break;

    case MapElement::Type::Firefly: { // 7 - FIREFLY
    } break;

    case MapElement::Type::Player: { // 8 - PLAYER

        std::shared_ptr<Player> new_player = std::make_shared<Player>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_player);
        player_ = new_player;

    } break;

    case MapElement::Type::Explosion: { // 9 - EXPLOSION
    } break;
    }

    // if new element was allocated
    if (new_element) {

        // put a pointer to a new element onto the map
        map_[position.r][position.c] = new_element;

        // add to the list of simulated objects
        simulated_objects_.insert(new_element);

        // add a new element to the list of elements created during the current turn
        new_objects_.push_back(new_element);
    }
}