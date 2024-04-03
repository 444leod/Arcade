/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibraryLoader
*/

#include "LibraryLoader.hpp"

LibraryObject::LibraryObject(const std::string &path)
{
    this->_path = path.starts_with("./") ? path : "./" + path;
    this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
    if (this->_handle == nullptr)
        return;

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
    if (_handle != nullptr)
        dlclose(_handle);
}

LibraryLoader::LibraryLoader(const std::string &path)
{
    if (!std::filesystem::exists(path))
        return;

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        auto object = std::make_shared<LibraryObject>(entry.path().string());
        if (object->loaded())
            this->_libs.push_back(object);
    }
}

LibraryLoader::~LibraryLoader()
{
    if (this->_handle != nullptr)
        dlclose(this->_handle);
}

bool LibraryLoader::contains(const std::string &lib, arc::SharedLibraryType type) const
{
    for (auto l : this->_libs)
        if (path_cmp(lib, l->path()) && l->type() == type)
            return true;
    return false;
}

bool LibraryLoader::contains(const std::string &lib) const
{
    for (auto l : this->_libs)
        if (path_cmp(lib, l->path()))
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

std::shared_ptr<LibraryObject> LibraryLoader::nextLib()
{
    this->_libIndex = (this->_libIndex + 1) % _libs.size();
    while (this->_libs[this->_libIndex]->type() != arc::SharedLibraryType::LIBRARY)
        this->_libIndex = (this->_libIndex + 1) % _libs.size();
    return this->_libs[this->_libIndex];
}

std::shared_ptr<LibraryObject> LibraryLoader::nextGame()
{
    this->_gameIndex = (this->_gameIndex + 1) % _libs.size();
    while (this->_libs[this->_gameIndex]->type() != arc::SharedLibraryType::GAME)
        this->_gameIndex = (this->_gameIndex + 1) % _libs.size();
    return this->_libs[this->_gameIndex];
}

std::shared_ptr<LibraryObject> LibraryLoader::load(const std::string &path, arc::SharedLibraryType type)
{
    if (this->_libIndex < 0)
        this->_libIndex = 0;
    auto l = this->_libs[this->_libIndex];

    while (!path_cmp(l->path(), path))
        l = type == arc::SharedLibraryType::LIBRARY ? this->nextLib() : this->nextGame();
    return l;
}

bool LibraryLoader::path_cmp(const std::string &a, const std::string& b) const
{
    std::string _a = a.starts_with("./") ? a : "./" + a;
    std::string _b = b.starts_with("./") ? b : "./" + b;
    return _a == _b;
}
