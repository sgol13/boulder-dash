// Szymon Golebiowski
// Boulder Dash

#ifndef BD_MAP_ELEMENT_HPP
#define BD_MAP_ELEMENT_HPP

#include "boulder-dash/MapCoordinates.hpp"
#include "boulder-dash/ResourceHandler.hpp"
#include "boulder-dash/defs.hpp"
#include "boulder-dash/resources.hpp"

namespace bd {

class MapElement : public sf::Sprite {
  public:
    //==========================================================================
    /* TYPES of map elements */
    //==========================================================================
    enum class Type : int {
        Empty = 0,
        Wall = 1,
        Ground = 2,
        Diamond = 3,
        Exit = 4,
        Boulder = 5,
        Butterfly = 6,
        Firefly = 7,
        Player = 8,
        Explosion = 9,
    };

    //==========================================================================
    /** COMPARE functional object - used to compare MapElement objects to form
     * proper layers. Puts expired pointers in the end. */
    //==========================================================================
    class Compare {
      public:
        bool operator()(const std::weak_ptr<MapElement> &el1,
                        const std::weak_ptr<MapElement> &el2);

      private:
        /* Sets an order in which objects should be put (to preserve proper layers)*/
        static const std::vector<Type> type_layers;
    };

    //==========================================================================

    MapElement(Type _type, const MapCoordinates &_map_position);

    virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler);

    virtual void simulateAnimation(sf::Time elapsed_time);

    bool isAnimating() const;

    MapCoordinates getMapPosition() const;

    /* Returns the vector containing the current map position or two positions
    if the object is currently in move between two tiles */
    virtual std::vector<MapCoordinates> getAllMapPositions() const;

    /* Const member indicating the type of the map element */
    const Type type_;

  protected:
    virtual void startAnimation(const sf::Texture &texture,
                                sf::Time duration = sf::seconds(0),
                                sf::Time initial_time = sf::seconds(0),
                                bool looped = true);

    std::shared_ptr<const sf::Texture> basic_texture_;

    MapCoordinates map_position_;

  private:
    sf::Time animation_duration_;
    sf::Time animation_time_;

    bool is_animating_;
    bool is_looped_;
};

} // namespace bd

#endif