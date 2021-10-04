#ifndef BD2_PLAYER_HPP
#define BD2_PLAYER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Player final : public Moveable {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and its initial position (row and column) */
    Player(Type _type, MapCoordinates _position);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    void loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    MapCoordinates getPlannedMove() const override;

    void startMove(MapCoordinates new_move) override;

    void finishMove() override;

    void reverseMove() override;

    void setPlannedMove(MapCoordinates new_planned_move);

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