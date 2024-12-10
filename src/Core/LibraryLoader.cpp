/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibraryLoader
*/

#include "LibraryLoader.hpp"

/**============================================
 *               OBEJCTS
 *=============================================**/

LibraryObject::LibraryObject(const std::string &path)
{
    this->_path = path;
    this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
    if (this->_handle == nullptr)
        return;

    this->_entrypoint = dlsym(this->_handle, "entrypoint");

    auto nameHandle = reinterpret_cast<const char *(*)()>(dlsym(this->_handle, "name"));
    if (nameHandle == nullptr)
        return;
    this->_name = nameHandle();

    auto typeHandle = reinterpret_cast<arc::SharedLibraryType (*)()>(dlsym(this->_handle, "type"));
    if (typeHandle == nullptr)
        return;
    this->_type = typeHandle();

    _loaded = true;
}

LibraryObject::~LibraryObject()
{
    if (this->_handle != nullptr)
        dlclose(_handle);
}

/**============================================
 *               LOADER
 *=============================================**/

LibraryLoader::LibraryLoader(const std::string &path, bool restrict_tty)
{
    if (!std::filesystem::exists(path))
        return;

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        auto object = std::make_shared<LibraryObject>(entry.path().string());
        if (restrict_tty && object->type() == arc::SharedLibraryType::LIBRARY && object->name() != "NCurses")
            continue;
        if (object->loaded())
            this->_libs.push_back(object);
    }
}

bool LibraryLoader::contains(const std::string &lib, arc::SharedLibraryType type) const
{
    for (auto l : this->_libs)
        if (LibraryLoader::_path_cmp(lib, l->path()) && l->type() == type)
            return true;
    return false;
}

bool LibraryLoader::contains(arc::SharedLibraryType type) const
{
    for (auto l : this->_libs)
        if (l->type() == type)
            return true;
    return false;
}

std::shared_ptr<LibraryObject> LibraryLoader::get(const std::string &path) const
{
    for (auto lo : this->_libs)
        if (LibraryLoader::_path_cmp(lo->path(), path))
            return lo;
    return nullptr;
}

std::vector<std::shared_ptr<LibraryObject>> LibraryLoader::get(arc::SharedLibraryType type) const
{
    std::vector<std::shared_ptr<LibraryObject>> libs;

    for (auto lo : this->_libs)
        if (lo->type() == type)
            libs.push_back(lo);
    return libs;
}

bool LibraryLoader::_path_cmp(const std::string &a, const std::string& b)
{
    std::string _a = a.starts_with(".") || a.starts_with("/") ? a : "./" + a;
    std::string _b = b.starts_with(".") || b.starts_with("/") ? b : "./" + b;
    _a = _a.starts_with("/") ? "." + _a.substr(std::filesystem::current_path().string().size()) : _a;
    _b = _b.starts_with("/") ? "." + _b.substr(std::filesystem::current_path().string().size()) : _b;
    return _a == _b;
}
