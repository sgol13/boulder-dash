// Szymon Golebiowski
// Boulder Dash 2, 2021

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

    if (ptr1_ == ptr)
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
// ENGINE
// ==============================================================================

bd2::Engine::Engine(sf::RenderWindow &_window)
    : window_(_window),
      end_game_(false),
      exit_game_(false),
      win_game_(false),
      pause_game_(false),
      player_(nullptr),
      exit_(nullptr),
      picked_diamonds_(0),
      score_(0),
      time_score_(0) {}

void bd2::Engine::initialiseEngine(const std::shared_ptr<const Level> level) {

    // restart all members
    map_.clear();
    new_objects_.clear();
    map_objects_.clear();
    moveable_objects_.clear();
    double_tiles_.clear();
    explosions_.clear();
    sounds_to_play_.clear();
    diamonds_to_add_.clear();
    end_game_ = false;
    exit_game_ = false;
    win_game_ = false;
    player_ = nullptr;
    exit_ = nullptr;
    clock_.restart();
    total_elapsed_time_ = sf::seconds(0);
    turn_elapsed_time_ = sf::seconds(0);
    picked_diamonds_ = 0;
    score_ = 0;
    time_score_ = 0;
    pause_game_ = false;

    // set map dimensions
    map_size_ = level->getMapSize();
    time_limit_ = sf::seconds(static_cast<float>(level->getTimeLimit()));
    required_diamonds_ = level->getRequiredDiamonds();

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

    if (pause_game_) {
        turn_elapsed_time_ = sf::seconds(0);
    }

    if (time_score_ &&
        time_score_transfer_clock_.getElapsedTime() > TIME_SCORE_TRANSFER_DURATION) {

        time_score_transfer_clock_.restart();
        total_elapsed_time_ += sf::seconds(1);
        time_score_--;
        score_++;
    }

    total_elapsed_time_ += turn_elapsed_time_;

    if (total_elapsed_time_ > time_limit_) {
        killObject(player_);
    }

    // clear the list of newly created map elements from the previous turn
    new_objects_.clear();
    sounds_to_play_.clear();

    eraseFromVectorIf<std::shared_ptr<MapElement>>(
        explosions_, [](auto a) { return !a->isAnimating(); });

    eraseFromVectorIf<std::vector<DoubleTile>::iterator>(
        double_tiles_, [](auto a) { return a->size() < 2; });

    eraseFromVectorIf<std::weak_ptr<MapElement>>(map_objects_,
                                                 [](auto a) { return a.expired(); });

    eraseFromVectorIf<std::weak_ptr<Moveable>>(moveable_objects_,
                                               [](auto a) { return a.expired(); });

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

    // check all double tiles if the objects collided
    for (auto &double_tile : double_tiles_) {
        if (double_tile->size() == 2) {

            auto rectangle_1 = (*double_tile)[0]->getGlobalBounds();
            auto rectangle_2 = (*double_tile)[1]->getGlobalBounds();

            if (rectangle_1.intersects(rectangle_2)) {
                collideObjectsInMove((*double_tile)[0], (*double_tile)[1]);
            }
        }
    }

    // remove all objects killed during the current turn
    for (auto &killed_object : killed_objects_) {

        for (auto &map_position : killed_object->getAllMapPositions()) {
            map_[map_position.r][map_position.c].remove(killed_object);
        }

        if (end_game_ == false) {
            switch (killed_object->type_) {
            case MapElement::Type::Player:
                player_->die();
                gameOver();
                break;

            case MapElement::Type::Diamond:
                score_ += DIAMOND_POINTS;
                break;

            case MapElement::Type::Firefly:
                score_ += FIREFLY_POINTS;
                break;

            case MapElement::Type::Butterfly:
                score_ += BUTTERFLY_POINTS;
                break;

            default:
                break;
            }
        }
    }
    killed_objects_.clear();

    // add new diamonds
    for (auto &map_position : diamonds_to_add_) {
        addMapElement(MapElement::Type::Diamond, map_position);
    }
    diamonds_to_add_.clear();
}

void bd2::Engine::finaliseEngine() { score_ += time_score_; }

