#ifndef BD2_MOVEABLE_HPP
#define BD2_MOVEABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Moveable : virtual public MapElement {
  public:
    // inherit constructors of MapElement
    using MapElement::MapElement;

    virtual bool isMoveable() const override;

  private:
};

} // namespace bd2

#endif
