#ifndef BD2_MAP_ELEMENTS_HPP
#define BD2_MAP_ELEMENTS_HPP

#include "boulder-dash2/defs.hpp"

namespace bd2 {

class MapElement : public sf::Sprite {
  public:
    /* Types of map elements */
    enum class Type : int {
        Empty = 0,
        Wall = 1,
        Exit = 2,
        Ground = 3,
        Boulder = 4,
        Diamond = 5,
        Butterfly = 6,
        Firefly = 7,
        Player = 8
    };

    /* Functional object - used to compare MapElement objects to form proper layers.
      Puts expired pointers in the beginning */
    class Compare {
      public:
        bool operator()(const std::weak_ptr<MapElement> el1,
                        const std::weak_ptr<MapElement> el2);

      private:
        /* Sets an order in which objects should be put (to preserve proper layers)*/
        static const std::vector<Type> type_layers;
    };

    /* Constructor - passes the real type of the element */
    MapElement(Type _type);

    /* Const member indicating the type of the map element */
    const Type type_;

  private:
    std::shared_ptr<sf::Texture> static_texture_;
};

} // namespace bd2

#endif