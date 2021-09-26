#ifndef BD2_RESOURCE_HANDLER_HPP
#define BD2_RESOURCE_HANDLER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/resources.hpp"

namespace bd2 {

//=============================================================================
// RESOURCE HANDLER
//=============================================================================
/** In the project, there are ResourceHandlers of various types: Textures,
 * Fonts, Sounds, Levels. There is only one instance of the ResourceHandler
 * for a given type of resources. Each ResourceHandler should load its resources
 * from files using loadResources() function which takes as a parameter a list
 * of resources to read. If some resource cannot be properly loaded, its name
 * is added to the common (static class member) list missing_resources_.
 * The constant references to ResourceHandlers are passed to various components
 * of the game, thus providing an access to loaded resources.
 * An access to a particular resource can be demanded from ResourceHandler
 * by resource's name or its label (namespace resource::). Then, a shared pointer
 * to the demanded resource is returned. */
//=============================================================================

template <class T> class ResourceHandler {
  public:
    /* Loads all resources from a given list. Returns true if all resources were
    correctly loaded, false otherwise. */
    bool loadResources(const std::vector<std::string> &files_list,
                       const std::string &resources_dir);

    bool loadResources(const char *files_list[], const int files_num,
                       const std::string &resources_dir);

    template <class S>
    bool loadResources(const std::pair<S, const char *> files_list[],
                       const int files_num, const std::string &resources_dir);

    /* Returns a pointer to the resource of a given name (or label).
    Returns nullptr if no resource with this name was loaded */
    std::shared_ptr<const T> getResource(const std::string resource_filename) const;

    template <class S> std::shared_ptr<const T> getResource(S resource_name);

    /* Returns the list of resources that were not loaded correctly */
    static std::vector<std::string> getMissingResources();

  private:
    std::unordered_map<std::string, std::shared_ptr<const T>> resources_;

    static std::vector<std::string> missing_resources_;
};

} // namespace bd2

//=============================================================================
// ResourceHandler::loadResources()
//=============================================================================
/** Basic loadResources() that actually loads the resources from files.
 * Other loadResources() overloads which differ due to the way how list of files
 * is passed only create a std::vector<std::string> of filenames
 * and call this function. */
template <class T>
bool bd2::ResourceHandler<T>::loadResources(
    const std::vector<std::string> &files_list, const std::string &resources_dir) {

    bool correct_loading = true;

    T resource;
    for (auto &filename : files_list) {

        if (resource.loadFromFile(resources_dir + filename)) {
            resources_[filename] = std::make_shared<T>(resource);
        } else {
            correct_loading = false;
            missing_resources_.push_back(filename);
        }
    }

    return correct_loading;
}

// create std::vector of resources names and run another function overload
template <class T>
bool bd2::ResourceHandler<T>::loadResources(const char *files_list[],
                                            const int files_num,
                                            const std::string &resources_dir) {


    std::vector<std::string> resources_vector;
    for (int i = 0; i < files_num; i++) {
        resources_vector.push_back(files_list[i]);
    }

    return loadResources(resources_vector, resources_dir);
}


template <class T>
template <class S>
bool bd2::ResourceHandler<T>::loadResources(
    const std::pair<S, const char *> files_list[], const int files_num,
    const std::string &resources_dir) {

    std::vector<std::string> resources_vector;
    for (int i = 0; i < files_num; i++) {
        resources_vector.push_back(files_list[i].second);
    }

    return loadResources(resources_vector, resources_dir);
}

//=============================================================================
// ResourceHandler::getResource()
//=============================================================================
/* Basic getResource() function that searches for a resource in a map container.*/
template <class T>
std::shared_ptr<const T>
bd2::ResourceHandler<T>::getResource(const std::string resource_name) const {

    auto it = resources_.find(resource_name);
    if (it == resources_.end()) {
        return std::shared_ptr<T>(nullptr);
    }

    return it->second;
}

/* getResource() function overload that takes as a parameter the label of the
resource and uses resource::getFilename() to obtain a name of the file in which
the resource is saved. Then, it runs a basic (above) getResource() function. */
template <class T>
template <class S>
std::shared_ptr<const T> bd2::ResourceHandler<T>::getResource(S resource_name) {
    return getResource(resources::getFilename(resource_name));
}

//=============================================================================

template <class T>
std::vector<std::string> bd2::ResourceHandler<T>::getMissingResources() {
    return missing_resources_;
}

#endif