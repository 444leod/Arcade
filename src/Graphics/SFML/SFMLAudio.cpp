/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLAudio
*/

#include "SFMLAudio.hpp"



///////////////////////////////////////////////////////////////////////////////
//
//    SOUND RELATED

bool SFMLSound::init(const arc::SoundSpecification &spec)
{
    this->_spec = spec;
    if (!this->_buffer.loadFromFile(spec.path))
    {
        const int sampleRate = 44100;

        std::vector<sf::Int16> samples(sampleRate);
        for (size_t i = 0; i < samples.size(); ++i)
        {
            samples[i] = 0;
        }

        this->_buffer.loadFromSamples(&samples[0], samples.size(), 1, sampleRate);
    }
    return true;
}

bool SFMLSoundManager::load(const std::string &name, const arc::SoundSpecification &spec)
{
    auto sound = std::make_shared<SFMLSound>();

    if (!sound->init(spec))
        return false;

    this->_sounds[name] = sound;
    this->_sounds[name]->setBuffer();
    return true;
}

std::shared_ptr<arc::ISound> SFMLSoundManager::get(const std::string &name)
{
    return this->_sounds.at(name);
}

std::map<std::string, arc::SoundSpecification> SFMLSoundManager::dump() const
{
    auto specs = std::map<std::string, arc::SoundSpecification>{};

    for (auto &[name, sound] : this->_sounds)
    {
        specs[name] = sound->specification();
    }

    return specs;
}

void SFMLSoundManager::play(const std::string &name, const float volume)
{
    this->_sounds.at(name)->setVolume(volume);
    this->_sounds.at(name)->play();
}

void SFMLSoundManager::stop(const std::string &name)
{
    this->_sounds.at(name)->stop();
}

bool SFMLSoundManager::isPlaying(const std::string &name)
{
    return this->_sounds.at(name)->getStatus() == sf::Sound::Playing;
}



///////////////////////////////////////////////////////////////////////////////
//
//    MUSIC RELATED

bool SFMLMusic::init(const arc::MusicSpecification &spec)
{
    this->_spec = spec;
    if (!this->_music.openFromFile(spec.path))
        return false;

    this->_music.setLoop(spec.loop);
    if (spec.startOffset != -1)
        this->_music.setPlayingOffset(sf::seconds(spec.startOffset));
    if (spec.isPlaying)
        this->_music.play();
    return true;
}

bool SFMLMusicManager::load(const std::string &name, const arc::MusicSpecification &spec)
{
    auto music = std::make_shared<SFMLMusic>();

    if (!music->init(spec))
        return false;

    this->_musics[name] = music;
    return true;
}

std::shared_ptr<arc::IMusic> SFMLMusicManager::get(const std::string &name)
{
    return this->_musics.at(name);
}

std::map<std::string, arc::MusicSpecification> SFMLMusicManager::dump() const
{
    auto specs = std::map<std::string, arc::MusicSpecification>{};

    for (auto &[name, music] : this->_musics)
    {
        arc::MusicSpecification spec = music->specification();
        spec.isPlaying = music->getStatus() == sf::Music::Playing;
        if (spec.isPlaying)
            spec.startOffset = music->music().getPlayingOffset().asSeconds();

        specs[name] = spec;
    }

    return specs;
}

void SFMLMusicManager::play(const std::string &name, const float volume)
{
    this->_musics.at(name)->setVolume(volume);
    this->_musics.at(name)->play();
}

void SFMLMusicManager::stop(const std::string &name)
{
    this->_musics.at(name)->stop();
}

bool SFMLMusicManager::isPlaying(const std::string &name)
{
    return this->_musics.at(name)->getStatus() == sf::Music::Playing;
}
