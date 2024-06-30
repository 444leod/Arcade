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
        Jab(std::uint32_t owner, double direction) : AMove(5.f, dVector(5, 2), false)
        {
            this->_direction = direction;
            this->_owner = owner;
            this->_setTimings(3, 5, 3);
            this->_hitboxes.push_back(HitBox(dVector(0.8f, -0.25f), 0.3f));
        }

        ~Jab() = default;

    protected:
    private:
};
