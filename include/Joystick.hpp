/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Joystick
*/

#pragma once

#include <cstdint>
#include <map>

namespace arc {

    struct JoyAxis {
        double x = .0;
        double y = .0;
    };

    class Joystick {
        public:
            Joystick() = default;
            ~Joystick() = default;

            JoyAxis axis() const { return this->_axis; }
            double x() const { return this->_axis.x; }
            double y() const { return this->_axis.y; }

            void setAxis(double x, double y)
                { this->_axis = (JoyAxis){x, y}; }

        protected:
        private:
            JoyAxis _axis;
    };
}
