/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Death
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Death animation is a basic animation when the champion dies
 */
namespace animation {
    class Death : public AAnimation {
        public:
            Death(const std::string& texture) : AAnimation(texture + "_death_")
            {
                _frame = _texture + "0";
                _frameIndex = 0;
            }
            ~Death() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Death/Player Death 64x64.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 10; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_death_" + std::to_string(i), spec);
                }
            }

            bool update(double dt) override
            {
                if (_dt_sum > 0.1) {
                    _frameIndex++;
                    if (_frameIndex == 10)
                        return true;
                    _frame = _texture + std::to_string(_frameIndex);
                    _dt_sum -= 0.1;
                }
                _dt_sum += dt;
                return false;
            }

        protected:
        private:
            double _dt_sum = 0;
    };
}
