/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** TamatoBerry
*/

#pragma once

#include "SnakeLib/GameObject/AGameObject.hpp"

class TamatoBerry : public AGameObject{
    public:
        TamatoBerry(Vec2i pos);
        
        ~TamatoBerry() = default;

        void applyEffect(SnakeObject &snake) override;

    protected:
    private:
};
