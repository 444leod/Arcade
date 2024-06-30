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
         * @param aerian AERIAN - Wether the move is aerian
        */
        AMove(double dmg, dVector kb, bool air);
        ~AMove() = default;

        std::uint32_t owner() const { return this->_owner; }
        double damage() const { return this->_damage; }
        dVector knockback() const { return this->_knockback; }
        bool aerian() const { return this->_aerian; }

        /**
         * @brief Updates the attack move progress and its position.
         * @param pos The position of the character effecting to move
         * @param grounded Wether the character is grounded this frame
         * @param dt The frame's delta-time.
         * @return `true` if the move is continuing. `false` if the move has ended.
        */
        virtual bool update(dVector pos, bool grounded, double dt);

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

        /**
         * @brief Add a player id to the list of hit players
         * @param id The player's ID
        */
        virtual void addHit(std::uint32_t id)
            { this->_hitIds.push_back(id); }

        /**
         * @brief Check wether a player was already hit.
         * @param id The player's ID
        */
        virtual bool hasHit(std::uint32_t id) const;

    protected:
        std::uint32_t _owner = 0;
        double _direction = .0;
        std::vector<HitBox> _hitboxes = {};

    protected:
        /**
         * @brief Sets the timing frames of the move
        */
        void _setTimings(uint8_t stu, uint8_t act, uint8_t lag);

    private:
        double _damage = .0;
        dVector _knockback;
        bool _aerian = false;

    private:
        double _time = .0;
        double _startup = .0;
        double _active = .0;
        double _lag = .0;

    private:
        std::vector<HitBox> _poll = {};
        std::vector<std::uint32_t> _hitIds = {};
};
