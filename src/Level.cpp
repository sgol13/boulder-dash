// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/Level.hpp"

bool bd2::Level::loadFromFile(const std::string &filename) {

    bool correct = true;
    filename_ = filename;

    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {

        // read time limit and required diamonds
        file >> time_limit_ >> required_diamonds_;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // read level map as strings
        std::string row;
        std::vector<std::string> rows;

        getline(file, row);
        map_size_.c = static_cast<int>(row.size());

        while (static_cast<int>(row.size()) == map_size_.c && map_size_.c > 0 &&
               row.front() != ';') {
            rows.push_back(row);
            getline(file, row);
        }

        map_size_.r = static_cast<int>(rows.size());

        // interpret level map and check if it's correct
        if (map_size_.r > 2 && map_size_.c > 2) {

            if (!interpretMap(rows)) {
                correct = false;
            }

        } else {
            correct = false;
        }

        if (!file.good() || row.size() < 2) {
            correct = false;
        }

        if (correct) {

            // read level results
            std::istringstream records_stream(row.substr(1));
            std::string name;
            int score;
            for (int i = 0; i < TOP_RESULTS_NUM; i++) {

                std::string record;
                getline(records_stream, record, ';');
                record.push_back(' ');

                std::istringstream record_stream(record);
                record_stream >> name >> score;
                if (record_stream.good()) {
                    ranking_[i] = std::make_pair(name, score);

                } else {
                    ranking_[i] = std::make_pair("", 0);
                }
            }
        }

        // print error information
        if (!correct) {
            std::cerr << "Failed to load level file \"" << filename << "\". ";
            std::cerr << "Reason: incorrect file format" << std::endl;
        }

        file.close();

    } else {
        std::cerr << "Failed to load level file \"" << filename << "\". ";
        std::cerr << "Reason: Unable to open file" << std::endl;

        correct = false;
    }

    return correct;
}

bd2::MapCoordinates bd2::Level::getMapSize() const { return map_size_; }

int bd2::Level::getTimeLimit() const { return time_limit_; }

int bd2::Level::getRequiredDiamonds() const { return required_diamonds_; }

const std::vector<std::vector<bd2::MapElement::Type>> &bd2::Level::getMap() const {
    return map_;
}

void bd2::Level::updateRankingInFile() {

    std::fstream file(filename_, std::ios::in | std::ios::out);

    if (file.is_open()) {

        for (int c; c != EOF && c != ';';) {
            c = file.get();
        }

        for (auto &record : ranking_) {

            if (record.second > 0) {
                file << record.first << " " << record.second;
            }
            file << ";";
        }

        file << std::endl;
        file.close();
    }
}

bool bd2::Level::interpretMap(const std::vector<std::string> &rows) {

    if (rows.size() < 2)
        return false;

    /** check if all the characters are '0' - '8' ('9' - explostion, cannot exist
     * at the beginning of the game)*/
    for (const auto &row : rows)
        for (const auto &c : row)
            if (c < '0' || c > '8')
                return false;

    if (static_cast<int>(rows.front().size()) != map_size_.c ||
        static_cast<int>(rows.back().size()) != map_size_.c)
        return false;



    // count players and exists to check if there is only one of one type
    int players_counter = 0;
    int exits_counter = 0;

    // interpret rows as a map
    for (const auto &row : rows) {

        map_.push_back(std::vector<MapElement::Type>());

        for (const auto &c : row) {

            map_.back().push_back(MapElement::Type(c - '0'));

            if (map_.back().back() == MapElement::Type::Exit)
                exits_counter++;
            else if (map_.back().back() == MapElement::Type::Player)
                players_counter++;
        }
    }

    /* Check if there are exactly one player and one exit */
    if (players_counter != 1 || exits_counter != 1) {
        map_.clear();
        return false;
    }

    // check if the map is surrounded by walls (or an exit tile)
    for (const auto &row : map_) {

        if (!isBorderTile(row.front()) || !isBorderTile(row.back())) {
            map_.clear();
            return false;
        }
    }

    for (int i = 0; i < map_size_.c; i++) {

        if (!isBorderTile(map_.front()[i]) || !isBorderTile(map_.back()[i])) {
            map_.clear();
            return false;
        }
    }

    return true;
}

bool bd2::Level::isBorderTile(MapElement::Type tile_type) {
    return tile_type == MapElement::Type::Wall || tile_type == MapElement::Type::Exit;
}