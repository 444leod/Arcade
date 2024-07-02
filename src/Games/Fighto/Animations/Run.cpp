/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Run
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Run animation is a basic animation when the champion is running
 */
namespace animation {
    class Run : public AAnimation {
        public:
            Run(const std::string& texture) : AAnimation(texture + "_run_")
            {
                _frame = _texture + "0";
                _frameIndex = 0;

            }
            ~Run() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Run/player run 48x48.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 8; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_run_" + std::to_string(i), spec);
                }
            }

            bool update(double dt) override
            {
                if (_dtSum > 0.1) {
                    _frameIndex++;
                    if (_frameIndex == 8)
                        return true;
                    _frameIndex = _frameIndex % 8;
                    _frame = _texture + std::to_string(_frameIndex);
                    _dtSum -= 0.1;
                }
                _dtSum += dt;
                return false;
            }

        protected:
        private:
            double _dtSum = 0;
    };
}
