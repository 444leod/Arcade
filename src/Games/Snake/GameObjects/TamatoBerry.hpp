/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** TamatoBerry
*/

#pragma once

#include "SnakeLib/GameObject/AGameObject.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

class TamatoBerry : public AGameObject {
    public:
        TamatoBerry(Vec2i pos);
        
        ~TamatoBerry() = default;

        void applyEffect(ASnakeObject &snake) override;

    protected:
    private:
};
