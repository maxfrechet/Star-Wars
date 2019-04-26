#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <iostream>
#include <tuple>
#include <cstddef>
#include <algorithm>
#include "imperialfleet.h"
#include "rebelfleet.h"

template <typename T , T t0, T t1, typename... S>
class SpaceBattle {
    static_assert(t1 >= t0, "t1 < t0");
    static_assert(t0 >= 0, "t0 < 0");

public:
    constexpr SpaceBattle (S... fleets)
    : clock(t0), fleets(fleets ...) {
        shipCount(this->fleets);
    }

    size_t countImperialFleet () {
        return count_imperials;
    }

    size_t countRebelFleet () {
        return count_rebels;
    }

    void tick (T timeStep) {
        if (!count_rebels && !count_imperials) {
            std::cout << "DRAW\n";
        } else if (!count_rebels) {
            std::cout << "IMPERIUM WON\n";
        } else if (!count_imperials) {
            std::cout << "REBELLION WON\n";
        } else {
            if (std::binary_search(squares_Table().begin(), squares_Table().end(), clock))
                imperial_attack(fleets);
        }
        clock += timeStep;
        clock %= (t1 + 1);
    }

private:
    T clock;
    size_t count_rebels = 0;
    size_t count_imperials = 0;
    std::tuple<S...> fleets;

    template <size_t n = 0, typename ...Fl>
    constexpr void shipCount (std::tuple<Fl...> &s) {
        if constexpr (n < sizeof... (Fl)) {
            if (std::get<n>(s).isImperial()) {
                count_imperials++;
            } else {
                count_rebels++;
            }
            shipCount<n + 1>(s);
        }
    }

    static constexpr size_t square_limit () {
        size_t n = 0;
        while (n * n < t1)
            n = n + 1;
        return n;
    }

    static constexpr auto squares_Table () {
        std::array<T, square_limit()> square_table{};

        for (T i = 0; i < (T) square_limit(); i++) {
            square_table[i] = i * i;
        }
        return square_table;
    }

    template <size_t n = 0, typename E, typename ... Fl>
    constexpr void rebel_attack (std::tuple<Fl ...> &s, E &enemy) {
        if constexpr (n < sizeof... (Fl)) {
            if (!std::get<n>(s).isImperial()) {
                if (std::get<n>(s).getShield()) {
                    attack(enemy, std::get<n>(s));
                }
                if (!enemy.getShield()) count_imperials--;
                if (!std::get<n>(s).getShield()) count_rebels--;
            }
            rebel_attack<n + 1>(s, enemy);
        }
    }

    template <size_t n = 0, typename ... Fl>
    constexpr void imperial_attack(std::tuple<Fl ...> &s) {
        if constexpr (n < sizeof... (Fl)) {
            if(std::get<n>(s).isImperial()) {
                if (std::get<n>(s).getShield()) {
                    rebel_attack(s, std::get<n>(s));
                }
            }
            imperial_attack<n + 1>(s);
        }
    }
};

#endif //STARWARS_BATTLE_H