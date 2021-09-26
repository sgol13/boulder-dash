#include "boulder-dash2/Level.hpp"

bool bd2::Level::loadFromFile(const std::string &filename) {

    bool correct = true;

    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {

        // read level name
        getline(file, name_);

        // read time limit and required diamonds
        file >> time_limit_ >> required_diamonds_;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // read level map as strings
        std::string row;
        std::vector<std::string> rows;

        getline(file, row);
        n_columns_ = row.size();

        while (row.size() == n_columns_ && row.front() != ';') {
            rows.push_back(row);
            getline(file, row);
        }

        n_rows_ = rows.size();

        // interpret level map and check if it's correct
        if (!interpretMap(rows))
            correct = false;

        if (!file.good())
            correct = false;

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

int bd2::Level::getNumRows() const { return n_rows_; }

int bd2::Level::getNumColumns() const { return n_columns_; }

std::string bd2::Level::getName() const { return name_; }

int bd2::Level::getTimeLimit() const { return time_limit_; }

int bd2::Level::getRequiredDiamonds() const { return required_diamonds_; }

const std::vector<std::vector<bd2::MapElement::Type>> &bd2::Level::getMap() const {
    return map_;
}

bool bd2::Level::interpretMap(const std::vector<std::string> &rows) {

    if (rows.size() < 2)
        return false;

    // check if all the characters are '0' - '8'
    for (const auto &row : rows)
        for (const auto &c : row)
            if (c < '0' || c > '8')
                return false;



    // check if the map is surrounded by walls (or an exit tile)
    for (const auto &row : rows) {

        if (row.size() < 2)
            return false;

        if (!isBorderTile(row.front()) || !isBorderTile(row.back()))
            return false;
    }

    if (rows.front().size() != n_columns_ || rows.back().size() != n_columns_)
        return false;

    for (int i = 0; i < n_columns_; i++) {

        if (!isBorderTile(rows.front()[i]) || !isBorderTile(rows.back()[i]))
            return false;
    }

    // interpret rows as a map
    for (const auto &row : rows) {

        map_.push_back(std::vector<MapElement::Type>());

        for (const auto &c : row) {
            map_.back().push_back(MapElement::Type(c - '0'));
        }
    }

    return true;
}

/* Checks if a given char is a border tile = is a wall or an exit */
bool bd2::Level::isBorderTile(char c) { return c == '1' || c == '2'; }