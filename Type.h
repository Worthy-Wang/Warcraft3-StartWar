#ifndef _WARCRAFT_TYPE_H_
#define _WARCRAFT_TYPE_H_
#include <memory>
#include <iostream>
#include <string>
#define MAX_WEAPON_SIZE 10
using std::string;
namespace warcraft
{

enum ColorType
{
    RED,
    BLUE
};

enum WarriorType
{
    DRAGON,
    NINJA,
    ICEMAN,
    LION,
    WOLF
};


enum WeaponType
{
    SWORD,
    BOMB,
    ARROW
};

inline string toString(WeaponType weapon)
{
    switch(weapon)
    {
        case SWORD:
        return "sword";
        case BOMB:
        return "bomb";
        case ARROW:
        return "arrow";
        default:
        return string();
    }
}


inline string toString(WarriorType warrior)
{
    switch(warrior)
    {
        case DRAGON:
        return "dragon";
        case NINJA:
        return "ninja";
        case ICEMAN:
        return "iceman";
        case LION:
        return "lion";
        case WOLF:
        return "wolf";
        default:
        return string();
    }
}

inline string toString(ColorType color)
{
    switch(color)
    {
        case RED:
        return "red";
        case BLUE:
        return "blue";
        default:
        return string();
    }
}



class Weapon;
class WeaponView;
class Warrior;
class WarriorView;
class City;

using CityPtr = std::shared_ptr<City>;
using WeaponPtr = std::shared_ptr<Weapon>;
using WeaponViewPtr = std::shared_ptr<WeaponView>;
using WarriorPtr = std::shared_ptr<Warrior>;
using WarriorViewPtr = std::shared_ptr<WarriorView>;

}//end of namespace warcraft


#endif 