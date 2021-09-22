#ifndef BD2_DEFS_HPP
#define BD2_DEFS_HPP

// =============================================================================
// LIBRARIES
// standard library headers
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// SFML headers
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// =============================================================================
// RESOURCES
// path to resources directory (if not set by cmake)
#ifndef BD2_RESOURCES_DIR
#define BD2_RESOURCES_DIR "res/"
#endif

/* Lists of indispensable resources (game does not load if one of them is
missing). Every list should be ended with nullptr. */
const char *GRAPHIC_RESOURCES_LIST[] = {"boulder.png", "ground.png", "exit.png",
                                        "wall.png"};

const char *AUDIO_RESOURCES_LIST[] = {};

const char *FONT_RESOURCES_LIST[] = {"font.ttf"};

constexpr int GRAPHIC_RESOURCES_NUM = sizeof GRAPHIC_RESOURCES_LIST / sizeof(char *);
constexpr int AUDIO_RESOURCES_NUM = sizeof AUDIO_RESOURCES_LIST / sizeof(char *);
constexpr int FONT_RESOURCES_NUM = sizeof FONT_RESOURCES_LIST / sizeof(char *);

// =============================================================================
// DURATION SETTINGS

#endif