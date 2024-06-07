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
class Kick : public AMove {
    public:
        Kick() : AMove(15.f, 3.f, FRAME(4), FRAME(6), FRAME(4), false)
        {
            this->_hitboxes.push_back(HitBox(dVector(1.f, 0.35f), 0.3f));
            this->_hitboxes.push_back(HitBox(dVector(0.8f, 0.35f), 0.3f));
        }

        ~Kick() = default;

    protected:
    private:
};
