// Szymon Golebiowski
// Boulder Dash

#ifndef BD_RESOURCE_HANDLER_HPP
#define BD_RESOURCE_HANDLER_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/resources.hpp"

namespace bd {

template <class T> class ResourceHandler {
  public:
    bool loadResources(const std::vector<std::string> &files_list,
                       const std::string &resources_dir);

    bool loadResources(const char *files_list[], const int files_num,
                       const std::string &resources_dir);

    template <class S>
    bool loadResources(const std::pair<S, const char *> files_list[],
                       const int files_num, const std::string &resources_dir);

    /* Returns a pointer to the resource of a given name (or label).
    Returns nullptr if no resource with this name was loaded */
    template <class S> std::shared_ptr<T> operator[](S resource_label) const;

    /* Returns the list of resources that were not loaded correctly */
    std::vector<std::string> getMissingResources() const;

  private:
    std::unordered_map<std::string, std::shared_ptr<T>> resources_;

    std::vector<std::string> missing_resources_;
};

} // namespace bd


/** Basic loadResources() that actually loads the resources from files.
 * Other loadResources() overloads which differ due to the way how list of files
 * is passed only create a std::vector<std::string> of filenames
 * and call this function. */
template <class T>
bool bd::ResourceHandler<T>::loadResources(const std::vector<std::string> &files_list,
                                           const std::string &resources_dir) {

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

// creates std::vector of resources names and calls another function overload
template <class T>
bool bd::ResourceHandler<T>::loadResources(const char *files_list[],
                                           const int files_num,
                                           const std::string &resources_dir) {

    std::vector<std::string> resources_vector;
    for (int i = 0; i < files_num; i++) {
        resources_vector.push_back(files_list[i]);
    }

    return loadResources(resources_vector, resources_dir);
}

// creates std::vector of resources names and calls another function overload
template <class T>
template <class S>
bool bd::ResourceHandler<T>::loadResources(
    const std::pair<S, const char *> files_list[], const int files_num,
    const std::string &resources_dir) {

    std::vector<std::string> resources_vector;
    for (int i = 0; i < files_num; i++) {
        resources_vector.push_back(files_list[i].second);
    }

    return loadResources(resources_vector, resources_dir);
}

template <class T>
template <class S>
std::shared_ptr<T> bd::ResourceHandler<T>::operator[](S resource_label) const {

    const char *resource_name = resources::getFilename(resource_label);

    auto it = resources_.find(resource_name);
    if (it == resources_.end()) {
        return std::shared_ptr<T>(nullptr);
    }

    return it->second;
}

template <class T>
std::vector<std::string> bd::ResourceHandler<T>::getMissingResources() const {
    return missing_resources_;
}

#endif