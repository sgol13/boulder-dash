#ifndef BD2_RESOURCES_HPP
#define BD2_RESOURCES_HPP

#include "boulder-dash2/defs.hpp"

//=============================================================================
// RESOURCE LISTS
//=============================================================================
/** Each resource type has its own enum class that contains labels for
 * all the resources of this type. Moreover, for each resource type, there is
 * an array that stores pairs of resource labels and names of the files
 * in which they are saved.
 * All resources which appear on the lists are indispensable. The game will not
 * start if one of them is missing or cannot be loaded correctly. */
//=============================================================================

namespace bd2 {
namespace resources {

//=============================================================================
// TEXTURES
//=============================================================================
enum class Textures {

    // static textures
    WALL,
    GROUND,
    EXIT,
    BOULDER,

    // animatable textures
    DIAMOND,
    BUTTERFLY,
    FIREFLY,
    PLAYER_STANDING,
    PLAYER_MOVING_LEFT,
    PLAYER_MOVING_RIGHT,

    // other textures
    ICON,
};

constexpr std::pair<Textures, const char *> texture_files[] = {

    // static textures
    {Textures::WALL, "wall.png"},
    {Textures::GROUND, "ground.png"},
    {Textures::EXIT, "exit.png"},
    {Textures::BOULDER, "boulder.png"},

    // animatable textures
    {Textures::DIAMOND, "diamond.png"},
    {Textures::BUTTERFLY, "butterfly.png"},
    {Textures::FIREFLY, "firefly.png"},
    {Textures::PLAYER_STANDING, "player_standing.png"},
    {Textures::PLAYER_MOVING_LEFT, "player_moving_left.png"},
    {Textures::PLAYER_MOVING_RIGHT, "player_moving_right.png"},

    // other textures
    {Textures::ICON, "icon.png"},
};

constexpr int texture_files_num =
    sizeof(texture_files) / sizeof(std::pair<Textures, const char *>);

//=============================================================================
// FONTS
//=============================================================================
enum class Fonts { PIXEL_FONT };

constexpr std::pair<Fonts, const char *> font_files[] = {
    {Fonts::PIXEL_FONT, "font.ttf"}};

constexpr int font_files_num =
    sizeof(font_files) / sizeof(std::pair<Fonts, const char *>);

//=============================================================================
// LEVELS
//=============================================================================
enum class Levels { TEST_LEVEL };

constexpr std::pair<Levels, const char *> level_files[] = {
    {Levels::TEST_LEVEL, "level1"}};

constexpr int level_files_num =
    sizeof(level_files) / sizeof(std::pair<Levels, const char *>);

//=============================================================================
// getFilename() function
//=============================================================================
/** getFilename() template function needs to recognise the type of a resource
 * label 'name', passed as a parameter, and search for a resource filename
 * in a proper list (containing resources of the same type as 'name').
 * Multi-specialised template class __FilenamesStruct is created to get this
 * effect. Thanks to template specialisation, it always contains a pointer to the
 * proper resource list. */
//=============================================================================

// not specialised template
template <class T> struct __FilenamesStruct {};

// template specialised for Textures
template <> struct __FilenamesStruct<Textures> {
    static constexpr const std::pair<Textures, const char *> *files_ = texture_files;
    static constexpr int files_num_ = texture_files_num;
};

// template specialised for Fonts
template <> struct __FilenamesStruct<Fonts> {
    static constexpr const std::pair<Fonts, const char *> *files_ = font_files;
    static constexpr int files_num_ = font_files_num;
};

// template specialised for Levels
template <> struct __FilenamesStruct<Levels> {
    static constexpr const std::pair<Levels, const char *> *files_ = level_files;
    static constexpr int files_num_ = level_files_num;
};


/** Returns the filename which is assigned to the resource label given as a parameter.
 * Searches in a proper list thanks to template specialisation of class
 * __FilenamesStruct which contains a pointer to the resource list and its size.*/
template <class T> constexpr const char *getFilename(T name) {

    for (int i = 0; i < __FilenamesStruct<T>::files_num_; i++) {

        if (name == __FilenamesStruct<T>::files_[i].first) {
            return __FilenamesStruct<T>::files_[i].second;
        }
    }
    return nullptr;
}

} // namespace resources
} // namespace bd2

#endif