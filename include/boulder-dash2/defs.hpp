#ifndef BD2_DEFS_HPP
#define BD2_DEFS_HPP

// =============================================================================
// LIBRARIES
// standard library headers
#include <fstream>
#include <iostream>
#include <limits>
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
// paths to resources directories (if not set by cmake)

#ifndef BD2_GRAPHIC_RESOURCES_DIR
#define BD2_GRAPHIC_RESOURCES_DIR "res/textures/"
#endif

#ifndef BD2_FONT_RESOURCES_DIR
#define BD2_FONT_RESOURCES_DIR "res/fonts/"
#endif

#ifndef BD2_LEVEL_RESOURCES_DIR
#define BD2_LEVEL_RESOURCES_DIR "res/levels/"
#endif

/* Lists of indispensable resources (game does not load if one of them is missing) */
extern const char *GRAPHIC_RESOURCES_LIST[];
extern const char *FONT_RESOURCES_LIST[];
extern const char *LEVEL_RESOURCES_LIST[];

// automatically calculate reosources lists' sizes
extern const int GRAPHIC_RESOURCES_NUM;
extern const int FONT_RESOURCES_NUM;
extern const int LEVEL_RESOURCES_NUM;

// =============================================================================
// DURATION SETTINGS

#endif