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

    struct JoystickAxis {
        double x;
        double y;
    };

    class Joystick {
        public:
            Joystick() = default;
            ~Joystick() = default;

            JoystickAxis axis() const { return this->_axis; }
            double x() const { return this->_axis.x; }
            double y() const { return this->_axis.y; }

            void setAxis(double x, double y)
                { this->_axis = (JoystickAxis){x, y}; }

        protected:
        private:
            JoystickAxis _axis = {0, 0};
    };
}
