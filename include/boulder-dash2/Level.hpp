#ifndef BD2_LEVEL_HPP
#define BD2_LEVEL_HPP

#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Level {
  public:
    /* Loads a level from a given file. Returns true if loaded correctly */
    bool loadFromFile(const std::string &filename);

    /** Returns the std::pair indicating sizes of the level map:
     * {number of rows, number of columns}*/
    MapCoordinates getMapSize() const;

    /* Returns the time limit for the level */
    int getTimeLimit() const;

    /* Returns the required number of diamonds for this level */
    int getRequiredDiamonds() const;

    /* Returns a const reference for the level map */
    const std::vector<std::vector<MapElement::Type>> &getMap() const;

    std::array<std::pair<std::string, int>, TOP_RESULTS_NUM> ranking_;

    void updateRankingInFile();

  private:
    /* Interprets a vector of string as a level map. Returns true of the map is
     * correct or false otherwise */
    bool interpretMap(const std::vector<std::string> &rows);

    /* Checks if a given char is a border tile = is a wall or an exit */
    bool isBorderTile(MapElement::Type tile_type);


    std::vector<std::vector<MapElement::Type>> map_;
    MapCoordinates map_size_;

    int time_limit_;
    int required_diamonds_;

    std::string filename_;
};

} // namespace bd2

#endif