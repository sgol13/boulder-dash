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

    if (ptr0_ == ptr) {
        return ptr0_;
    }

    if (ptr1_ == ptr) {
        return ptr1_;
    }

    return const_cast<std::shared_ptr<MapElement> &>(empty_ptr);
}

std::shared_ptr<bd2::MapElement> &bd2::Engine::DoubleTile::operator[](int n) {

    if (n == 0) {
        return ptr0_;
    }

    if (n == 1) {
        return ptr1_;
    }

    return const_cast<std::shared_ptr<MapElement> &>(empty_ptr);
}

int bd2::Engine::DoubleTile::size() const {

    if (ptr0_ == nullptr) {
        return 0;
    }

    if (ptr1_ == nullptr) {
        return 1;
    }

    return 2;
}

void bd2::Engine::DoubleTile::remove(int n) {

    if (n == 0) {
        ptr0_ = ptr1_;
        ptr1_ = nullptr;

    } else if (n == 1) {
        ptr1_ = nullptr;
    }
}

void bd2::Engine::DoubleTile::remove(const std::shared_ptr<MapElement> &ptr_remove) {

    if (ptr_remove == ptr0_) {
        remove(0);

    } else if (ptr_remove == ptr1_) {
        remove(1);
    }
}

void bd2::Engine::DoubleTile::remove(const MapElement &object_remove) {

    if (&object_remove == ptr0_.get()) {
        remove(0);

    } else if (&object_remove == ptr1_.get()) {
        remove(1);
    }
}

bool bd2::Engine::DoubleTile::add(const std::shared_ptr<MapElement> &ptr_add) {

    if (ptr0_ == nullptr) {
        ptr0_ = ptr_add;

    } else if (ptr1_ == nullptr) {
        ptr1_ = ptr_add;

    } else {
        return false;
    }

    return true;
}

bd2::Engine::DoubleTile::operator std::shared_ptr<MapElement> &() { return ptr0_; }

const std::shared_ptr<bd2::MapElement> bd2::Engine::DoubleTile::empty_ptr = nullptr;

// ==============================================================================
bool bd2::Engine::MapIteratorCompare::operator()(
    const std::vector<DoubleTile>::iterator &it1,
    const std::vector<DoubleTile>::iterator &it2) {
    return it1->size() > it2->size();
}
// ==============================================================================
// ENGINE
// ==============================================================================

bd2::Engine::Engine(sf::RenderWindow &_window) : window_(_window) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

    map_.clear();
    new_objects_.clear();
    map_objects_.clear();
    moveable_objects_.clear();
    end_game_ = false;
    player_ = nullptr;
    exit_ = nullptr;
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

    // simulate and finish moves
    for (auto &weak_moveable_object : moveable_objects_) {

        auto moveable_object = weak_moveable_object.lock();

        moveable_object->simulateMovement(turn_elapsed_time_);

        if (moveable_object->getMovePhase() == Moveable::MovePhase::ENDED_MOVE) {
            finishObjectMove(*moveable_object);
        }
    }

    // start new moves
    for (auto &weak_moveable_object : moveable_objects_) {

        auto moveable_object = weak_moveable_object.lock();

        if (moveable_object->getMovePhase() == Moveable::MovePhase::STANDING) {

            auto map3x3 = getMap3x3(moveable_object->getMapPosition());
            auto planned_move = moveable_object->getPlannedMove(map3x3);

            startObjectMove(*moveable_object, planned_move);
        }
    }

    std::sort(map_objects_.begin(), map_objects_.end(), MapElement::Compare());

    while (!map_objects_.empty() && map_objects_.back().expired()) {
        map_objects_.pop_back();
    }

    std::sort(moveable_objects_.begin(), moveable_objects_.end(),
              MapElement::Compare());

    while (!moveable_objects_.empty() && moveable_objects_.back().expired()) {
        moveable_objects_.pop_back();
    }
}

void bd2::Engine::addMapElement(MapElement::Type type,
                                const MapCoordinates &position) {

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

        auto new_exit = std::make_shared<Exit>(type, position);
        exit_ = new_exit;
        new_element = std::dynamic_pointer_cast<MapElement>(new_exit);

    } break;

    case MapElement::Type::Boulder: { // 5 - BOULDER

        auto new_boulder = std::make_shared<Boulder>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_boulder);

    } break;

    case MapElement::Type::Butterfly: // 6 - BUTTERFLY
    case MapElement::Type::Firefly: { // 7 - FIREFLY

        auto new_moveable = std::make_shared<Flyable>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_moveable);

    } break;

    case MapElement::Type::Player: { // 8 - PLAYER

        auto new_player = std::make_shared<Player>(type, position);
        player_ = new_player;
        new_element = std::dynamic_pointer_cast<MapElement>(new_player);

    } break;

    case MapElement::Type::Explosion: { // 9 - EXPLOSION
    } break;
    }

    if (new_element) {

        map_[position.r][position.c] = new_element;
        map_objects_.push_back(new_element);

        if (auto new_moveable = std::dynamic_pointer_cast<Moveable>(new_element)) {
            moveable_objects_.push_back(new_moveable);
        }

        // add a new element to the list of elements created during the current turn
        new_objects_.push_back(new_element);
    }
}

