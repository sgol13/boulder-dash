#include "boulder-dash2/game_components/Engine.hpp"

bd2::Engine::Engine(sf::RenderWindow &_window) : window_(_window), exit_(false) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

    // set map dimensions
    rows_num_ = level->getNumRows();
    columns_num_ = level->getNumColumns();

    std::cout << rows_num_ << " " << columns_num_ << std::endl;

    map_.resize(rows_num_,
                std::vector<std::shared_ptr<MapElement>>(columns_num_, nullptr));

    // create initial map elements
    auto level_map = level->getMap();

    for (int i = 0; i < rows_num_; i++) {
        for (int j = 0; j < columns_num_; j++) {
            addMapElement(level_map[i][j], i, j);
        }
    }
}

void bd2::Engine::processEngineOperations() {

    // clear newly created map elements from the previous turn
    new_objects_.clear();
}

void bd2::Engine::addMapElement(MapElement::Type type, int row, int column) {

    /* if a tile is empty - do nothing (map_[row][column]
    is defaultly set to nullptr) */
    if (MapElement::Type::Empty == type)
        return;

    // allocate a new element
    std::shared_ptr<MapElement> new_element =
        std::make_shared<MapElement>(type, row, column);

    switch (type) {
    case MapElement::Type::Wall: // 1
        break;

    case MapElement::Type::Exit: // 2
        break;

    case MapElement::Type::Ground: // 3
        break;

    default:
        break;
    }

    // put a pointer to a new element onto the map
    map_[row][column] = new_element;

    // add a new element to the list of elements created during the current turn
    new_objects_.push_back(new_element);
}