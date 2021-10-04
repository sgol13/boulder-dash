#ifndef BD2_EXIT_HPP
#define BD2_EXIT_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Exit final : public MapElement {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and its initial position (row and column) */
    Exit(Type _type, const MapCoordinates &_map_position);

    void loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    void openDoor();

  private:
    std::shared_ptr<const sf::Texture> opened_exit_texture_;
};

} // namespace bd2

#endif