/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Jab
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Jab animation is a basic animation when the champion punch
 */
namespace animation {
    class Jab : public AAnimation {
        public:
            Jab(const std::string& texture, double direction) : AAnimation(texture + "_jab_")
            {
                _frame = _texture + "0";
                _frameIndex = 1;
                _direction = direction;
            }
            ~Jab() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Punch Jab/Player Jab 48x48.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 10; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_jab_" + std::to_string(i), spec);
                }
            }

            bool update(double dt) override
            {
                if (_dt_sum > 0.016f) {
                    _frameIndex++;
                    if (_frameIndex == 8)
                        return true;
                    _frame = _texture + std::to_string(_frameIndex);
                    _dt_sum -= 0.016;
                }
                _dt_sum += dt;
                return false;
            }

        protected:
        private:
            double _dt_sum = 0;
    };
}
