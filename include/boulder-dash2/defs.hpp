#ifndef BD2_DEFS_HPP
#define BD2_DEFS_HPP

//==============================================================================
// LIBRARIES
// =============================================================================

// standard library headers
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// SFML headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// =============================================================================
// RESOURCES
// paths to resource directories (default if not set by cmake)
// =============================================================================

#ifndef BD2_GRAPHIC_RESOURCES_DIR
#define BD2_GRAPHIC_RESOURCES_DIR "res/textures/"
#endif

#ifndef BD2_FONT_RESOURCES_DIR
#define BD2_FONT_RESOURCES_DIR "res/fonts/"
#endif

#ifndef BD2_AUDIO_RESOURCES_DIR
#define BD2_AUDIO_RESOURCES_DIR "res/sounds/"
#endif

#ifndef BD2_LEVEL_RESOURCES_DIR
#define BD2_LEVEL_RESOURCES_DIR "res/levels/"
#endif

// =============================================================================
// WINDOW SETTINGS
// =============================================================================

constexpr char WINDOW_NAME[] = "Boulder Dash 2";

// initial ratio: window dimensions / screen dimensions
constexpr float INI_WINDOW_SCREEN_RATIO_X = 0.5f;
constexpr float INI_WINDOW_SCREEN_RATIO_Y = 0.7f;

// initial window position on the screen
constexpr int INI_WINDOW_POS_X = 0;
constexpr int INI_WINDOW_POS_Y = 0;

// minimal window dimensions
constexpr int MIN_WINDOW_WIDTH = 800;
constexpr int MIN_WINDOW_HEIGHT = 600;

constexpr int TILE_SIZE = 32;
constexpr int VERTICAL_TILES_NUM = 25;
constexpr float UPPER_BAR_TILE_RATIO = 2.0f;
constexpr float VIEW_MARGIN_RATIO = 0.4f;
constexpr float INTERFACE_FONT_RATIO = 0.6f;

constexpr float UPPER_BAR_SIZE = TILE_SIZE * UPPER_BAR_TILE_RATIO;

constexpr float UPPER_BAR_SCREEN_RATIO =
    UPPER_BAR_SIZE / (TILE_SIZE * VERTICAL_TILES_NUM);

constexpr int INTERFACE_FONT_SIZE =
    static_cast<int>(UPPER_BAR_SIZE * INTERFACE_FONT_RATIO);

constexpr float INTERFACE_TEXT_POS =
    0.7f * ((UPPER_BAR_SIZE - INTERFACE_FONT_SIZE) / 2.f);

constexpr int GAME_OVER_FONT_SIZE = 80;
constexpr int VICTORY_TEXT_FONT_SIZE = 30;
constexpr int GAME_OVER_SCORE_FONT_SIZE = 40;
constexpr int PAUSE_TEXT_FONT_SIZE = 80;

// =============================================================================
// MENU SETTINGS
// =============================================================================

constexpr int MENU_WIDTH = 1800;
constexpr int MENU_GAME_NAME_FONT_SIZE = 150;
constexpr int MENU_OPTIONS_TEXTS_SIZE = 75;
constexpr int MENU_OPTIONS_TEXTS_POSITION_X = 785;
constexpr int MENU_ABOVE_GAME_NAME_GAP_HEIGHT = 150;
constexpr int MENU_BELOW_GAME_NAME_GAP_HEIGHT = 150;
constexpr int MENU_BETWEEN_OPTIONS_TEXT_GAP_HEIGHT = 50;
constexpr int MENU_BELOW_OPTIONS_TEXTS_GAP_HEIGHT = 150;
constexpr int MENU_PLAYER_SIZE = 100;

const sf::Color GREY_COLOR(180, 180, 180);

// =============================================================================
// RANKING SETTINGS
// =============================================================================
constexpr int TOP_RESULTS_NUM = 5;

constexpr int RANKING_WIDTH = 1800;
constexpr int RANKING_SCORE_TEXTS_POSITION_X = 885;
constexpr int RANKING_NICKNAME_TEXTS_POSITION_X = 915;
constexpr int RANKING_LEVEL_NAME_FONT_SIZE = 100;
constexpr int RANKING_SCORES_TEXTS_FONT_SIZE = 50;
constexpr int RANKING_ABOVE_LEVEL_NAME_GAP_HEIGHT = 150;
constexpr int RANKING_BELOW_LEVEL_NAME_GAP_HEIGHT = 150;
constexpr int RANKING_BETWEEN_SCORES_TEXT_GAP_HEIGHT = 25;
constexpr int RANKING_BELOW_SCORES_TEXTS_GAP_HEIGHT = 300;
constexpr int RANKING_HEIGHT =
    RANKING_ABOVE_LEVEL_NAME_GAP_HEIGHT + RANKING_LEVEL_NAME_FONT_SIZE +
    RANKING_BELOW_LEVEL_NAME_GAP_HEIGHT +
    TOP_RESULTS_NUM *
        (RANKING_SCORES_TEXTS_FONT_SIZE + RANKING_BETWEEN_SCORES_TEXT_GAP_HEIGHT) +
    RANKING_BELOW_SCORES_TEXTS_GAP_HEIGHT;

constexpr int NICKNAME_LENGTH_LIMIT = 20;

// =============================================================================
// DURATION SETTINGS
// =============================================================================

const sf::Time PLAYER_MOVE_DURATION = sf::milliseconds(120);
const sf::Time PLAYER_MOVING_ANIMATION_DURATION = sf::milliseconds(240);
const sf::Time PLAYER_STANDING_ANIMATION_DURATION = sf::milliseconds(1400);
const sf::Time PLAYER_DEATH_ANIMATION_DURATION = sf::milliseconds(500);
const sf::Time PLAYER_START_ANIMATION_DURATION = sf::milliseconds(500);

const sf::Time FLYABLE_MOVE_DURATION = sf::milliseconds(195);
const sf::Time FLYABLE_ANIMATION_DURATION = sf::milliseconds(195);

const sf::Time BOULDER_MOVE_DURATION = sf::milliseconds(150);

const sf::Time DIAMOND_ANIMATION_DURATION = sf::milliseconds(240);

const sf::Time EXPLOSION_DURATION = sf::milliseconds(720);

const sf::Time TIME_SCORE_TRANSFER_DURATION = sf::milliseconds(15);

const sf::Time BLINKING_NICKNAME_CYCLE_DURATION = sf::milliseconds(300);

// =============================================================================
// SOUNDS SETTINGS
// =============================================================================
constexpr float MUSIC_VOLUME = 100;
constexpr float IN_GAME_SOUNDS_VOLUME = 100;

// =============================================================================
// SCORE SETTINGS
// =============================================================================
constexpr int DIAMOND_POINTS = 5;
constexpr int BUTTERFLY_POINTS = 10;
constexpr int FIREFLY_POINTS = 10;
constexpr int SECOND_LEFT_POINTS = 1;


#endif