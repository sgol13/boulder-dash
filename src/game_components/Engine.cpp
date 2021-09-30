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

bd2::Engine::Engine(sf::RenderWindow &_window) : window_(_window), exit_(false) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

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

    // clear the list of newly created map elements from the previous turn
    new_objects_.clear();

    // delete pointers to non-existing objects - they are in the beginning of the set,
    // thanks to the special compare operator (bd2::MapElement::Compare())
    while (!simulated_objects_.empty() && simulated_objects_.begin()->expired()) {
        simulated_objects_.erase(simulated_objects_.begin());
    }

    // call simulation() for every simulated object
    // this allows each object to execute its internal operations
    auto elapsed_time = clock_.restart();

    for (auto &weak_object : simulated_objects_) {
        if (auto object = weak_object.lock()) {

            object->simulate(elapsed_time);

            // if an object is Moveable
            if (auto moveable_object = std::dynamic_pointer_cast<Moveable>(object)) {

                switch (moveable_object->getMoveState()) {

                case Moveable::State::PLANNED_MOVE:
                    startObjectMove(moveable_object);
                    break;

                case Moveable::State::ENDED_MOVE:
                    finishObjectMove(moveable_object);
                    break;

                default:
                    break;
                }
            }
        }
    }
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

void bd2::Engine::startObjectMove(const std::shared_ptr<Moveable> &object) {


    // get the move that an object is planning to do
    auto planned_move = object->getPlannedMove();

    if (planned_move) {

        auto position = object->getMapPosition();
        auto target_position = position + planned_move;

        map_[target_position.r][target_position.c] = object;

        object->startMove();
    }
}

void bd2::Engine::finishObjectMove(const std::shared_ptr<Moveable> &object) {

    auto planned_move = object->getPlannedMove();

    if (planned_move) {

        auto position = object->getMapPosition();

        map_[position.r][position.c].remove(object);

        object->finishMove();
    }
}