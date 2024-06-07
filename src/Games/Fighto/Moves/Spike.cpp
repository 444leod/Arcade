/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Spike
*/

#include "AMove.hpp"

/**
 * @brief A Spike is a slow aerial downwards attack.
*/
class Spike : public AMove {
    public:
        Spike() : AMove(15.f, 10.f, FRAME(5), FRAME(15), FRAME(15), true)
        {
            this->_hitboxes.push_back(HitBox(dVector(0.f, 0.8f), 0.3f));
            this->_hitboxes.push_back(HitBox(dVector(0.f, 1.1f), 0.3f));
        }

        ~Spike() = default;

    protected:
    private:
};
