/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Idle
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Idle animation is a basic animation when the champion is not moving.
 */
namespace animation {
    class Idle : public AAnimation {
        public:
            Idle(const std::string& texture) : AAnimation(texture + "_idle_")
            {
                _frame = _texture + "0";
                _frameIndex = 0;
            }
            ~Idle() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Idle/Player Idle 48x48.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 10; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_idle_" + std::to_string(i), spec);
                }
            }

            bool update(double dt) override
            {
                if (_dt_sum > 0.1) {
                    _frameIndex++;
                    if (_frameIndex == 10) {
                        _frameIndex = 0;
                    }
                    _frame = _texture + std::to_string(_frameIndex);
                    _dt_sum -= 0.1;

                }
                _dt_sum += dt;
                return (_frameIndex >= 6);
            }

        protected:
        private:
            double _dt_sum = 0;
    };
}
