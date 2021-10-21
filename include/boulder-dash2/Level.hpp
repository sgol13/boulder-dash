// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_LEVEL_HPP
#define BD2_LEVEL_HPP

#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Level {
  public:
    bool loadFromFile(const std::string &filename);

    MapCoordinates getMapSize() const;

    int getTimeLimit() const;

    int getRequiredDiamonds() const;

    const std::vector<std::vector<MapElement::Type>> &getMap() const;

    /* Updates score ranking in the file from which the level was loaded */
    void updateRankingInFile();

    std::array<std::pair<std::string, int>, TOP_RESULTS_NUM> ranking_;

  private:
    bool interpretMap(const std::vector<std::string> &rows);

    /* Check if the tile is an exit or a wall */
    bool isBorderTile(MapElement::Type tile_type);

    std::vector<std::vector<MapElement::Type>> map_;
    MapCoordinates map_size_;

    int time_limit_;
    int required_diamonds_;

    std::string filename_;
};

} // namespace bd2

#endif