/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AAnimation
*/

#pragma once

#include "ILibrary.hpp"
#include "Vector.hpp"

class AAnimation {
    public:
        AAnimation(const std::string& texture);
        virtual ~AAnimation() = default;

        /**
         * @brief Update the animation
         *
         * @param dt Delta time, how much time since last update
         *
         * @return true if the animation has ended, false otherwise
         */
        virtual bool update(double dt);

        /**
         * @brief Draw the animation
         *
         * @param lib The library to draw with
         * @param position The position to draw the animation at
         * @param direction The direction to draw the animation
         */
        virtual void draw(arc::ILibrary& lib, const dVector& position, double direction) const;

        /**
         * @brief Draw the debug of the animation
         *
         * @param lib The library to draw with
         * @param position The position to draw the debug at
         */
        virtual void debug(arc::ILibrary& lib, const dVector& position) const;

        /**
         * @brief Say if the animation need the player to be grounded to end
         *
         * @return true if the animation need the player to be grounded to end, false otherwise
         */
        virtual bool needGround() const { return false; }

    protected:
        const std::string _texture;
        std::string _frame;
        uint32_t _frameIndex = 0;
        std::optional<double> _direction = std::nullopt;

};
