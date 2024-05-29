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

            enum JoystickButton : std::uint16_t
                { Cross = 0, Square, Circle, Triangle, L1, R1, L2, R2, END };

            Joystick() = default;
            ~Joystick() = default;

            JoyAxis axis() const { return this->_axis; }
            double x() const { return this->_axis.x; }
            double y() const { return this->_axis.y; }
            bool isButtonPressed(JoystickButton key) const { return this->_inputs.at(key); }

            void setAxis(double x, double y)
                { this->_axis = (JoyAxis){x, y}; }

            void setButton(JoystickButton key, bool val = true)
                { this->_inputs.at(key) = val; }

        protected:
        private:
            JoyAxis _axis;
            std::map<JoystickButton, bool> _inputs = {
                { Cross,    false },
                { Square,   false },
                { Circle,   false },
                { Triangle, false },
                { L1,       false },
                { R1,       false },
                { L2,       false },
                { R2,       false },
            };
    };
}
