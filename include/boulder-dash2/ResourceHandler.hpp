#ifndef BD2_RESOURCE_HANDLER_HPP
#define BD2_RESOURCE_HANDLER_HPP

#include "boulder-dash2/defs.hpp"

namespace bd2 {

template <class T> class ResourceHandler {
  public:
    /* Loads all resources from a given list. Returns true if all resource were
    correctly loaded, false otherwise. */
    bool loadResources(const char *resources_list[], int n_resources);

    /* Returns the list of resources that were not loaded correctly */
    std::vector<std::string> getMissingResources();

    /* Returns a pointer to the resource of a given name. Returns nullptr if no
        resource with this name was loaded */
    std::shared_ptr<T> getResource(const std::string resource_name);

  private:
    std::unordered_map<std::string, T> resources_;

    std::vector<std::string> missing_resources_;
};

} // namespace bd2

//==============================================================================

template <class T>
bool bd2::ResourceHandler<T>::loadResources(const char *resources_list[],
                                            int n_resources) {

    bool correct_loading = true;

    T resource;
    for (int i = 0; i < n_resources; i++) {

        if (resource.loadFromFile(resources_list[i])) {
            resources_[resources_list[i]] = resource;
        } else {
            correct_loading = false;
            missing_resources_.push_back(resources_list[i]);
        }
    }

    return correct_loading;
}

template <class T>
std::vector<std::string> bd2::ResourceHandler<T>::getMissingResources() {
    return missing_resources_;
}

template <class T>
std::shared_ptr<T>
bd2::ResourceHandler<T>::getResource(const std::string resource_name) {

    auto it = resources_.find(resource_name);
    if (it == resources_.end()) {
        return std::shared_ptr<T>(nullptr);
    }

    return std::shared_ptr<T>(&it->second);
}

#endif