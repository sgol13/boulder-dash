#include "boulder-dash2/game_components/Ranking.hpp"

bd2::Ranking::Ranking(sf::RenderWindow &_window,
                      const ResourceHandler<sf::Font> &_fonts_handler)
    : window_(_window), fonts_handler_(_fonts_handler), exit_ranking_(false),
      started_typing_(false), typing_nickname_(false) {

    // temp
    rect.setSize(sf::Vector2f(RANKING_WIDTH - 6, RANKING_HEIGHT - 6));
    rect.setPosition(3, 3);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(3);
    // temp

    sf::Vector2f text_position;
    level_name_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    level_name_text_.setFillColor(GREY_COLOR);
    level_name_text_.setCharacterSize(RANKING_LEVEL_NAME_FONT_SIZE);
    text_position.x = 0;
    text_position.y = RANKING_ABOVE_LEVEL_NAME_GAP_HEIGHT;
    level_name_text_.setPosition(text_position);

    text_position.x = RANKING_SCORE_TEXTS_POSITION_X;
    text_position.y += RANKING_BELOW_LEVEL_NAME_GAP_HEIGHT;

    for (auto &score_text : score_texts_) {

        score_text.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
        score_text.setFillColor(GREY_COLOR);
        score_text.setCharacterSize(RANKING_SCORES_TEXTS_FONT_SIZE);

        score_text.setPosition(text_position);
        text_position.y +=
            RANKING_SCORES_TEXTS_FONT_SIZE + RANKING_BETWEEN_SCORES_TEXT_GAP_HEIGHT;
    }

    for (auto &nickname_text : nickname_texts_) {

        nickname_text.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
        nickname_text.setFillColor(GREY_COLOR);
        nickname_text.setCharacterSize(RANKING_SCORES_TEXTS_FONT_SIZE);
    }
}

void bd2::Ranking::open(Level &level, int level_index, int score) {

    exit_ranking_ = false;

    initialiseLevelRanking(level, level_index, score);

    while (window_.isOpen() && !exit_ranking_) {

        handleEvents();

        if (typing_nickname_) {
            nickname_texts_[ranking_index_].setString(typed_string_);

            if (blinking_nickname_clock_.getElapsedTime() >
                BLINKING_NICKNAME_CYCLE_DURATION) {

                blinking_nickname_clock_.restart();

                if (nickname_texts_[ranking_index_].getFillColor() == GREY_COLOR) {
                    nickname_texts_[ranking_index_].setFillColor(sf::Color::Cyan);

                } else {
                    nickname_texts_[ranking_index_].setFillColor(GREY_COLOR);
                }
            }
        }

        window_.clear(sf::Color::Black);
        window_.setView(getRankingView());

        window_.draw(rect);
        window_.draw(level_name_text_);

        for (auto &score_text : score_texts_) {
            window_.draw(score_text);
        }

        for (auto &nickname_text : nickname_texts_) {
            window_.draw(nickname_text);
        }

        window_.display();
    }

    finaliseLevelRanking(level);
}

void bd2::Ranking::handleEvents() {

    sf::Event event;
    while (window_.pollEvent(event)) {

        switch (event.type) {
        case sf::Event::Closed: // exit the game
            exit_ranking_ = true;
            window_.close();
            break;

        case sf::Event::KeyPressed:

            if (event.key.code == sf::Keyboard::Return) {

                nickname_texts_[ranking_index_].setFillColor(GREY_COLOR);
                exit_ranking_ = true;
            }

            break;

        case sf::Event::TextEntered:

            if (window_.hasFocus()) {

                if (event.text.unicode >= 33 && event.text.unicode <= 126) {

                    if (!started_typing_) {
                        started_typing_ = true;
                        typed_string_.clear();
                    }

                    if (typed_string_.size() < NICKNAME_LENGTH_LIMIT) {
                        typed_string_.push_back(
                            static_cast<char>(event.text.unicode));
                    }

                } else if (event.text.unicode == 8) { // backspace

                    if (!typed_string_.empty()) {
                        typed_string_.pop_back();
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}

sf::View bd2::Ranking::getRankingView() {

    sf::View view;
    view.reset(sf::FloatRect(0, 0, RANKING_WIDTH, RANKING_HEIGHT));

    sf::FloatRect viewport;
    auto window_size = window_.getSize();

    if (window_size.y * RANKING_WIDTH < window_size.x * RANKING_HEIGHT) {

        viewport.top = 0.f;
        viewport.height = 1.f;
        float margin =
            (static_cast<float>(window_size.x) -
             static_cast<float>(RANKING_WIDTH) * static_cast<float>(window_size.y) /
                 static_cast<float>(RANKING_HEIGHT)) /
            static_cast<float>(2 * window_size.x);
        viewport.left = margin;
        viewport.width = 1.f - 2.f * margin;

    } else {

        viewport.left = 0.f;
        viewport.width = 1.f;
        float margin =
            (static_cast<float>(window_size.y) -
             static_cast<float>(RANKING_HEIGHT) * static_cast<float>(window_size.x) /
                 static_cast<float>(RANKING_WIDTH)) /
            static_cast<float>(2 * window_size.y);
        viewport.top = margin;
        viewport.height = 1.f - 2.f * margin;
    }

    view.setViewport(viewport);
    return view;
}

void bd2::Ranking::initialiseLevelRanking(Level &level, int level_index, int score) {

    typing_nickname_ = false;
    started_typing_ = false;

    // update score
    ranking_index_ = TOP_RESULTS_NUM;
    while (ranking_index_ > 0 && level.ranking_[ranking_index_ - 1].second < score) {
        ranking_index_--;
    }

    if (ranking_index_ < TOP_RESULTS_NUM) {

        for (int i = TOP_RESULTS_NUM - 1; i > ranking_index_; i--) {
            level.ranking_[i] = level.ranking_[i - 1];
        }
        level.ranking_[ranking_index_] = std::make_pair(std::string(), score);
        typing_nickname_ = true;
        started_typing_ = false;
        typed_string_ = "you";
    }

    // initialise visible elements
    level_name_text_.setString("LEVEL" + std::to_string(level_index));
    auto text_position = level_name_text_.getPosition();
    text_position.x = RANKING_WIDTH / 2 - level_name_text_.getLocalBounds().width / 2;
    level_name_text_.setPosition(text_position);

    for (int i = 0; i < TOP_RESULTS_NUM; i++) {

        if (level.ranking_[i].second > 0) {
            score_texts_[i].setString(std::to_string(level.ranking_[i].second));
            text_position.y = score_texts_[i].getPosition().y;
            text_position.x = RANKING_SCORE_TEXTS_POSITION_X -
                              score_texts_[i].getLocalBounds().width;
            score_texts_[i].setPosition(text_position);

            nickname_texts_[i].setString(level.ranking_[i].first);
            text_position.x = RANKING_NICKNAME_TEXTS_POSITION_X;
            nickname_texts_[i].setPosition(text_position);
        }
    }
}

void bd2::Ranking::finaliseLevelRanking(Level &level) {

    if (ranking_index_ >= 0 && ranking_index_ < TOP_RESULTS_NUM) {
        level.ranking_[ranking_index_].first = typed_string_;
    }
}