/*
** EPITECH PROJECT, 2024
** Display.hpp
** File description:
** Display.hpp
*/

#pragma once

#include "IFontManager.hpp"
#include "ITextureManager.hpp"
#include "ISoundManager.hpp"
#include "IMusicManager.hpp"

namespace arc {
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
        virtual void draw(const ITexture& texture, float x, float y) = 0;

        /**
         * @brief Draws a string to the display
         *
         * @param string the string to draw
         * @param font the font to use
         * @param x the column to draw the texture at
         * @param y the row to draw the texture at
         */
        virtual void print(const std::string& string, const arc::IFont& font, float x, float y) = 0;

        /**
         * @brief Returns the size of a string when printed
         *
         * @param string the string to measure
         * @param font the font to use
         * @return Rect the size of the string when printed
         */
        virtual Rect<float> measure(const std::string& string, const arc::IFont& font, float x, float y) = 0;

        /**
         * @brief Plays a sound
         *
         * @param sound the sound to play
         * @param volume the volume of the sound
         */
        virtual void playSound(const arc::ISound& sound, const float volume) = 0;

        /**
         * @brief Stops a sound
         *
         * @param sound the sound to stop
         */
        virtual void stopSound(const arc::ISound& sound) = 0;

        // /**
        //  * @brief Plays a music
        //  *
        //  * @param music the music to play
        //  * @param volume the volume of the music
        //  */
        // virtual void playMusic(const arc::IMusic& music, const float volume) = 0;

        // /**
        //  * @brief Stops a music
        //  *
        //  * @param music the music to stop
        //  */
        // virtual void stopMusic(const arc::IMusic& music) = 0;

        /**
         * @brief Flushes what has been drawn to the display.
         */
        virtual void flush() = 0;
    };
};
