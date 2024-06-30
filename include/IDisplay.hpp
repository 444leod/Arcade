/*
** EPITECH PROJECT, 2024
** Display.hpp
** File description:
** Display.hpp
*/

#pragma once

#include "Joystick.hpp"
#include "IFontManager.hpp"
#include "ITextureManager.hpp"

namespace arc {
    /**
     * @brief Represents a key
     */
    enum class KeyCode {
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V,
        W, X, Y, Z, UP, DOWN, LEFT, RIGHT, SPACE, ENTER, TAB, DELETE, ESCAPE, UNKNOWN
    };

    /**
     * @brief Represents a mouse button
     */
    enum class MouseButton {
        LEFT = 0, RIGHT, MIDDLE, UNKNOWN
    };

    enum class JoystickButton {
        Cross = 0, Circle, Triangle, Square, L1, R1, L2, R2, SHARE, START, UNKNOWN, LEFT_JOYSTICK, RIGHT_JOYSTICK, END
    };

    /**
     * @brief Represents an even type
     */
    // enum class EventType {
    //     KEY_PRESSED = 0,
    //     MOUSE_BUTTON_PRESSED,
    //     JOYSTICK_BUTTON_PRESSED,
    //     KEY_DOWN,
    //     MOUSE_BUTTON_DOWN,
    //     JOYSTICK_BUTTON_DOWN,
    //     KEY_RELEASED,

    // };

    enum class KeyType {
        KEY,
        MOUSE_BUTTON,
        JOYSTICK,
        JOYSTICK_BUTTON,
    };

    enum class EventType {
        PRESSED,
        DOWN,
        RELEASED,
        MOVE
    };

    /**
     * @brief Represents an event
     */
    struct Event {
        EventType eventType;
        KeyType keyType;

        union {
            struct {
                KeyCode code;
                bool shift;
            } key;
            struct {
                MouseButton button;
                int32_t x;
                int32_t y;
            } mouse;
            struct {
                union {
                    arc::JoystickAxis axis;
                    arc::JoystickButton button;
                };
                int32_t id;
            } joystick;
        };
    };

    /**
     * @brief Represents a display. This could be a window or a terminal.
     */
    class IDisplay {
    public:
        virtual ~IDisplay() = default;

        /**
         * @brief Sets the title of the display
         *
         * @param title the title of the display
         */
        virtual void setTitle(const std::string& title) = 0;

        /**
         * @brief Sets the max framerate of the display
         *
         * @param framerate the limit framerate
         */
        virtual void setFramerate(uint32_t framerate) = 0;

        /**
         * @brief Sets the size of a single tile
         *
         * @param size the size of a single tile
         */
        virtual void setTileSize(std::size_t size) = 0;

        /**
         * @brief Sets the number of tiles per row
         *
         * @param width the number of tiles per row
         */
        virtual void setWidth(std::size_t width) = 0;

        /**
         * @brief Sets the number of tiles per column
         *
         * @param height the number of tiles per column
         */
        virtual void setHeight(std::size_t height) = 0;

        /**
         * @brief Sets the delay between key down events
         *
         * @param delay the delay between key down events
         */
        virtual void setKeyDownDelay(arc::KeyCode key, float delay) = 0;

        /**
         * @brief Returns the title of the display
         *
         * @return std::string The title
         */
        virtual std::string title() const = 0;

        /**
         * @brief Returns the framerate limit of the display
         *
         * @return uint32_t The framerate limit
         */
        virtual uint32_t framerate() const = 0;

        /**
         * @brief Returns the size of tiles
         *
         * @return std::size_t The size of tiles
         */
        virtual std::size_t tileSize() const = 0;

        /**
         * @brief Returns the number of columns of the display
         *
         * @return std::size_t the number of columns
         */
        virtual std::size_t width() const = 0;

        /**
         * @brief Returns the number of rows of the display
         *
         * @return std::size_t the number of rows
         */
        virtual std::size_t height() const = 0;

        /**
         * @brief Returns whether the display is opened
         *
         * @return true if the display is opened
         * @return false if the display is closed
         */
        virtual bool opened() const = 0;

        /**
         * @brief Closes the display
         */
        virtual void close() = 0;

        /**
         * @brief Poll events
         *
         * @param event the event to fill
         * @return true if there was an event
         * @return false if there was no event
         */
        virtual bool pollEvent(Event& event) = 0;

        /**
         * @brief Returns the position of the mouse
         *
         * @return const std::pair<int32_t, int32_t>& the position of the mouse
         */
        virtual const std::pair<int32_t, int32_t> mousePosition() const = 0;

        /**
         * @brief Gets the data relative to a certain joystick.
         *
         * @param id The id of the Joystick. 0 => P1, 1 => P2, ...
         * @return A const reference to a `Joystick`.
        */
        virtual const Joystick& joystick(std::uint16_t id) const = 0;

        /**
         * @brief Updates the display. For instance, this could be used poll
         *        events or compute frame rate.
         */
        virtual void update(float deltaTime) = 0;

        /**
         * @brief Clears the display
         *
         * @param color the color to clear the display with
         */
        virtual void clear(Color color = {0, 0, 0, 255}) = 0;

        /**
         * @brief Draws a texture to the display
         *
         * @param texture the texture to draw
         * @param x the column to draw the texture at
         * @param y the row to draw the texture at
         */
        virtual void draw(std::shared_ptr<ITexture> texture, float x, float y) = 0;

        /**
         * @brief Draws a texture to the display
         *
         * @param texture the texture to draw
         * @param x the column to draw the texture at
         * @param y the row to draw the texture at
         * @param scaleX the scale on the x axis
         * @param scaleY the scale on the y axis
         */
        virtual void draw(std::shared_ptr<ITexture> texture, float x, float y, float scaleX, float scaleY) = 0;

        /**td::shared_ptr<ITexture> g
         * @brief Draws a string to the display
         *
         * @param string the string to draw
         * @param font the font to use
         * @param x the column to draw the texture at
         * @param y the row to draw the texture at
         */
        virtual void print(const std::string& string, std::shared_ptr<IFont> font, float x, float y) = 0;

        /**
         * @brief Returns the size of a string when printed
         *
         * @param string the string to measure
         * @param font the font to use
         * @return Rect the size of the string when printed
         */
        virtual Rect<float> measure(const std::string& string, std::shared_ptr<IFont> font, float x, float y) = 0;

        /**
         * @brief Flushes what has been drawn to the display.
         */
        virtual void flush() = 0;
    };
};
