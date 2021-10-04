#include "boulder-dash2/game_components/Engine.hpp"

// ==============================================================================
// DOUBLE TILE
// ==============================================================================

bd2::Engine::DoubleTile::DoubleTile() : ptr0_(nullptr), ptr1_(nullptr) {}

bd2::Engine::DoubleTile::DoubleTile(const std::shared_ptr<MapElement> &_ptr0)
    : ptr0_(_ptr0) {}

bd2::Engine::DoubleTile::DoubleTile(const std::shared_ptr<MapElement> &_ptr0,
                                    const std::shared_ptr<MapElement> &_ptr1)
    : ptr0_(_ptr0), ptr1_(_ptr1) {}

std::shared_ptr<bd2::MapElement> &
bd2::Engine::DoubleTile::operator=(const std::shared_ptr<MapElement> &ptr) {

    add(ptr);

    if (ptr0_ == ptr)
        return ptr0_;
    else if (ptr1_ == ptr)
        return ptr1_;

    return const_cast<std::shared_ptr<MapElement> &>(empty_ptr);
}

std::shared_ptr<bd2::MapElement> &bd2::Engine::DoubleTile::operator[](int n) {

    if (n == 0)
        return ptr0_;

    if (n == 1)
        return ptr1_;

    return const_cast<std::shared_ptr<MapElement> &>(empty_ptr);
}

int bd2::Engine::DoubleTile::size() const {

    if (ptr0_ == nullptr)
        return 0;

    if (ptr1_ == nullptr)
        return 1;

    return 2;
}

void bd2::Engine::DoubleTile::remove(int n) {

    if (n == 0) {
        ptr0_ = nullptr;
        ptr0_ = ptr1_;
        ptr1_ = nullptr;

    } else if (n == 1)
        ptr1_ = nullptr;
}

void bd2::Engine::DoubleTile::remove(const std::shared_ptr<MapElement> &ptr_remove) {

    if (ptr_remove == ptr0_)
        remove(0);
    else if (ptr_remove == ptr1_)
        remove(1);
}

bool bd2::Engine::DoubleTile::add(const std::shared_ptr<MapElement> &ptr_add) {

    if (ptr0_ == nullptr)
        ptr0_ = ptr_add;
    else if (ptr1_ == nullptr)
        ptr1_ = ptr_add;
    else
        return false;

    return true;
}

bd2::Engine::DoubleTile::operator std::shared_ptr<MapElement> &() { return ptr0_; }

const std::shared_ptr<bd2::MapElement> bd2::Engine::DoubleTile::empty_ptr = nullptr;

// ==============================================================================
// ENGINE
// ==============================================================================

bd2::Engine::Engine(sf::RenderWindow &_window) : window_(_window) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

    new_objects_.clear();
    map_objects_.clear();
    exit_ = false;
    map_.clear();
    clock_.restart();

    // set map dimensions
    map_size_ = level->getMapSize();

    map_.resize(map_size_.r, std::vector<DoubleTile>(map_size_.c));

    // create initial map elements
    auto level_map = level->getMap();

    for (int i = 0; i < map_size_.r; i++) {
        for (int j = 0; j < map_size_.c; j++) {
            addMapElement(level_map[i][j], {i, j});
        }
    }
}

void bd2::Engine::processEngineOperations() {

    turn_elapsed_time_ = clock_.restart();

    // clear the list of newly created map elements from the previous turn
    new_objects_.clear();

    // delete pointers to non-existing objects - they are in the beginning of the set,
    // thanks to the special compare operator (bd2::MapElement::Compare())
    /*     while (!map_objects_.empty() && map_objects_.begin()->expired()) {
            map_objects_.erase(map_objects_.begin());
        } */

    // simulate and finish moves
    for (auto &weak_moveable_object : moveable_objects_) {

        auto moveable_object = weak_moveable_object.lock();

        moveable_object->simulateMovement(turn_elapsed_time_);

        if (moveable_object->getMovePhase() == Moveable::MovePhase::ENDED_MOVE) {
            finishObjectMove(moveable_object);
        }
    }

    // start new moves
    for (auto &weak_moveable_object : moveable_objects_) {

        auto moveable_object = weak_moveable_object.lock();

        if (moveable_object->getMovePhase() == Moveable::MovePhase::STANDING) {

            auto map3x3 = getMap3x3(moveable_object->getMapPosition());
            auto planned_move = moveable_object->getPlannedMove(map3x3);
            startObjectMove(moveable_object, planned_move);
        }
    }
}

void bd2::Engine::addMapElement(MapElement::Type type, MapCoordinates position) {

    std::shared_ptr<MapElement> new_element = nullptr;

    switch (type) {
    case MapElement::Type::Empty: // 0 - EMPTY
        break;

    case MapElement::Type::Wall:      // 1 - WALL
    case MapElement::Type::Ground:    // 2 - GROUND
    case MapElement::Type::Diamond: { // 3 - DIAMOND

        new_element = std::make_shared<MapElement>(type, position);

    } break;

    case MapElement::Type::Exit: { // 6 - EXIT

    } break;

    case MapElement::Type::Boulder: { // 5 - BOULDER

    } break;

    case MapElement::Type::Butterfly: // 6 - BUTTERFLY
    case MapElement::Type::Firefly: { // 7 - FIREFLY

        std::shared_ptr<Moveable> new_moveable =
            std::make_shared<Flyable>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_moveable);

    } break;

    case MapElement::Type::Player: { // 8 - PLAYER

        std::shared_ptr<Player> new_player = std::make_shared<Player>(type, position);
        player_ = new_player;
        new_element = std::dynamic_pointer_cast<MapElement>(new_player);

    } break;

    case MapElement::Type::Explosion: { // 9 - EXPLOSION
    } break;
    }

    if (new_element) {

        map_[position.r][position.c] = new_element;
        map_objects_.insert(new_element);

        if (auto new_moveable = std::dynamic_pointer_cast<Moveable>(new_element)) {
            moveable_objects_.insert(new_moveable);
        }

        // add a new element to the list of elements created during the current turn
        new_objects_.push_back(new_element);
    }
}

void bd2::Engine::startObjectMove(const std::shared_ptr<Moveable> &object,
                                  MapCoordinates planned_move) {

    if (planned_move) {

        auto position = object->getMapPosition();
        auto target_position = position + planned_move;
        std::cout << target_position << "\n";

        map_[target_position.r][target_position.c] = object;

        object->startMove(planned_move);
    }
}

void bd2::Engine::finishObjectMove(const std::shared_ptr<Moveable> &object) {

    auto position = object->getMapPosition();
    map_[position.r][position.c].remove(object);
    object->finishMove();
}

bd2::Moveable::Map3x3 bd2::Engine::getMap3x3(MapCoordinates center) {

    Moveable::Map3x3 map3x3 = {};

    if (center.r < 1 || center.c < 1 || center.r + 1 >= map_size_.r ||
        center.c + 1 >= map_size_.c + 1) {
        return map3x3;
    }

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {

            switch (map_[center.r + r - 1][center.c + c - 1].size()) {
            case 0:
                map3x3[r][c] = MapElement::Type::Empty;
                break;

            case 1:
                map3x3[r][c] = map_[center.r + r - 1][center.c + c - 1][0]->type_;
                break;

            case 2:
                map3x3[r][c] = MapElement::Type::Wall;
                break;

            default:
                break;
            }
        }
    }

    return map3x3;
}