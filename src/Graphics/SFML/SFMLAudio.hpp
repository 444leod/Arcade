/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLAudio
*/

#pragma once

#include "IMusicManager.hpp"
#include "ISoundManager.hpp"
#include <SFML/Audio.hpp>

class SFMLSound : public arc::ISound {
public:
    SFMLSound() = default;
    virtual ~SFMLSound() = default;

    bool init(const arc::SoundSpecification& spec);
    void setBuffer(void) { this->_sound.setBuffer(this->_buffer); }
    virtual void play() { this->_sound.play(); }
    virtual void stop() { this->_sound.stop(); }
    virtual sf::Sound::Status getStatus() const { return this->_sound.getStatus(); }
    virtual void setVolume(float volume) { this->_sound.setVolume(volume); }

    virtual const arc::SoundSpecification& specification() const { return this->_spec; }
    const sf::Sound& sound() const { return this->_sound; }

private:
    sf::Sound _sound = {};
    sf::SoundBuffer _buffer = {};
    arc::SoundSpecification _spec = {};
};

class SFMLSoundManager : public arc::ISoundManager {
public:
    SFMLSoundManager() = default;
    virtual ~SFMLSoundManager() = default;

    virtual bool load(const std::string& name, const arc::SoundSpecification& spec);
    virtual std::map<std::string, arc::SoundSpecification> dump() const;

    virtual bool isPlaying(const std::string& name);
    virtual std::shared_ptr<arc::ISound> get(const std::string &name);

    virtual void play(const std::string& name, const float volume);
    virtual void stop(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<SFMLSound>> _sounds;
};

class SFMLMusic : public arc::IMusic {
public:
    SFMLMusic() = default;
    virtual ~SFMLMusic() = default;

    bool init(const arc::MusicSpecification& spec);
    virtual void play() { this->_music.play(); }
    virtual void stop() { this->_music.stop(); }
    virtual void setVolume(float volume) { this->_music.setVolume(volume); }
    virtual sf::Music::Status getStatus() const { return this->_music.getStatus(); }

    virtual const arc::MusicSpecification& specification() const { return this->_spec; }
    const sf::Music& music() const { return this->_music; }

private:
    sf::Music _music = {};
    arc::MusicSpecification _spec = {};
};

class SFMLMusicManager : public arc::IMusicManager {
public:
    SFMLMusicManager() = default;
    virtual ~SFMLMusicManager() = default;

    virtual bool load(const std::string& name, const arc::MusicSpecification& spec);
    virtual std::map<std::string, arc::MusicSpecification> dump() const;

    virtual bool isPlaying(const std::string& name);
    virtual std::shared_ptr<arc::IMusic> get(const std::string &name);

    virtual void play(const std::string& name, const float volume);
    virtual void stop(const std::string& name);


private:
    std::map<std::string, std::shared_ptr<SFMLMusic>> _musics;
};
