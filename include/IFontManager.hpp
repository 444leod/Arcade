/*
** EPITECH PROJECT, 2024
** IFontManager.hpp
** File description:
** IFontManager.hpp
*/

#pragma once

#include "Datatypes.hpp"

#include <string>
#include <vector>

namespace arc {


    /**
     * @brief Represents a font
     */
    class IFont {
    public:
         ~IFont() = default;

        /**
         * @brief Returns the specification of the font
         *
         * @return const FontSpecification& The specification of the font
         */
        virtual const FontSpecification& specificiation() const = 0;
    };

    /**
     * @brief Represents the font manager
     */
    class IFontManager {
    public:
        ~IFontManager() = default;

        /**
         * @brief Loads a font from a specification
         *
         * @param name the name of the font
         * @param spec the specification of the font
         * @return true if the font was loaded successfully
         * @return false if the font could not be loaded
         */
        virtual bool load(const std::string& name, const FontSpecification& spec) = 0;

        /**
         * @brief Retrieves a fon
         *
         * @param name the name of font
         * @return IFont& the font
         */
        virtual IFont& get(const std::string &name) = 0;

        /**
         * @brief Retrieves all the fonts specifications with their name
         *
         * @return std::vector<TextureSpecification> the specifications of all the textures
         */
        virtual std::vector<std::pair<std::string, FontSpecification>> dump() const = 0;
    };
}
