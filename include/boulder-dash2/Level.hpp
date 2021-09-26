#ifndef BD2_LEVEL_HPP
#define BD2_LEVEL_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Level {
  public:
    /* Loads a level from a given file. Returns true if loaded correctly */
    bool loadFromFile(const std::string &filename);

    /* Returns the number of rows */
    int getNumRows() const;

    /* Returns the number of columns */
    int getNumColumns() const;

    /* Returns the level's name */
    std::string getName() const;

    /* Returns the time limit for the level */
    int getTimeLimit() const;

    /* Returns the required number of diamonds for this level */
    int getRequiredDiamonds() const;

    /* Returns a const reference for the level map */
    const std::vector<std::vector<MapElement::Type>> &getMap() const;

  private:
    /* Interprets a vector of string as a level map. Returns true of the map is
     * correct or false otherwise */
    bool interpretMap(const std::vector<std::string> &rows);

    /* Checks if a given char is a border tile = is a wall or an exit */
    bool isBorderTile(char c);

    int rows_num_;
    int columns_num_;
    int time_limit_;
    int required_diamonds_;

    std::string name_;

    std::vector<std::vector<MapElement::Type>> map_;
};

} // namespace bd2

#endif