#ifndef BD2_PLAYER_HPP
#define BD2_PLAYER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Animatable.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Player final : public Moveable, public Animatable {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and its initial position (row and column) */
    Player(Type _type, MapCoordinates _position);

    /* This function is called once a turn to let the object execute its operations */
    virtual void simulate(sf::Time elapsed_time) override;

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                              unsigned int tile_size) override;

    /** Passes information about the current position of arrow keys. Should be
     * used once a turn to let the player plan the moves */
    void passArrowKeysPosition(MapCoordinates arrow_keys);

  private:
    MapCoordinates arrow_keys_;

    std::vector<std::shared_ptr<const sf::Texture>> standing_textures_;
    std::shared_ptr<const sf::Texture> move_left_texture_;
    std::shared_ptr<const sf::Texture> move_right_texture_;

    bool previous_left_;
};

} // namespace bd2

#endif