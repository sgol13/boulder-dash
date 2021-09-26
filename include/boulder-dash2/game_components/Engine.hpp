#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Engine {
  public:
    /* Constructor */
    Engine(sf::RenderWindow &_window,
           const ResourceHandler<sf::Texture> &_textures_handler);

  protected:
    /* Processes all game engine operations */
    void processEngineOperations();

    /* Creates an initial state of the map on the basis of level object */
    void initialiseLevel(const std::shared_ptr<const Level> level);


    sf::RenderWindow &window_;
    bool exit_;

    std::set<std::weak_ptr<MapElement>, MapElement::Compare> drawable_objects_;

  private:
    /* Creates a new map element of given type on [pos_i, pos_j] position */
    void addMapElement(MapElement::Type type, int pos_i, int pos_j);

    // map
    std::vector<std::vector<std::shared_ptr<MapElement>>> map_;
    int rows_num_;
    int columns_num_;

    // objects' sets

    // resource handlers
    const ResourceHandler<sf::Texture> &textures_handler_;
};

} // namespace bd2

#endif