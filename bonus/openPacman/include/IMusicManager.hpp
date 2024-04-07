/*
** EPITECH PROJECT, 2024
** IMusicManager.hpp
** File description:
** IMusicManager.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace arc {

    /**
     * @brief Represents the specification required to create a music
     */
    struct MusicSpecification {
        std::string path;
        bool loop;
        float startOffset = 0;
        bool isPlaying = false;
    };

    /**
     * @brief Represents a music
     */
    class IMusic {
    public:
        virtual ~IMusic() = default;

        /**
         * @brief Returns the specification required to create the music
         *
         * @return const MusicSpecification& The specification required to create the music
         */
        virtual const MusicSpecification& specification() const = 0;
    };

    /**
     * @brief Represents a music manager
     */
    class IMusicManager {
    public:
        virtual ~IMusicManager() = default;

        /**
         * @brief Loads a music
         *
         * @param name the name of the music
         * @param specification the specification required to create the music
         * @return true if the music has been loaded
         * @return false if the music failed to load
         */
        virtual bool load(const std::string& name, const MusicSpecification& specification) = 0;

        /**
         * @brief Retrieves all the musics specifications with their name
         *
         * @return std::vector<MusicSpecification> the specifications of all the musics
         */
        virtual std::map<std::string, MusicSpecification> dump() const = 0 ;

        /**
         * @brief Plays a music
         *
         * @param name the name of the music
         */
        virtual void play(const std::string& name, const float volume) = 0;

        /**
         * @brief Stops a music
         *
         * @param name the name of the music
         */
        virtual void stop(const std::string& name) = 0;

        /**
         * @brief get whether the music is playing
         *
         * @param name the name of the music
         */
        virtual bool isPlaying(const std::string& name) = 0;
    };
}
