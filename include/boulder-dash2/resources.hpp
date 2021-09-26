#ifndef BD2_RESOURCES_HPP
#define BD2_RESOURCES_HPP

#include "boulder-dash2/defs.hpp"

//=============================================================================
// RESOURCE LISTS
//=============================================================================
/** Each resource type has its own enum class that contains labels for
 * all the resources of this type. Moreover, for each resource type, there is
 * an array that stores pairs of resource labels and names of the files
 * in which they are saved. */
//=============================================================================

namespace bd2 {
namespace resources {

// TEXTURES
enum class Textures {

    // static textures
    WALL,
    BOULDER,
    EXIT,
    GROUND,

    // animations
};

constexpr std::pair<Textures, const char *> texture_files[] = {

    // static textures
    {Textures::WALL, "wall.png"},
    {Textures::BOULDER, "boulder.png"},
    {Textures::EXIT, "exit.png"},
    {Textures::GROUND, "ground.png"},
};

// FONTS
enum class Fonts { PIXEL_FONT };

constexpr std::pair<Fonts, const char *> font_files[] = {
    {Fonts::PIXEL_FONT, "font.ttf"}};

//=============================================================================
// getFilename() function
//=============================================================================
/** getFilename() template function needs to recognise the type of a resource
 * label 'name', passed as a parameter, and search for a resource filename
 * in a proper list (containing resources of the same type as 'name').
 * Multi-specialised template class __FilenamesStruct is created to get this effect.
 * Thanks to template specialisation, it always contains a pointer to the proper
 * resource list. */
//=============================================================================

// not specialised template
template <class T> struct __FilenamesStruct {};

// template specialised for Textures
template <> struct __FilenamesStruct<Textures> {
    static constexpr const std::pair<Textures, const char *> *files_ = texture_files;
    static constexpr int files_num_ =
        sizeof(texture_files) / sizeof(std::pair<Textures, const char *>);
};

// template specialised for Fonts
template <> struct __FilenamesStruct<Fonts> {
    static constexpr const std::pair<Fonts, const char *> *files_ = font_files;
    static constexpr int files_num_ =
        sizeof(texture_files) / sizeof(std::pair<Fonts, const char *>);
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