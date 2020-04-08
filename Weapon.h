#ifndef _WARCRAFT_WEAPON_H_
#define _WARCRAFT_WEAPON_H_
#include "Type.h"
#include "GameConfig.h"
#include <iostream>
#include <string>
using std::string;

namespace warcraft
{

/**************************Weapon*******************************/
class Weapon
{
protected:
    WeaponType _type;
    string _name;
    size_t _attack;
    size_t _durability;

public:
    Weapon(WeaponType type, string name, size_t attack, size_t durability)
        : _type(type), _name(name), _attack(attack), _durability(durability)
    {
    }
    virtual ~Weapon() {}

    WeaponType getType() const { return _type; }
    string getName() const { return _name; }
    size_t getAttackValue() const { return _attack; }
    size_t getDurability() { return _durability; }
    void setDurability(size_t durability) { _durability = durability;}
    void decreaseDuribility() { --_durability; }
};

class Sword : public Weapon
{
public:
    Sword(WarriorType type)
        : Weapon(SWORD, "Sword", GameConfig::getInstance()->getInitWarriorAttack(GameConfig::getInstance()->currentGroupId(), type) * 0.2, 1000)
    {
    }
};

class Bomb : public Weapon
{
public:
    Bomb(WarriorType type)
        : Weapon(BOMB, "Bomb", GameConfig::getInstance()->getInitWarriorAttack(GameConfig::getInstance()->currentGroupId(), type) * 0.4, 1)
    {
    }
};

class Arrow : public Weapon
{
    size_t _durability;

public:
    Arrow(WarriorType type)
        : Weapon(ARROW, "Arrow", GameConfig::getInstance()->getInitWarriorAttack(GameConfig::getInstance()->currentGroupId(), type) * 0.3, 2)
    {
    }
};

/**************************View层*******************************/
class WeaponView
{
protected:
    WeaponPtr _weapon;

public:
    WeaponView(WeaponPtr weapon)
        : _weapon(weapon)
    {
    }
    virtual ~WeaponView() {}

    virtual void showWeapon() const {}
};

class SwordView : public WeaponView
{
public:
    SwordView(WeaponPtr weapon)
        : WeaponView(weapon)
    {
    }

    void showWeapon() const
    {
        std::cout << "Sword";
    }
};

class BombView : public WeaponView
{
public:
    BombView(WeaponPtr weapon)
        : WeaponView(weapon)
    {
    }

    void showWeapon() const
    {
        std::cout << "Bomb";
    }
};

class ArrowView : public WeaponView
{
public:
    ArrowView(WeaponPtr weapon)
        : WeaponView(weapon)
    {
    }

    void showWeapon() const
    {
        std::cout << "Arrow";
    }
};

} //end of namespace warcraft

#endif