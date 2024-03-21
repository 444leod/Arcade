/*
** EPITECH PROJECT, 2024
** Arcade-Commons
** File description:
** Datatypes
*/

#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include <variant>

namespace arc {
    /**
     * @brief Represents a color
     */
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    /**
     * @brief Represents a rectangle
     */
    template<typename T>
    struct Rect {
        T x;
        T y;
        T width;
        T height;
    };

    /**
     * @brief Represents a key
     */
    enum class Key {
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V,
        W, X, Y, Z, UP, DOWN, LEFT, RIGHT, SPACE, ENTER, ESCAPE, UNKNOWN
    };

    /**
     * @brief Represents a mouse button
     */
    enum class MouseButton {
        LEFT = 0, RIGHT, MIDDLE, UNKNOWN
    };

    /**
     * @brief Represents an even type
     */
    enum class EventType {
        KEY_PRESSED = 0,
        MOUSE_BUTTON_PRESSED
    };

    /**
     * @brief Represents an event
     */
    struct Event {
        EventType type;
        union {
            Key key;
            struct {
                MouseButton button;
                int32_t x;
                int32_t y;
            } mouse;
        };
    };


    /**
     * @brief Represents the specification required to create a Font
     */
    struct FontSpecification {
        arc::Color color;
        std::size_t size;
        std::string path;
    };


    /**
     * @brief Represents the specification required to create a textual texture
     */
    struct TextureTextualSpecification {
        char character;
        Color color;
    };

    /**
     * @brief Represents an image for a texture
     */
    struct TextureImage {
        std::string path;
        std::optional<Rect<uint32_t>> subrect = std::nullopt;
    };

    /**
     * @brief Represents the specification required to create a graphical texture
     */
    using TextureGraphicalSpecification = std::variant<TextureImage, Color>;

    /**
     * @brief Represents the specification required to create a texture
     */
    struct TextureSpecification {
        TextureTextualSpecification textual;
        TextureGraphicalSpecification graphical;
    };
}
