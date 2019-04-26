#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include<iostream>
#include <cassert>

template <typename U, bool isStar>
class RebelStarship {
    U shield, speed, attackPower;
    static constexpr int StarCruiser_min = 99999;
    static constexpr int StarCruiser_max = 299795;
    static constexpr int general_min = 299796;
    static constexpr int general_max = 2997960;
    bool explorer = false;
public:
    constexpr RebelStarship (U shield, U speed, U attackPower):
    shield(shield), speed(speed), attackPower(attackPower) {
        if (isStar)
            assert(StarCruiser_min <= speed && speed <= StarCruiser_max);
        else
            assert(general_min <= speed && speed <= general_max);
    }

    constexpr RebelStarship (U shield, U speed):
    shield(shield), speed(speed) {
        explorer = true;
        assert(general_min <= speed && speed <= general_max);
    }

    U getShield () {
        return shield;
    }

    U getSpeed () {
        return speed;
    }

    U getAttackPower() {
        return attackPower;
    }

    void takeDamage(U damage) {
        if (shield < damage) {
            shield = 0;
        } else {
            shield = shield - damage;
        }
    }
    constexpr bool isExplorer () {return explorer;}
    constexpr bool isImperial () const {return false;}
};

template <typename U>
using XWing = RebelStarship<U, false>;
template <typename U>
using StarCruiser = RebelStarship<U, true>;
template <typename U>
using Explorer = RebelStarship<U, false>;

#endif //STARWARS_REBELFLEET_H
