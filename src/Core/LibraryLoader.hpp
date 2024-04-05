/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** LibraryLoader
*/

#pragma once

#include "SharedLibraryType.hpp"
#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <filesystem>

class LibraryObject {
        public:
        LibraryObject(const std::string& path);
        ~LibraryObject();

        template<typename T>
        std::unique_ptr<T> get()
        {
            auto h = reinterpret_cast<T *(*)()>(dlsym(_handle, "entrypoint"));
            return std::unique_ptr<T>(h());
        }

        bool loaded() const { return this->_loaded; }
        const std::string& path() const { return this->_path; }
        const std::string& name() const { return this->_name; }
        arc::SharedLibraryType type() const { return this->_type; }

    protected:
    private:
        bool _loaded = false;
        std::string _path = "";
        std::string _name = "";
        arc::SharedLibraryType _type = arc::SharedLibraryType::LIBRARY;
        void *_handle = nullptr;
};

class LibraryLoader {
    public:
        LibraryLoader(const std::string &path);
        ~LibraryLoader();
        const std::vector<std::shared_ptr<LibraryObject>> &libs() const { return this->_libs; }
        bool contains(const std::string &lib, arc::SharedLibraryType type) const;
        bool contains(const std::string &lib) const;
        bool contains(arc::SharedLibraryType type) const;
        std::shared_ptr<LibraryObject> nextLib();
        std::shared_ptr<LibraryObject> nextGame();
        std::shared_ptr<LibraryObject> load(const std::string &path, arc::SharedLibraryType type = arc::SharedLibraryType::LIBRARY);

    protected:
    private:
        bool path_cmp(const std::string &a, const std::string& b) const;
    private:
        int _gameIndex = -1;
        int _libIndex = -1;
        std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};
