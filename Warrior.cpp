#include "Warrior.h"

namespace warcraft
{

void Warrior::attack(WarriorPtr enemy, WeaponPtr weapon)
{
    switch (weapon->getType())
    {
    case SWORD:
    {
        enemy->sufferAttack(weapon->getAttackValue());
        break;
    }
    case BOMB:
    {
        enemy->sufferAttack(weapon->getAttackValue());
        if (this->getType() != NINJA)
            this->sufferAttack(weapon->getAttackValue() / 2);
        break;
    }
    case ARROW:
    {
        enemy->sufferAttack(weapon->getAttackValue());
        break;
    }
    }
    weapon->decreaseDuribility();
}

//获得一件与此武器相同的武器
void Warrior::getNewWeapon(WeaponPtr weapon) 
{
    if (!weapon.get())
        return;
    WeaponPtr newWeapon;
    switch (weapon->getType())
    {
        case SWORD:newWeapon.reset(new Sword(_type)); break;
        case BOMB:newWeapon.reset(new Bomb(_type));break;
        case ARROW:newWeapon.reset(new Arrow(_type)); newWeapon->setDurability(weapon->getDurability()); break;
    }
    _weapons.push_back(newWeapon);
}

} //end of namespace warcraft