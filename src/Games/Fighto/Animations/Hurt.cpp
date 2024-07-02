/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Hurt
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Hurt animation is a basic animation when the champion is hurt
 */
namespace animation {
    class Hurt : public AAnimation {
        public:
            Hurt(const std::string& texture) : AAnimation(texture + "_hurt_")
            {
                _frame = _texture + "0";
                _frameIndex = 0;
            }
            ~Hurt() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Hurt-Damaged/Player Hurt 48x48.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 4; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_hurt_" + std::to_string(i), spec);
                }
            }

            bool update(double dt) override
            {
                if (_dt_sum > 0.015f) {
                        _frameIndex++;
                    if (_frameIndex == 4)
                        return true;
                    _frame = _texture + std::to_string(_frameIndex);
                    _dt_sum -= 0.05f;
                }
                _dt_sum += dt;
                return false;
            }

        protected:
        private:
            double _dt_sum = 0;
    };
}
