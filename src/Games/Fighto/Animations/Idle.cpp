/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Idle
*/

#include "AAnimation.hpp"

/**
 * @brief Idle animation is a basic animation when the champion is not moving.
 */
class Idle : public AAnimation {
    public:
        Idle(const std::string& texture) : AAnimation(texture + "_idle_")
        {
            _frame = _texture + "0";
            _frameIndex = 0;
        }
        ~Idle() = default;

        void update(double dt) override
        {
            static double dtSum = 0;

            if (dtSum > 0.1) {
                    _frameIndex++;
                if (_frameIndex == 10)
                    _frameIndex = 0;
                _frame = _texture + std::to_string(_frameIndex);
                dtSum -= 0.1;
            }
            dtSum += dt;
        }

    protected:
    private:
};
