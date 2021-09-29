#ifndef BD2_PLAYER_HPP
#define BD2_PLAYER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Player final : public Moveable {
  public:
    // inherit constructors of Moveable
    using Moveable::Moveable;

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                              unsigned int tile_size) override;

  private:
};

} // namespace bd2

#endif