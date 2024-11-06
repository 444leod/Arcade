/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Spike
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Spike animation is a basic animation when the champion spikes
 */
namespace animation {
    class Spike : public AAnimation {
        public:
            Spike(const std::string& texture) : AAnimation(texture + "_idle_")
            {
                _frame = _texture + "0";
                _frameIndex = 0;
            }
            ~Spike() = default;

            static void initialize([[maybe_unused]] arc::ILibrary& lib)
            {
            }

            bool update([[maybe_unused]] double dt) override
            {
                return true;
            }

            void draw(arc::ILibrary& lib, const dVector& position, double direction) const override
            {
                if (_direction.value_or(direction) < 0)
                    lib.display().draw(lib.textures().get(_frame), position.x + 2 - 0.5f, position.y + 1 + 0.3f, -2, -2);
                else
                    lib.display().draw(lib.textures().get(_frame), position.x - 0.5f, position.y + 1 + 0.3f, 2, -2);
            }

            bool needGround() const override { return true; }

        protected:
        private:
            double _dt_sum = 0;
    };
}
