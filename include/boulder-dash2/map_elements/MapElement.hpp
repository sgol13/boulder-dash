#ifndef BD2_MAP_ELEMENT_HPP
#define BD2_MAP_ELEMENT_HPP

#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/resources.hpp"

namespace bd2 {

class MapElement : public sf::Sprite {
  public:
    //==========================================================================
    /* TYPES of map elements */
    //==========================================================================
    enum class Type : int {
        Empty = 0,
        Wall = 1,
        Exit = 2,
        Ground = 3,
        Boulder = 4,
        Diamond = 5,
        Butterfly = 6,
        Firefly = 7,
        Player = 8,
        Explosion = 9,
    };

    //==========================================================================
    /** COMPARE functional object - used to compare MapElement objects to form
     * proper layers. Puts expired pointers in the end */
    //==========================================================================
    class Compare {
      public:
        bool operator()(const std::weak_ptr<MapElement> el1,
                        const std::weak_ptr<MapElement> el2);

      private:
        /* Sets an order in which objects should be put (to preserve proper layers)*/
        static const std::vector<Type> type_layers;
    };

    //==========================================================================
    /** Constructor - as an argument takes the real type of the element
     * and ist initial position (row and column) */
    MapElement(Type _type, MapCoordinates _position);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                              int tile_size);

    /* returns the current position on the map {row, column} */
    MapCoordinates getMapPosition() const;

    /* Virtual functions reterning information about type category */
    virtual bool isMoveable() const;

    /* Const member indicating the type of the map element */
    const Type type_;

  private:
    std::shared_ptr<const sf::Texture> static_texture_;

    // current position on the map
    MapCoordinates position_;
};

} // namespace bd2

#endif