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
        Spike(std::uint32_t owner, double direction) : AMove(15.f, dVector(10, 2), true)
        {
            this->_direction = direction;
            this->_owner = owner;
            this->_setTimings(7, 15, 15);
            this->_hitboxes.push_back(HitBox(dVector(0.f, 0.8f), 0.3f));
            this->_hitboxes.push_back(HitBox(dVector(0.f, 1.1f), 0.3f));
        }

        ~Spike() = default;

    protected:
    private:
};
