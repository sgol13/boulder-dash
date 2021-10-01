#ifndef BD2_DEFS_HPP
#define BD2_DEFS_HPP

//==============================================================================
// LIBRARIES
// =============================================================================

// standard library headers
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// SFML headers
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

constexpr int VERTICAL_TILES_NUM = 20;
constexpr float VIEW_MARGIN_RATIO = 0.3f;


// =============================================================================
// DURATION SETTINGS
// Values given in milliseconds indicate the time that the half of the
// object's move lasts.
// =============================================================================
const sf::Time PLAYER_MOVE_DURATION = sf::milliseconds(120);

#endif