/*
** EPITECH PROJECT, 2024
** IMusicManager.hpp
** File description:
** IMusicManager.hpp
*/

#pragma once

#include <string>
#include <variant>
#include <vector>
#include <optional>

namespace arc {

    /**
     * @brief Represents the specification required to create a music
     */
    struct MusicSpecification {
        std::string path;
        bool loop;
        float startOffset = -1;
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
         * @brief Retrieves a music
         *
         * @param name the name of the music
         * @return IMusic& the music
         */
        virtual IMusic& get(const std::string& name) = 0;

        /**
         * @brief Retrieves all the musics specifications with their name
         *
         * @return std::vector<MusicSpecification> the specifications of all the musics
         */
        virtual std::vector<std::pair<std::string, MusicSpecification>> dump() const = 0;
    };
}
