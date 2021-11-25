// Szymon Golebiowski
// Boulder Dash

#ifndef BD_EXIT_HPP
#define BD_EXIT_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/map_elements/MapElement.hpp"

namespace bd {

class Exit final : public MapElement {
  public:
    Exit(Type _type, const MapCoordinates &_map_position);

    void loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    void openDoor();

    bool isOpen();

  private:
    std::shared_ptr<const sf::Texture> opened_exit_texture_;

    bool is_open;
};

} // namespace bd

#endif