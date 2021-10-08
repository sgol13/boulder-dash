#ifndef BD2_PLAYER_HPP
#define BD2_PLAYER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Player final : public Moveable {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and its initial position (row and column) */
    Player(Type _type, const MapCoordinates &_map_position);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    void loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    MapCoordinates getPlannedMove(const Map3x3 &map3x3) override;

    void startMove(const MapCoordinates &new_move,
                   sf::Time new_move_duration) override;

    void finishMove() override;

    void reverseMove() override;

    void setPlannedMove(const MapCoordinates &new_planned_move);

    void setTempMoveDuration(sf::Time new_temporary_move_duration);

    void die();

    void startAnimation(const sf::Texture &texture,
                        sf::Time duration = sf::seconds(0),
                        sf::Time initial_time = sf::seconds(0),
                        bool looped = true) override;

    void simulateAnimation(sf::Time elapsed_time) override;

  private:
    /* Starts an animation proper for the current move direction. */
    void startMoveAnimation();

    MapCoordinates planned_move_;

    std::shared_ptr<const sf::Texture> move_left_texture_;
    std::shared_ptr<const sf::Texture> move_right_texture_;
    std::shared_ptr<const sf::Texture> death_texture_;
    std::shared_ptr<const sf::Texture> start_texture_;

    bool previous_move_left_;

    bool dead_;

    sf::Time temporary_move_duration_;
};

} // namespace bd2

#endif