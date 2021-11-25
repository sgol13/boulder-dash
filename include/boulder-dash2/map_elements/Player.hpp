// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_PLAYER_HPP
#define BD2_PLAYER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd {

class Player final : public Moveable {
  public:
    Player(Type _type, const MapCoordinates &_map_position);

    void loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;


    void startMove(const MapCoordinates &new_move,
                   sf::Time new_move_duration) override;

    void finishMove() override;

    void reverseMove() override;

    void simulateAnimation(sf::Time elapsed_time) override;

    MapCoordinates getPlannedMove(const Map3x3 &map3x3) override;

    /* Passes the next move (used by Input module) */
    void setPlannedMove(const MapCoordinates &new_planned_move);

    /* Temporarily changes move duration (until the end of the current move) */
    void setTempMoveDuration(sf::Time new_temporary_move_duration);

    /* Initiates dying animation */
    void die();

  private:
    void startAnimation(const sf::Texture &texture,
                        sf::Time duration = sf::seconds(0),
                        sf::Time initial_time = sf::seconds(0),
                        bool looped = true) override;

    /* Starts an animation proper for the current move direction. */
    void startMoveAnimation();


    std::shared_ptr<const sf::Texture> move_left_texture_;
    std::shared_ptr<const sf::Texture> move_right_texture_;
    std::shared_ptr<const sf::Texture> death_texture_;
    std::shared_ptr<const sf::Texture> start_texture_;

    MapCoordinates planned_move_;

    bool previous_move_left_;
    bool dead_;

    sf::Time temporary_move_duration_;
};

} // namespace bd

#endif