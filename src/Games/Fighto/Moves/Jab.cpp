/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Jab
*/

#include "AMove.hpp"

/**
 * @brief A Jab is a fast & short-range forwarded attack.
*/
class Jab : public AMove {
    public:
        Jab() : AMove(1.f, 4.f, FRAME(3), FRAME(5), FRAME(3), false)
        {
            this->_hitboxes.push_back(HitBox(dVector(0.8f, -0.25f), 0.3f));
        }

        ~Jab() = default;

    protected:
    private:
};
