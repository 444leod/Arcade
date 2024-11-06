/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Jump
*/

#include "AAnimation.hpp"
#include <iostream>

/**
 * @brief Jump animation is a basic animation when the champion jump
 */
namespace animation {
    class Jump : public AAnimation {
        public:
            Jump(const std::string& texture, const dVector& velocity) : AAnimation(texture + "_jump_"), _velocity(velocity)
            {
                _frame = _texture + "0";
                _frameIndex = 0;
            }
            ~Jump() = default;

            static void initialize(arc::ILibrary& lib)
            {
                arc::TextureSpecification spec;
                arc::TextureImage image = arc::TextureImage{
                    .path = "assets/fighto/Player Jump/player jump 48x48.png",
                    .subrect = arc::Rect<uint32_t>{0, 0, 48, 48}
                };

                for (uint8_t i = 0; i < 3; i++) {
                    image.subrect->x = i * 48;
                    spec.graphical = image;
                    lib.textures().load("template_jump_" + std::to_string(i), spec);
                }
            }

            bool update([[maybe_unused]] double dt) override
            {
                if (_velocity.y < -1 && _frameIndex != 2) {
                    _frameIndex = 2;
                    _frame = _texture + std::to_string(_frameIndex);
                } else if ((_velocity.y > 1 && _velocity.y < -1) && _frameIndex != 1) {
                    _frameIndex = 1;
                    _frame = _texture + std::to_string(_frameIndex);
                } else if (_velocity.y == 0 && _frameIndex == 2) {
                    return true;
                }
                return false;
            }

        protected:
        private:
            double _dt_sum = 0;
            const dVector& _velocity;
    };
}
