#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

template <typename U>
class ImperialStarship {
    U shield, attackPower;
public:
    constexpr ImperialStarship (U shield, U attackPower)
    : shield(shield), attackPower(attackPower) {}

    U getShield () {
        return shield;
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
    static constexpr bool isExplorer () {return false;}
    constexpr bool isImperial () const {return true;}
};

template <typename I, typename R>
void attack (I &imperialShip, R &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    if (!rebelShip.isExplorer()) {
        imperialShip.takeDamage(rebelShip.getAttackPower());
    }
};

template <typename U>
using DeathStar = ImperialStarship<U>;
template <typename U>
using ImperialDestroyer = ImperialStarship<U>;
template <typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H
