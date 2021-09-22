#ifndef BD2_LEVEL_HPP
#define BD2_LEVEL_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Level {
  public:
    /* Loads a level from a given file. Returns true if loaded correctly */
    bool loadFromFile(const std::string &filename);

  private:
    /* Interprets a vector of string as a level map. Returns true of the map is
     * correct or false otherwise */
    bool interpretMap(const std::vector<std::string> &rows);

    /* Checks if a given char is a border tile = is a wall or an exit */
    bool isBorderTile(char c);

    int n_rows_;
    int n_columns_;
    int time_limit_;
    int required_diamonds_;

    std::string name_;

    std::vector<std::vector<map_elements::Type>> tiles_;
};

} // namespace bd2

#endif