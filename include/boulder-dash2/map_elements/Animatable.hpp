#ifndef BD2_ANIMATABLE_HPP
#define BD2_ANIMATABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Animatable : virtual public MapElement {
  public:
    Animatable(Type _type, MapCoordinates _position);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                              unsigned int tile_size) override = 0;

    /* This function is called once a turn to let an object execute its operations */
    virtual void simulate(sf::Time elapsed_time) override = 0;

  protected:
    void simulateAnimation(sf::Time elapsed_time);

    void startAnimation(std::shared_ptr<const sf::Texture> animation_texture,
                        sf::Time duration,
                        sf::Time initial_time = sf::milliseconds(0));

    bool isAnimating() const;

    unsigned int tile_size_;

  private:
    bool is_animating_;

    sf::Time animation_time_;

    sf::Time animation_duration_;
};

} // namespace bd2

#endif
