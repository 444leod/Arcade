/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "IGame.hpp"
#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <filesystem>

class CoreException : public std::exception
{
    public:
        CoreException(const std::string& msg) : _msg(msg) {}
        ~CoreException() = default;
        virtual const char *what() const noexcept { return _msg.c_str(); }
    private:
        std::string _msg;
};

class LibraryObject
{
    public:
        LibraryObject(const std::string& path)
        {
            this->_path = path;
            this->_handle = dlopen(path.c_str(), RTLD_LAZY);
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

        ~LibraryObject()
        {
            if (_handle != nullptr)
                dlclose(_handle);
        }

        template<typename T>
        std::unique_ptr<T> get()
        {
            auto h = reinterpret_cast<T *(*)()>(dlsym(_handle, "entrypoint"));
            return std::unique_ptr<T>(h());
        }

        bool loaded() const { return _loaded; }
        const std::string& path() const { return this->_path; }
        const std::string& name() const { return this->_name; }
        arc::SharedLibraryType type() const { return this->_type; }

    private:
        bool _loaded = false;
        std::string _path = "";
        std::string _name = "";
        arc::SharedLibraryType _type = arc::SharedLibraryType::LIBRARY;
        void *_handle = nullptr;
};

class LibraryLoader
{
    public:
        LibraryLoader(const std::string& path)
        {
            if (!std::filesystem::exists(path))
                return;

            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                auto object = std::make_shared<LibraryObject>(entry.path().string());
                if (object->loaded())
                    this->_libs.push_back(object);
            }
        }

        ~LibraryLoader()
        {
            if (this->_handle != nullptr)
                dlclose(this->_handle);
        }

        const std::vector<std::shared_ptr<LibraryObject>>& libs() const { return this->_libs; }

        bool contains(const std::string& lib, arc::SharedLibraryType type) const
        {
            for (auto l : this->_libs)
                if (l->path() == lib && l->type() == type)
                    return true;
            return false;
        }

        bool contains(const std::string& lib) const
        {
            for (auto l : this->_libs)
                if (l->path() == lib)
                    return true;
            return false;
        }

        bool contains(arc::SharedLibraryType type) const
        {
            for (auto l : this->_libs)
                if (l->type() == type)
                    return true;
            return false;
        }

        std::shared_ptr<LibraryObject> nextLib()
        {
            this->_libIndex = (this->_libIndex + 1) % _libs.size();
            while (this->_libs[this->_libIndex]->type() != arc::SharedLibraryType::LIBRARY)
                this->_libIndex = (this->_libIndex + 1) % _libs.size();
            return this->_libs[this->_libIndex];
        }

        std::shared_ptr<LibraryObject> nextGame()
        {
            this->_gameIndex = (this->_gameIndex + 1) % _libs.size();
            while (this->_libs[this->_gameIndex]->type() != arc::SharedLibraryType::GAME)
                this->_gameIndex = (this->_gameIndex + 1) % _libs.size();
            return this->_libs[this->_gameIndex];
        }

        std::shared_ptr<LibraryObject> load(const std::string& path,
            arc::SharedLibraryType type = arc::SharedLibraryType::LIBRARY)
        {
            if (this->_libIndex < 0) this->_libIndex = 0;
            auto l = this->_libs[this->_libIndex];

            while (l->path() != path)
                l = type == arc::SharedLibraryType::LIBRARY ? this->nextLib() : this->nextGame();
            return l;
        }

    private:
        int _gameIndex = -1;
        int _libIndex = -1;
        void *_handle = nullptr;
        std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};

class CoreMenu : public arc::IGame
{
    public:
        CoreMenu(const std::vector<std::shared_ptr<LibraryObject>>& libs)
        {
            for (auto l : libs)
                if (l->type() == arc::SharedLibraryType::GAME)
                    this->_libs.push_back(l);
        }

        ~CoreMenu() = default;

        virtual std::string name() const
        {
            return "CoreMenu";
        }

        virtual void initialize(arc::ILibrary& lib)
        {
            lib.display().setTitle("Arcade");
            lib.display().setFramerate(60);
            lib.display().setTileSize(16);
            lib.display().setWidth(25);
            lib.display().setHeight(25);

            arc::FontSpecification normal = {{200, 200, 200, 200}, 16, "assets/regular.ttf"};
            lib.fonts().load("normal", normal);

            arc::FontSpecification game = {{255, 100, 100, 255}, 16, "assets/regular.ttf"};
            lib.fonts().load("game", game);

            arc::FontSpecification library = {{100, 255, 100, 255}, 16, "assets/regular.ttf"};
            lib.fonts().load("library", library);
        }

