/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Kick
*/

#include "AMove.hpp"

/**
 * @brief A Kick is a fast & medium-range forwarded attack that hits low.
*/
namespace move {
    class Kick : public AMove {
        public:
            Kick(std::uint32_t owner, double direction) : AMove(7.f, dVector(2, 3), false)
            {
                this->_direction = direction;
                this->_owner = owner;
                this->_setTimings(4, 6, 4);
                this->_hitboxes.push_back(HitBox(dVector(1.f, 0.35f), 0.3f));
                this->_hitboxes.push_back(HitBox(dVector(0.8f, 0.35f), 0.3f));
            }

            std::shared_ptr<AAnimation> animation([[maybe_unused]] const std::string& skin) override
            {
                return nullptr;
            }

            ~Kick() = default;

        protected:
        private:
    };
}
