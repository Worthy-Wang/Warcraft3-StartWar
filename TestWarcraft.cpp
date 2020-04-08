#include "GameConfig.h"
#include "GameTime.h"
#include "Weapon.h"
#include "Warrior.h"
#include "Headquarters.h"
#include "City.h"
#include "WarcraftWorld.h"
#include <iostream>
#include <memory>
using namespace warcraft;

//GameConfig
void test1()
{
    //勇士生命值，攻击力赋值顺序
    vector<WarriorType> initWarriorOrder{DRAGON, NINJA, ICEMAN, LION, WOLF};
    GameConfig::getInstance()->setInitWarriorOrder(initWarriorOrder.begin(), initWarriorOrder.end());
    GameConfig::getInstance()->readFromFile("warcraft.conf");
    GameConfig::getInstance()->print();
}

//GameTime
void test2()
{
    GameTime::getInstance()->showTime();
    GameTime::getInstance()->updateTime();
    cout << endl;
    GameTime::getInstance()->showTime();
    GameTime::getInstance()->updateTime();
    cout << endl;
    GameTime::getInstance()->showTime();
    GameTime::getInstance()->updateTime();
    cout << endl;
}

//Weapon
void test3()
{
    test1();
    WeaponPtr weapon(new Arrow(DRAGON));
    cout << weapon->getAttackValue() << endl;
    cout << weapon->getName() << endl;
    cout << weapon->getDurability() << endl;
    weapon->decreaseDuribility();
    cout << weapon->getDurability() << endl;
}

//Warrior In city
void test4()
{
    test1();
    WarriorPtr warrior1(new Dragon(RED, 1, 20, 20));
    WarriorPtr warrior2(new Wolf(BLUE, 2, 2, 10));
    WeaponPtr weapon1(new Sword(DRAGON));
    WeaponPtr weapon11(new Sword(DRAGON));
    WeaponPtr weapon2(new Bomb(DRAGON));
    WeaponPtr weapon3(new Arrow(DRAGON));

    warrior1->setWeapon(weapon2);
    warrior1->setWeapon(weapon3);
    
    warrior2->stealWeapons(warrior1);

    City city(2);
    city.attach(warrior1);
    city.attach(warrior2);
    city.Battle();
 
    // vector<WeaponPtr>& weapons = warrior2->getWeapons();
    // for (auto &e : weapons)
    //     cout << e->getName() << ":" << e->getDurability() << endl;
}


//最终测验
void test5()
{
    WarcraftWorld world;
    world.startGame();
}


int main()
{
    test5();
    return 0;
}