        virtual void onKeyPressed([[maybe_unused]]arc::ILibrary& lib, arc::Key key)
        {
            switch (key)
            {
            case arc::Key::UP:
                this->_selection = (this->_selection + 1) % _libs.size();
                break;
            case arc::Key::DOWN:
                this->_selection = this->_selection ? (this->_selection - 1) % _libs.size() : _libs.size() - 1;
                break;
            default:
                break;
            }
        }

        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y)
        {
            (void)lib;
            (void)button;
            (void)x;
            (void)y;
        }

        virtual void update(arc::ILibrary& lib, float deltaTime)
        {
            (void)lib;
            (void)deltaTime;
        }

        virtual void draw(arc::ILibrary& lib)
        {
            lib.display().clear();

            for (int i = this->_selection - 1; i <= this->_selection + 1; i++) {
                auto l = i < 0 ? _libs.back() : _libs.at(i % _libs.size());
                auto font = i == this->_selection ? "game" : "normal";
                auto size = lib.display().measure(l->name(), lib.fonts().get(font), 0, 0).width;
                auto x = (lib.display().width() - size) / 2;
                auto y = (this->_selection - i + 1) * 2;
                lib.display().print(l->name(), lib.fonts().get(font), x, y + 1);
            }

            for (int i = this->_selection - 1; i <= this->_selection + 1; i++) {
                auto l = i < 0 ? _libs.back() : _libs.at(i % _libs.size());
                auto font = i == this->_selection ? "library" : "normal";
                auto size = lib.display().measure(l->name(), lib.fonts().get(font), 0, 0).width;
                auto x = (lib.display().width() - size) / 2;
                auto y = (this->_selection - i + 1) * 2;
                lib.display().print(l->name(), lib.fonts().get(font), x, y + 10);
            }

            lib.display().flush();
        }

        std::shared_ptr<arc::IGame> getSelection()
        {
            return this->_libs.at(this->_selection)->get<arc::IGame>();
        }

    private:
        int _selection = 0;
        std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};

class Core
{
    public:
        Core(const std::string& path) : _loader(LibraryLoader("./lib"))
        {
            if (!this->_loader.contains(path))
                throw CoreException("Could not find " + path + ".");
            this->_lib = this->_loader.load(path)->get<arc::ILibrary>();
            if (!this->_loader.contains(arc::SharedLibraryType::GAME))
                throw CoreException("No game library found.");
            this->_game = std::make_shared<CoreMenu>(_loader.libs());
        }

        ~Core()
        {
        }

        void switch_game_lib()
        {
            auto menu = std::dynamic_pointer_cast<CoreMenu>(this->_game);

            if (menu != nullptr) {
                this->_game.reset();
                auto next = menu->getSelection();
                this->_game = next;
            } else {
                this->_game.reset();
                this->_game = std::make_shared<CoreMenu>(_loader.libs());
            }
            this->_game->initialize(*_lib);
        }

        void switch_graphic_lib()
        {
            std::string title = this->_lib->display().title();
            uint32_t framerate = this->_lib->display().framerate();
            std::size_t tileSize = this->_lib->display().tileSize();
            std::size_t width = this->_lib->display().width();
            std::size_t height = this->_lib->display().height();

            auto textures = this->_lib->textures().dump();
            auto fonts = this->_lib->fonts().dump();
            auto sounds = this->_lib->sounds().dump();
            auto musics = this->_lib->musics().dump();

            this->_lib.reset();
            this->_lib = this->_loader.nextLib()->get<arc::ILibrary>();

            if (_lib == nullptr)
                throw std::runtime_error("Failed to load library");

            this->_lib->display().setTitle(title);
            this->_lib->display().setFramerate(framerate);
            this->_lib->display().setTileSize(tileSize);
            this->_lib->display().setWidth(width);
            this->_lib->display().setHeight(height);

            for (const auto& texture : textures)
                this->_lib->textures().load(texture.first, texture.second);

            for (const auto& font : fonts)
                this->_lib->fonts().load(font.first, font.second);

            for (const auto& sound : sounds)
                this->_lib->sounds().load(sound.first, sound.second);

            for (const auto& music : musics)
                this->_lib->musics().load(music.first, music.second);
        }

        void run()
        {
            auto lib_switch = false;
            auto game_switch = false;
            auto before = std::chrono::high_resolution_clock::now();

            _game->initialize(*_lib);
            while (_lib->display().opened()) {
                arc::Event event = {};
                auto now = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                before = now;

                if (lib_switch) {
                    this->switch_graphic_lib();
                    lib_switch = false;
                    continue;
                }

                if (game_switch) {
                    switch_game_lib();
                    game_switch = false;
                    continue;
                }

                _lib->display().update(deltaTime);
                while (_lib->display().pollEvent(event)) {
                    if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::SPACE)
                        lib_switch = true;
                    if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::ENTER)
                        game_switch = true;
                    if (event.type == arc::EventType::KEY_PRESSED)
                        _game->onKeyPressed(*_lib, event.key);
                    if (event.type == arc::EventType::MOUSE_BUTTON_PRESSED)
                        _game->onMouseButtonPressed(*_lib, event.mouse.button, event.mouse.x, event.mouse.y);
                }
                _game->update(*_lib, deltaTime);
                _game->draw(*_lib);
            }
        }

    private:
        std::shared_ptr<arc::ILibrary> _lib = nullptr;
        std::shared_ptr<arc::IGame> _game = nullptr;
        LibraryLoader _loader;
};

int main(int ac, char **av, [[maybe_unused]] char **env)
{
    if (ac != 2) {
        std::cerr << "Wrong argument count" << std::endl;
        return 84;
    }

    try {
        Core core(av[1]);
        core.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
