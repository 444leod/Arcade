/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitSolver
*/

#include "Champion.hpp"

class HitSolver {
    public:
        static void solve(std::vector<Champion>& champions)
        {
            std::vector<OwnedHit> hits = {};

            for (std::uint32_t i = 0; i < champions.size(); i++) {
                auto m = champions.at(i).move();
                if (m == nullptr) continue;
                HitBox hitbox;
                while (m->poll(hitbox)) {
                    hits.push_back({ i, m, hitbox });
                }
            }

            for (std::uint32_t i = 0; i < champions.size(); i++) {
                auto& champ = champions.at(i);

                for (auto& hit : hits) {
                    if (hit.owner == i || hit.move->hasHit(i))
                        continue;
                    if (!hit.hit.overlaps(champ.position(), champ.size()))
                        continue;
                    dVector knockback(
                        hit.move->knockback() * -champ.direction(),
                        hit.move->knockback());
                    champ.damage(hit.move->damage(), knockback, 2.0);
                    hit.move->addHit(i);
                }
            }
        }

    private:
        struct OwnedHit
        {
            std::uint32_t owner;
            std::shared_ptr<AMove> move;
            HitBox hit;
        };
};
