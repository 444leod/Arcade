/*
** EPITECH PROJECT, 2024
** ISoundManager.hpp
** File description:
** ISoundManager.hpp
*/

#pragma once

#include <string>
#include <vector>

namespace arc {

    /**
     * @brief Represents the specification required to create a sound
     */
    struct SoundSpecification {
        std::string path;
    };

    /**
     * @brief Represents a sound
     */
    class ISound {
    public:
        virtual ~ISound() = default;

        /**
         * @brief Returns the specification required to create the sound
         *
         * @return const SoundSpecification& The specification required to create the sound
         */
        virtual const SoundSpecification& specification() const = 0;
    };

    /**
     * @brief Represents a sound manager
     */
    class ISoundManager {
    public:
        virtual ~ISoundManager() = default;

        /**
         * @brief Loads a sound
         *
         * @param name the name of the sound
         * @param specification the specification required to create the sound
         * @return true if the sound has been loaded
         * @return false if the sound failed to load
         */
        virtual bool load(const std::string& name, const SoundSpecification& specification) = 0;

        /**
         * @brief Retrieves all the sounds specifications with their name
         *
         * @return std::vector<SoundSpecification> the specifications of all the sounds
         */
        virtual std::vector<std::pair<std::string, SoundSpecification>> dump() const = 0;

        /**
         * @brief Plays a sound
         *
         * @param name the name of the sound
         */
        virtual void play(const std::string& name, const float volume) = 0;

        /**
         * @brief Stops a sound
         *
         * @param name the name of the sound
         */
        virtual void stop(const std::string& name) = 0;
    };
}