void bd2::Engine::addMapElement(MapElement::Type type,
                                const MapCoordinates &position) {

    std::shared_ptr<MapElement> new_element = nullptr;

    switch (type) {
    case MapElement::Type::Empty: // EMPTY
        break;

    case MapElement::Type::Wall:      //  WALL
    case MapElement::Type::Ground:    //  GROUND
    case MapElement::Type::Diamond: { //  DIAMOND

        new_element = std::make_shared<MapElement>(type, position);

    } break;

    case MapElement::Type::Exit: { //  EXIT

        auto new_exit = std::make_shared<Exit>(type, position);
        exit_ = new_exit;
        new_element = std::dynamic_pointer_cast<MapElement>(new_exit);

    } break;

    case MapElement::Type::Boulder: { //  BOULDER

        auto new_boulder = std::make_shared<Boulder>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_boulder);

    } break;

    case MapElement::Type::Butterfly: // BUTTERFLY
    case MapElement::Type::Firefly: { // FIREFLY

        auto new_moveable = std::make_shared<Flyable>(type, position);
        new_element = std::dynamic_pointer_cast<MapElement>(new_moveable);

    } break;

    case MapElement::Type::Player: { // PLAYER

        auto new_player = std::make_shared<Player>(type, position);
        player_ = new_player;
        new_element = std::dynamic_pointer_cast<MapElement>(new_player);

    } break;

    case MapElement::Type::Explosion: { // EXPLOSION

        new_element = std::make_shared<MapElement>(type, position);
        explosions_.push_back(new_element);

    } break;
    }

    if (new_element) {

        if (new_element->type_ != MapElement::Type::Explosion) {
            map_[position.r][position.c] = new_element;
        }

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

void bd2::Engine::startObjectMove(const std::shared_ptr<Moveable> &object,
                                  const MapCoordinates &planned_move) {

    if (planned_move) {

        auto position = object->getMapPosition();
        auto target_position = position + planned_move;

        if (checkCollision(object, planned_move)) {

            map_[target_position.r][target_position.c] = object;
            object->startMove(planned_move);
        }
    }
}

void bd2::Engine::finishObjectMove(const std::shared_ptr<Moveable> &object) {

    auto position = object->getMapPosition();
    map_[position.r][position.c].remove(object);
    object->finishMove();
}

void bd2::Engine::killObject(const std::shared_ptr<MapElement> &object,
                             const std::shared_ptr<MapElement> &killer) {

    if (object->type_ == MapElement::Type::Wall ||
        object->type_ == MapElement::Type::Exit) {
        return;
    }

    if (killed_objects_.find(object) != killed_objects_.end()) {
        return;
    }

    killed_objects_.insert(object);

    switch (object->type_) {
    case MapElement::Type::Butterfly: {

        playSound(resources::Sounds::BUTTERFLY_DESTROY);

        auto object_position = object->getMapPosition();
        if (killer) {
            auto killer_position = killer->getMapPosition();
            object_position.c = killer_position.c;
        }

        for (auto &dir : DIR_AROUND4) {

            bool add_diamond = false;
            auto map_position = object_position + dir;

            if (map_[map_position.r][map_position.c].size() == 0) {
                add_diamond = true;

            } else {

                if (auto object_1 = map_[map_position.r][map_position.c][0]) {

                    if (object_1->type_ == MapElement::Type::Ground ||
                        object_1->type_ == MapElement::Type::Boulder ||
                        object_1 == object) {
                        killObject(map_[map_position.r][map_position.c][0]);
                        add_diamond = true;
                    }
                }

                if (auto object_2 = map_[map_position.r][map_position.c][1]) {

                    if (object_2->type_ == MapElement::Type::Boulder ||
                        object_2 == object) {
                        killObject(map_[map_position.r][map_position.c][1]);
                        add_diamond = true;
                    }
                }
            }

            if (add_diamond) {
                diamonds_to_add_.push_back(map_position);
            }
        }
    } break;

    case MapElement::Type::Firefly: {

        playSound(resources::Sounds::EXPLOSION);

        for (auto &dir : DIR_AROUND8) {

            bool add_explosion = false;
            auto map_position = object->getMapPosition() + dir;

            if (auto object_1 = map_[map_position.r][map_position.c][0]) {

                if (object_1->type_ != MapElement::Type::Wall &&
                    object_1->type_ != MapElement::Type::Exit &&
                    object_1->type_ != MapElement::Type::Firefly) {
                    killObject(object_1);
                    add_explosion = true;
                }
            }

            if (auto object_2 = map_[map_position.r][map_position.c][1]) {

                if (object_2->type_ != MapElement::Type::Wall &&
                    object_2->type_ != MapElement::Type::Exit &&
                    object_2->type_ != MapElement::Type::Firefly) {
                    killObject(object_2);
                    add_explosion = true;
                }
            }

            if (add_explosion) {
                addMapElement(MapElement::Type::Explosion, map_position);
            }
        }
    } break;

    default:
        break;
    }
}

bool bd2::Engine::checkCollision(const std::shared_ptr<Moveable> &moveable_object,
                                 const MapCoordinates &move) {

    bool is_move_possible = false;

    auto target_position = moveable_object->getMapPosition() + move;
    DoubleTile &target_tile = map_[target_position.r][target_position.c];

    switch (target_tile.size()) {
    case 0: {
        is_move_possible = true;
    } break;

    case 1: {

        auto rectangle_1 = moveable_object->getGlobalBounds();
        rectangle_1.left += static_cast<float>(move.c);
        rectangle_1.top += static_cast<float>(move.r);
        auto rectangle_2 = target_tile[0]->getGlobalBounds();

        if (rectangle_1.intersects(rectangle_2)) {
            is_move_possible = collideObjects(moveable_object, target_tile[0]);

        } else {
            double_tiles_.push_back(map_[target_position.r].begin() +
                                    target_position.c);
            is_move_possible = true;
        }

    } break;

    case 2: {

        bool possible_1 = collideObjects(moveable_object, target_tile[0]);
        bool possible_2 = collideObjects(moveable_object, target_tile[1]);
        is_move_possible = possible_1 && possible_2;

    } break;

    default:
        break;
    }

    return is_move_possible;
}

bool bd2::Engine::collideObjects(const std::shared_ptr<Moveable> &moveable_object,
                                 const std::shared_ptr<MapElement> &target_object) {

    bool is_move_possible = false;

    switch (moveable_object->type_) {
    case MapElement::Type::Player: {

        auto player_ptr = std::dynamic_pointer_cast<Player>(moveable_object);
        is_move_possible = collidePlayer(player_ptr, target_object);

    } break;

    case MapElement::Type::Boulder: {

        killObject(target_object, moveable_object);
        is_move_possible = true;

    } break;

    case MapElement::Type::Butterfly:
    case MapElement::Type::Firefly: {

        if (target_object->type_ == MapElement::Type::Player) {

            killObject(target_object);
            is_move_possible = true;
        }

    } break;

    default:
        break;
    }

    return is_move_possible;
}

void bd2::Engine::collideObjectsInMove(std::shared_ptr<MapElement> object_1,
                                       std::shared_ptr<MapElement> object_2) {

    // swap if needed
    if (object_1->type_ == MapElement::Type::Boulder &&
        object_2->type_ == MapElement::Type::Player) {

        std::swap(object_1, object_2);
    }

    if (object_1->type_ == MapElement::Type::Boulder &&
        (object_2->type_ == MapElement::Type::Butterfly ||
         object_2->type_ == MapElement::Type::Firefly)) {

        std::swap(object_1, object_2);
    }

    if ((object_1->type_ == MapElement::Type::Butterfly ||
         object_1->type_ == MapElement::Type::Firefly) &&
        object_2->type_ == MapElement::Type::Player) {

        std::swap(object_1, object_2);
    }

    // collide
    switch (object_1->type_) {
    case MapElement::Type::Player: {

        if (object_2->type_ == MapElement::Type::Boulder) {

            if (object_2->getPosition().y < object_1->getPosition().y) {
                killObject(object_1);
            }

        } else if (object_2->type_ == MapElement::Type::Butterfly ||
                   object_2->type_ == MapElement::Type::Firefly) {

            killObject(object_1);
        }

    } break;

    case MapElement::Type::Butterfly:
    case MapElement::Type::Firefly: {

        if (object_2->type_ == MapElement::Type::Boulder) {
            killObject(object_1);

        } else if (object_2->type_ == MapElement::Type::Player) {
            killObject(object_1);
        }

    } break;

    default:
        break;
    }
}

bool bd2::Engine::collidePlayer(const std::shared_ptr<Player> &player,
                                const std::shared_ptr<MapElement> &target_object) {

    bool is_move_possible = false;

    switch (target_object->type_) {
    case MapElement::Type::Ground: {

        playSound(resources::Sounds::GROUND_DESTROY);
        killObject(target_object);
        is_move_possible = true;

    } break;

    case MapElement::Type::Diamond: {

        playSound(resources::Sounds::DIAMOND);
        killObject(target_object);
        picked_diamonds_++;
        if (picked_diamonds_ == required_diamonds_) {
            exit_->openDoor();
        }

        is_move_possible = true;

    } break;

    case MapElement::Type::Exit: {

        if (exit_->isOpen()) {
            is_move_possible = true;
            win_game_ = true;
            gameOver();
        }

    } break;

    case MapElement::Type::Boulder: {

        auto boulder_ptr = std::dynamic_pointer_cast<Boulder>(target_object);

        auto position = player->getMapPosition();
        auto move = target_object->getMapPosition() - position;

        auto player_pos_y = player->getPosition().y;
        auto boulder_pos_y = boulder_ptr->getPosition().y;

        if ((move == DIR_LEFT || move == DIR_RIGHT) && player_pos_y < boulder_pos_y) {
            is_move_possible = true;

        } else if (player_pos_y == boulder_pos_y) {

            if (move == DIR_LEFT && map_[position.r][position.c - 2].size() == 0) {

                boulder_ptr->pushSide(DIR_LEFT);
                player->setTempMoveDuration(BOULDER_MOVE_DURATION);
                is_move_possible = true;

            } else if (move == DIR_RIGHT &&
                       map_[position.r][position.c + 2].size() == 0) {

                boulder_ptr->pushSide(DIR_RIGHT);
                player->setTempMoveDuration(BOULDER_MOVE_DURATION);
                is_move_possible = true;
            }
        }

        if (is_move_possible) {
            playSound(resources::Sounds::BOULDER_PUSH);
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

void bd2::Engine::playSound(resources::Sounds sound) {
    sounds_to_play_.push_back(sound);
}

void bd2::Engine::gameOver() {

    end_game_ = true;
    if (win_game_) {
        playSound(resources::Sounds::GAME_WIN);
        time_score_ +=
            static_cast<int>((time_limit_ - total_elapsed_time_).asSeconds()) *
            SECOND_LEFT_POINTS;

    } else {
        playSound(resources::Sounds::GAME_OVER);
    }
}