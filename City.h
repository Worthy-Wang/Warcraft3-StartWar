#ifndef _WARCRAFT_CITY_H_
#define _WARCRAFT_CITY_H_
#include <iostream>
#include <algorithm>
#include "Warrior.h"
namespace warcraft
{
class City
{
    size_t _id; //城市ID
    WarriorPtr redWarrior;
    WarriorPtr blueWarrior;

public:
    City(size_t id)
        : _id(id)
    {
    }

    void attach(WarriorPtr warrior) { warrior->getColor() == RED ? (redWarrior = warrior) : (blueWarrior = warrior); }
    void detach(WarriorPtr warrior) { warrior->getColor() == RED ? redWarrior.reset(): blueWarrior.reset();}
    bool Battle(); //如果有红蓝武士在城市，Battle完返回true，反之返回false
    size_t getCityId() const { return _id; }
    WarriorPtr getRedWarrior() { return redWarrior; }
    WarriorPtr getBlueWarrior() { return blueWarrior; }

private:
    //报告战斗情况
    bool judgeResult(bool &, bool &);
    void win(WarriorPtr winner, WarriorPtr loser);
    void bothAlive() { cout << "Both red " << redWarrior->getName() << " " << redWarrior->getId() << " and blue " << blueWarrior->getName() << " " << blueWarrior->getId() << " were alive in city " << _id << endl; }
    void bothdie() { cout << "Both red " << redWarrior->getName() << " " << redWarrior->getId() << " and blue " << blueWarrior->getName() << " " << blueWarrior->getId() << " died in city " << _id << endl; }

    void blueWarriorAttackFirst();
    void redWarriorAttackFirst();
};

} // end of namespace warcraft

#endif