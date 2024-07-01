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
        std::shared_ptr<T> get()
        {
            auto h = reinterpret_cast<T *(*)()>(this->_entrypoint);
            return std::shared_ptr<T>(h());
        }

        bool loaded() const { return this->_loaded; }
        const std::string& path() const { return this->_path; }
        const std::string& name() const { return this->_name; }
        arc::SharedLibraryType type() const { return this->_type; }

    protected:
    private:
        void *_handle = nullptr;
        void *_entrypoint = nullptr;
        bool _loaded = false;
        std::string _path = "";
        std::string _name = "";
        arc::SharedLibraryType _type = arc::SharedLibraryType::LIBRARY;
};
class LibraryLoader {
    public:
        LibraryLoader(const std::string &path, bool restrict_tty);
        ~LibraryLoader() = default;
        bool contains(const std::string &lib, arc::SharedLibraryType type) const;
        bool contains(arc::SharedLibraryType type) const;
        std::shared_ptr<LibraryObject> get(const std::string &path) const;
        std::vector<std::shared_ptr<LibraryObject>> get(arc::SharedLibraryType type) const;

    protected:
    private:
        static bool _path_cmp(const std::string &a, const std::string& b);
    private:
        std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};
