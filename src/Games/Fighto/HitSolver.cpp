/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitSolver
*/

#include "ChampionManager.hpp"

class HitSolver {
    public:
        static void solve(ChampionManager& champs)
        {
            HitBox hb;
            std::vector<std::shared_ptr<AMove>> moves = {};

            // Gather all the moves
            for (auto c : champs.champions()) {
                auto m = c->move();
                if (m == nullptr) continue;
                moves.push_back(m);
            }

            // Solve all moves
            for (auto c : champs.champions()) {
                if (!c->alive()) continue;
                for (auto move : moves) {
                    if (move->owner() == c->id() || move->hasHit(c->id()))
                        continue;
                    while (move->poll(hb)) {
                        if (!hb.overlaps(c->position(), c->size()))
                            continue;

                        double strength = 1.0 + (100.0 - c->life()) * 0.01;
                        double direction = c->position().x - champs.getById(move->owner())->position().x;
                        direction = direction / std::abs(direction);
                        dVector kb(move->knockback().x * direction, move->knockback().y);
                        c->damage(move->damage(), kb * strength, 2.0);
                        move->addHit(c->id());
                        break;
                    }
                }
            }

            for (auto m : moves)
                while (m->poll(hb)) ;
        }
};