bd2::Moveable::Map3x3 bd2::Engine::getMap3x3(const MapCoordinates &center) {

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

void bd2::Engine::startObjectMove(Moveable &object,
                                  const MapCoordinates &planned_move) {

    if (planned_move) {

        auto position = object.getMapPosition();
        auto target_position = position + planned_move;

        if (checkCollision(object, planned_move)) {

            map_[target_position.r][target_position.c] =
                map_[position.r][position.c][0];
            object.startMove(planned_move);
        }
    }
}

void bd2::Engine::finishObjectMove(Moveable &object) {

    auto position = object.getMapPosition();
    map_[position.r][position.c].remove(object);
    object.finishMove();
}

void bd2::Engine::killObject(MapElement &object) {

    if (object.type_ == MapElement::Type::Player) {
        gameOver();
    }

    for (auto &map_position : object.getAllMapPositions()) {
        map_[map_position.r][map_position.c].remove(object);
    }
}

void bd2::Engine::gameOver() { std::cout << "GAME OVER\n"; }

bool bd2::Engine::checkCollision(Moveable &moveable_object,
                                 const MapCoordinates &move) {

    bool is_move_possible = false;

    auto target_position = moveable_object.getMapPosition() + move;
    DoubleTile &target_tile = map_[target_position.r][target_position.c];

    switch (target_tile.size()) {
    case 0: {
        is_move_possible = true;
    } break;

    case 1: {

        auto rectangle_1 = moveable_object.getGlobalBounds();
        rectangle_1.left += static_cast<float>(move.c);
        rectangle_1.top += static_cast<float>(move.r);
        auto rectangle_2 = target_tile[0]->getGlobalBounds();

        /* std::cout << rectangle_1.left << " " << rectangle_1.top << " "
                  << rectangle_1.width << " " << rectangle_1.height << "\n";

        std::cout << rectangle_2.left << " " << rectangle_2.top << " "
                  << rectangle_2.width << " " << rectangle_2.height << "\n"; */

        if (rectangle_1.intersects(rectangle_2)) {
            is_move_possible = collideObjects(moveable_object, *target_tile[0]);

        } else {
            double_tiles_.push_back(map_[target_position.r].begin() +
                                    target_position.c);
            is_move_possible = true;
        }

    } break;

    case 2: {

        bool possible_1 = collideObjects(moveable_object, *target_tile[0]);
        bool possible_2 = collideObjects(moveable_object, *target_tile[1]);
        is_move_possible = possible_1 && possible_2;

    } break;

    default:
        break;
    }

    return is_move_possible;
}

bool bd2::Engine::collideObjects(Moveable &moveable_object,
                                 MapElement &target_object) {

    bool is_move_possible = false;

    switch (moveable_object.type_) {
    case MapElement::Type::Player: {

        Player &player_reference = dynamic_cast<Player &>(moveable_object);
        is_move_possible = collidePlayer(player_reference, target_object);

    } break;

    case MapElement::Type::Boulder: {

        Boulder &boulder_reference = dynamic_cast<Boulder &>(moveable_object);
        is_move_possible = collideBoulder(boulder_reference, target_object);

    } break;

    case MapElement::Type::Butterfly:
    case MapElement::Type::Firefly: {

        Flyable &flyable_reference = dynamic_cast<Flyable &>(moveable_object);
        is_move_possible = collideFlyable(flyable_reference, target_object);

    } break;

    default:
        break;
    }

    return is_move_possible;
}

bool bd2::Engine::collidePlayer(Player &player, MapElement &target_object) {

    bool is_move_possible = false;
    std::cout << "PLAYER\n";

    switch (target_object.type_) {
    case MapElement::Type::Ground: {

        killObject(target_object);
        is_move_possible = true;

    } break;

    case MapElement::Type::Boulder: {

        Boulder &boulder_reference = dynamic_cast<Boulder &>(target_object);

        auto position = player.getMapPosition();
        auto move = target_object.getMapPosition() - player.getMapPosition();

        auto player_pos_y = player.getPosition().y;
        auto boulder_pos_y = boulder_reference.getPosition().y;

        if ((move == DIR_LEFT || move == DIR_RIGHT) && player_pos_y < boulder_pos_y) {
            is_move_possible = true;

        } else if (player_pos_y == boulder_pos_y) {

            if (move == DIR_LEFT && !map_[position.r][position.c - 2].size()) {

                boulder_reference.pushSide(DIR_LEFT);
                player.setTempMoveDuration(BOULDER_MOVE_DURATION);
                is_move_possible = true;

            } else if (move == DIR_RIGHT &&
                       !map_[position.r][position.c + 2].size()) {

                boulder_reference.pushSide(DIR_RIGHT);
                player.setTempMoveDuration(BOULDER_MOVE_DURATION);
                is_move_possible = true;
            }
        }
    } break;

    case MapElement::Type::Butterfly:
    case MapElement::Type::Firefly: {
        killObject(player);
    } break;

    default:
        break;
    }

    return is_move_possible;
}

bool bd2::Engine::collideBoulder(Boulder &boulder, MapElement &target_object) {

    (void)boulder;
    killObject(target_object);
    std::cout << "BOULDER\n";

    return true;
}

bool bd2::Engine::collideFlyable(Flyable &flyable, MapElement &target_object) {

    (void)flyable;
    (void)target_object;
    std::cout << "FLYABLE\n";

    if (target_object.type_ == MapElement::Type::Player) {

        killObject(target_object);
        return true;
    }

    return false;
}