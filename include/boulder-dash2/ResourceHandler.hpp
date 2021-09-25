#ifndef BD2_RESOURCE_HANDLER_HPP
#define BD2_RESOURCE_HANDLER_HPP

#include "boulder-dash2/defs.hpp"

namespace bd2 {

/* Labels for resources (all types) which are used in a game */
enum class ResourceNames {

    // static textures
    BOULDER_STATIC_TEXTURE,
    EXIT_STATIC_TEXTURE,
    GROUND_STATIC_TEXTURE,
    WALL_STATIC_TEXTURE,

    // animations

    // fonts
    PIXEL_FONT
};

/* constexpr std::map<const ResourceNames, const std::string> resource_filenames = {
    {ResourceNames::BOULDER_STATIC_TEXTURE, "boulder.png"},
    {ResourceNames::EXIT_STATIC_TEXTURE, "exit.png"},
    {ResourceNames::GROUND_STATIC_TEXTURE, "ground.png"}}; */

template <class T> class ResourceHandler {
  public:
    /* Loads all resources from a given list. Returns true if all resource were
    correctly loaded, false otherwise. */
    bool loadResources(const std::vector<std::string> &resources_list,
                       const std::string &resources_dir);

    bool loadResources(const char *resources_list[], int n_resources,
                       const std::string &resources_dir);

    /* Returns the list of resources that were not loaded correctly */
    std::vector<std::string> getMissingResources() const;

    /* Returns a pointer to the resource of a given name. Returns nullptr if no
        resource with this name was loaded */
    std::shared_ptr<const T> getResource(const std::string resource_name) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<const T>> resources_;

    std::vector<std::string> missing_resources_;
};

} // namespace bd2

//=========================================================================

template <class T>
bool bd2::ResourceHandler<T>::loadResources(
    const std::vector<std::string> &resources_list,
    const std::string &resources_dir) {

    bool correct_loading = true;

    T resource;
    for (auto &resource_name : resources_list) {

        if (resource.loadFromFile(resources_dir + resource_name)) {
            resources_[resource_name] = std::make_shared<T>(resource);
        } else {
            correct_loading = false;
            missing_resources_.push_back(resource_name);
        }
    }

    return correct_loading;
}

template <class T>
bool bd2::ResourceHandler<T>::loadResources(const char *resources_list[],
                                            int n_resources,
                                            const std::string &resources_dir) {

    // create std::vector of resources names and run another function overload
    std::vector<std::string> resources_vector;
    for (int i = 0; i < n_resources; i++) {
        resources_vector.push_back(resources_list[i]);
    }

    return loadResources(resources_vector, resources_dir);
}

template <class T>
std::vector<std::string> bd2::ResourceHandler<T>::getMissingResources() const {
    return missing_resources_;
}

template <class T>
std::shared_ptr<const T>
bd2::ResourceHandler<T>::getResource(const std::string resource_name) const {

    auto it = resources_.find(resource_name);
    if (it == resources_.end()) {
        return std::shared_ptr<T>(nullptr);
    }

    return it->second;
}

#endif