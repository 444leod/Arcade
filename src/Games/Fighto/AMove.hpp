/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AMove
*/

#pragma once

#include <vector>
#include "HitBox.hpp"
#include "ILibrary.hpp"

#define FRAME(x) x / 60.0

class AMove {
    public:
        AMove() = default;
        /**
         * @param dmg DAMAGE - The amount of damage move inflicts
         * @param kb KNOCKBACK - The amount of knockback move inflicts
         * @param stu STARTUP - The time before the move takes effect
         * @param act ACTIVE - The time the move takes effect
         * @param lag ACTIVE - The time taken for the move to end (innactive)
        */
        AMove(double dmg, double kb, double stu, double act, double lag, bool air);
        ~AMove() = default;

        bool air() const { return this->_air; }
        double damage() const { return this->_damage; }
        double knockback() const { return this->_knockback; }

        /**
         * @brief Updates the attack move progress and its position.
         * @param x The X position of the Champion doing the move
         * @param y The Y position of the Champion doing the move
         * @param dt The frame's delta-time.
         * @return `true` if the move is continuing. `false` if the move has ended.
        */
        virtual bool update(double direction, dVector pos, bool grounded, double dt);

        /**
         * @brief Get the next hitbox in the hitbox poll of the move.
         * @param hitbox A refernce to an hitbox that will be set for polling.
         * @return `true` if successfully poll a hitbox, `false` otherwise.
        */
        virtual bool poll(HitBox& hitbox);

        /**
         * @brief Debug prints the POLL hitboxes on the screen
         * @param library The graphical library to display with
        */
        virtual void debug(arc::ILibrary& library) const;

        /**
         * @brief Interrupts the move to end of active
        */
        virtual void interrupt();

        virtual void addHit(std::uint32_t id)
            { this->_hitIds.push_back(id); }
        virtual bool hasHit(std::uint32_t id) const;

    protected:
        std::vector<HitBox> _hitboxes = {};
    private:
        double _time = .0;
        double _damage = .0;
        double _knockback = .0;
        double _startup = .0;
        double _active = .0;
        double _lag = .0;
        bool _air = false;
        std::vector<HitBox> _poll = {};
        std::vector<std::uint32_t> _hitIds = {};
};
