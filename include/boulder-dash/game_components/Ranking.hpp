// Szymon Golebiowski
// Boulder Dash

#ifndef BD_RANKING_HPP
#define BD_RANKING_HPP

#include "boulder-dash/Level.hpp"
#include "boulder-dash/ResourceHandler.hpp"
#include "boulder-dash/defs.hpp"

namespace bd {

class Ranking {
  public:
    Ranking(sf::RenderWindow &_window,
            const ResourceHandler<sf::Font> &_fonts_handler);

    void open(Level &level, int level_index, int score);

  private:
    void initialiseLevelRanking(Level &level, int level_index, int score);

    void finaliseLevelRanking(Level &level);

    void handleEvents();

    sf::View getRankingView();

    sf::RenderWindow &window_;
    const ResourceHandler<sf::Font> &fonts_handler_;

    bool exit_ranking_;

    sf::Text level_name_text_;
    sf::Text top5_info_text_;
    sf::Text press_enter_info_text_;
    std::array<sf::Text, TOP_RESULTS_NUM> score_texts_;
    std::array<sf::Text, TOP_RESULTS_NUM> nickname_texts_;

    bool started_typing_;
    bool typing_nickname_;
    int ranking_index_;
    std::string typed_string_;

    sf::Clock blinking_nickname_clock_;
    sf::Clock ranking_initial_block_clock_;
};

} // namespace bd

#endif