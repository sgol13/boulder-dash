// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_RESOURCES_HPP
#define BD2_RESOURCES_HPP

#include "boulder-dash2/defs.hpp"

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
    PLAYER_DEATH,
    PLAYER_BORNING,
    EXPLOSION,

    // other textures
    PROGRAM_ICON,
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
    {Textures::PLAYER_DEATH, "player_death.png"},
    {Textures::PLAYER_BORNING, "player_start.png"},
    {Textures::EXPLOSION, "explosion.png"},

    // other textures
    {Textures::PROGRAM_ICON, "icon.png"},
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
// SOUNDS
//=============================================================================
enum class Sounds {

    MUSIC,
    EXPLOSION,
    BOULDER_PUSH,
    GROUND_DESTROY,
    BUTTERFLY_DESTROY,
    DIAMOND,
    GAME_OVER,
    GAME_WIN,
    MENU_SOUND,
};

constexpr std::pair<Sounds, const char *> sound_files[] = {
    {Sounds::MUSIC, "music.wav"},
    {Sounds::EXPLOSION, "explosion.wav"},
    {Sounds::BOULDER_PUSH, "boulder_push.wav"},
    {Sounds::GROUND_DESTROY, "ground_destroy.wav"},
    {Sounds::BUTTERFLY_DESTROY, "butterfly_destroy.wav"},
    {Sounds::DIAMOND, "diamond.wav"},
    {Sounds::GAME_OVER, "game_over.wav"},
    {Sounds::GAME_WIN, "game_win.wav"},
    {Sounds::MENU_SOUND, "menu_sound.wav"},
};

constexpr int sound_files_num =
    sizeof(sound_files) / sizeof(std::pair<Sounds, const char *>);

//=============================================================================
// LEVELS
//=============================================================================
enum class Levels { LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, LEVEL_6, LEVEL_7 };

constexpr std::pair<Levels, const char *> level_files[] = {

    {Levels::LEVEL_1, "level1"},
    {Levels::LEVEL_2, "level2"},
    {Levels::LEVEL_3, "level3"} /*, {Levels::LEVEL_4, "level4"},
     {Levels::LEVEL_5, "level5"}, {Levels::LEVEL_6, "level6"},
     {Levels::LEVEL_7, "level7"},*/
};

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

// template specialised for Sounds
template <> struct __FilenamesStruct<Sounds> {
    static constexpr const std::pair<Sounds, const char *> *files_ = sound_files;
    static constexpr int files_num_ = sound_files_num;
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