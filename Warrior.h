#ifndef _WARCRAFT_WARRIOR_H_
#define _WARCRAFT_WARRIOR_H_
#include "Type.h"
#include "Weapon.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using std::vector;

namespace warcraft
{

/**************************Warrior及其派生类Model*******************************/
class Warrior
{
protected:
    ColorType _color;
    string _name;
    size_t _id;
    int _hp;
    WarriorType _type;
    vector<WeaponPtr> _weapons;
    size_t _cityId;

public:
    Warrior(ColorType color, string name, size_t id, int hp, WarriorType type)
        : _color(color), _name(name), _id(id), _hp(hp), _type(type)
    {
        _color == RED ? (_cityId = 0) : (_cityId = GameConfig::getInstance()->getCityNum(GameConfig::getInstance()->currentGroupId()) + 1);
    }
    virtual ~Warrior() {}

    size_t getCityId() { return _cityId; }
    ColorType getColor() const { return _color; }
    string getName() const { return _name; }
    size_t getId() const { return _id; }
    int getHp() const { return _hp; }
    WarriorType getType() const { return _type; }
    void attack(WarriorPtr enemy, WeaponPtr weapon); //注意此时weapon的耐久度一定是大于0的    

    virtual void march() { getColor() == RED ? (_cityId++) : (_cityId--); }
    virtual void cheer() const {}
    virtual int getLoyalty() { return -1; }
    virtual void stealWeapons(WarriorPtr enemy) {}
    //Weapon
    vector<WeaponPtr> &getWeapons() { return _weapons; }
    void setWeapon(WeaponPtr weapon) { _weapons.push_back(weapon); }
    void getNewWeapon(WeaponPtr);

private:
    void sufferAttack(size_t attack) { _hp -= attack; }
};

class Dragon : public Warrior
{

public:
    Dragon(ColorType color, size_t id, int hp, double baseHp)
        : Warrior(color, "Dragon", id, hp, DRAGON)
    {
    }
    void cheer() const override
    {
        cout << "Dragon is Cheering " << endl;
    }
};

class Ninja : public Warrior
{
public:
    Ninja(ColorType color, size_t id, int hp, double baseHp)
        : Warrior(color, "Ninja", id, hp, NINJA)
    {
    }
};

class Iceman : public Warrior
{
public:
    Iceman(ColorType color, size_t id, int hp, double baseHp)
        : Warrior(color, "Iceman", id, hp, ICEMAN)
    {
    }

    void march() override
    {
        getColor() == RED ? (_cityId++) : (_cityId--);
        _hp *= 0.9;
    }
};

class Lion : public Warrior
{
    int _loyalty;

public:
    Lion(ColorType color, size_t id, int hp, size_t baseHp)
        : Warrior(color, "Lion", id, hp, LION), _loyalty(baseHp)
    {
    }

    int getLoyalty() { return _loyalty; }
    void march() override
    {
        getColor() == RED ? (_cityId++) : (_cityId--);
        _loyalty -= GameConfig::getInstance()->getLionReduceRoyalty(GameConfig::getInstance()->currentGroupId());
    }
};


class Wolf : public Warrior
{
public:
    Wolf(ColorType color, size_t id, int hp, double baseHp)
        : Warrior(color, "Wolf", id, hp, WOLF)
    {
    }

    void stealWeapons(WarriorPtr enemy) override
    {
        if (!enemy.get())
            return;
        vector<WeaponPtr> &enemyWeapons = enemy->getWeapons();
        if (WOLF == enemy->getType() || 0 == enemyWeapons.size())
            return;
        //抢敌人编号最小的武器
        std::sort(enemyWeapons.begin(), enemyWeapons.end(), [](WeaponPtr lhs, WeaponPtr rhs) {
            if (lhs->getType() < rhs->getType())
                return true;
            else if (lhs->getType() == ARROW && lhs->getType() == rhs->getType() && lhs->getDurability() > rhs->getDurability())
                return true;
            else
                return false;
        });
        WeaponType type = enemyWeapons[0]->getType();
        size_t cnt = 0;
        for (auto &e : enemyWeapons)
        {
            if (type != e->getType() || _weapons.size() > MAX_WEAPON_SIZE)
                break;
            getNewWeapon(e);
            cnt++;
        }
        cout << toString(_color) << " wolf " << _id << " took " << cnt << " " << toString(type) << " from " << toString(enemy->getColor()) << " " << toString(enemy->getType()) << " " << enemy->getId() << endl;
        auto it = std::remove_if(enemyWeapons.begin(), enemyWeapons.end(), [&](WeaponPtr weapon) { return type == weapon->getType(); });
        enemyWeapons.erase(it, enemyWeapons.end());
    }
};

/**************************WarriorView视图层*******************************/
class WarriorView
{
protected:
    WarriorPtr _warrior;

public:
    WarriorView(WarriorPtr warrior)
        : _warrior(warrior)
    {
    }

    virtual ~WarriorView() {}
    virtual void show() const {}
};

class DragonView : public WarriorView
{
public:
    DragonView(WarriorPtr warrior)
        : WarriorView(warrior)
    {
    }

    void show() const
    {
        std::cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) << " " << _warrior->getId() << " born " << endl;
    }
};

class NinjaView : public WarriorView
{
public:
    NinjaView(WarriorPtr warrior)
        : WarriorView(warrior)
    {
    }

    void show() const
    {
        std::cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) << " " << _warrior->getId() << " born " << endl;
    }
};

class IcemanView : public WarriorView
{
public:
    IcemanView(WarriorPtr warrior)
        : WarriorView(warrior)
    {
    }

    void show() const
    {
        std::cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) << " " << _warrior->getId() << " born " << endl;
    }
};

class WolfView : public WarriorView
{
public:
    WolfView(WarriorPtr warrior)
        : WarriorView(warrior)
    {
    }

    void show() const
    {
        std::cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) << " " << _warrior->getId() << " born " << endl;
    }
};

class LionView : public WarriorView
{
public:
    LionView(WarriorPtr warrior)
        : WarriorView(warrior)
    {
    }

    void show() const
    {
        std::cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) << " " << _warrior->getId() << " born " << endl;
        cout << "It's loyalty is " << _warrior->getLoyalty() << endl;
    }
};

} //end of namespace warcraft

#endif