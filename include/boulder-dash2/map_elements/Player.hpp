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

    MapCoordinates getPlannedMove(const Map3x3 &map3x3,
                                  sf::Time elapsed_time) override;

    void startMove(const MapCoordinates &new_move) override;

    void finishMove() override;

    void reverseMove() override;

    void setPlannedMove(const MapCoordinates &new_planned_move);

  private:
    /* Starts an animation proper for the current move direction. */
    void startMoveAnimation();

    MapCoordinates planned_move_;

    std::shared_ptr<const sf::Texture> move_left_texture_;
    std::shared_ptr<const sf::Texture> move_right_texture_;

    bool previous_move_left_;
};

} // namespace bd2

#endif