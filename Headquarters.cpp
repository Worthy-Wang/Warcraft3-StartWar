#include "Headquarters.h"

namespace warcraft
{

/*************************定义成员函数*********************************/
WarriorPtr Headquarters::createWarrior(WarriorType type)
{
    size_t hp = GameConfig::getInstance()->getInitWarriorHp(GameConfig::getInstance()->currentGroupId(), type);
    _baseHp -= hp;
    WarriorPtr warrior;
    WarriorViewPtr warriorView;
    WeaponPtr weapon;
    WeaponViewPtr weaponView;
    switch (type)
    {
    case DRAGON:
    {
        warrior.reset(new Dragon(getColor(), getWarriorId(), hp, getBaseHp()));
        warriorView.reset(new DragonView(warrior));
        weapon = createWeapon(getWarriorId() % 3, DRAGON);
        warrior->setWeapon(weapon);
        break;
    }
    case NINJA:
    {
        warrior.reset(new Ninja(getColor(), getWarriorId(), hp, getBaseHp()));
        warriorView.reset(new NinjaView(warrior));
        weapon = createWeapon(getWarriorId() % 3, NINJA);
        WeaponPtr weapon2 = createWeapon((getWarriorId() + 1) % 3, NINJA);
        warrior->setWeapon(weapon);
        warrior->setWeapon(weapon2);
        break;
    }
    case ICEMAN:
    {
        warrior.reset(new Iceman(getColor(), getWarriorId(), hp, getBaseHp()));
        warriorView.reset(new IcemanView(warrior));
        weapon = createWeapon(getWarriorId() % 3, ICEMAN);
        warrior->setWeapon(weapon);
        break;
    }
    case LION:
    {
        warrior.reset(new Lion(getColor(), getWarriorId(), hp, getBaseHp()));
        warriorView.reset(new LionView(warrior));
        weapon = createWeapon(getWarriorId() % 3, LION);
        warrior->setWeapon(weapon);
        break;
    }
    case WOLF:
    {
        warrior.reset(new Wolf(getColor(), getWarriorId(), hp, getBaseHp()));
        warriorView.reset(new WolfView(warrior));
        break;
    }
    default:
        cout << "Warrior Type ERROR!" << endl;
        break;
    }

    _warriorViews[warrior] = warriorView;

    return warrior;
}

WeaponPtr Headquarters::createWeapon(size_t number, WarriorType type)
{
    WeaponPtr weapon;
    WeaponViewPtr weaponView;
    switch (number)
    {
    case 0:
    {
        weapon.reset(new Sword(type));
        weaponView.reset(new SwordView(weapon));
        break;
    }
    case 1:
    {
        weapon.reset(new Bomb(type));
        weaponView.reset(new BombView(weapon));
        break;
    }
    case 2:
    {
        weapon.reset(new Arrow(type));
        weaponView.reset(new ArrowView(weapon));
        break;
    }
    default:
        cout << "Headquarters::createWeapon ERROR!" << endl;
        break;
    }
    _weaponViews[weapon] = weaponView;
    return weapon;
}

} // namespace warcraft