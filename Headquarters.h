#ifndef _WARCRAFT_HEADQUARTERS_H_
#define _WARCRAFT_HEADQUARTERS_H_
#include "Type.h"
#include "Warrior.h"
#include "Weapon.h"
#include "GameConfig.h"
#include <vector>
#include <unordered_map>
using std::unordered_map;
using std::vector;

namespace warcraft
{

class Headquarters
{
protected:
    ColorType _color;                                        //基地颜色
    size_t _baseHp;                                          //基地生命元
    size_t _warriorOrderIndex;                               //武士顺序创建的索引
    size_t _warriorId;                                       //武士编号
    vector<WarriorType> _warriorCreateOrder;                 //武士创建顺序
    unordered_map<WarriorPtr, WarriorViewPtr> _warriorViews; //武士视图层哈希表
    unordered_map<WeaponPtr, WeaponViewPtr> _weaponViews;    //武器视图层哈希表
public:
    Headquarters(ColorType color, size_t baseHp)
        : _color(color), _baseHp(baseHp), _warriorOrderIndex(0), _warriorId(1)
    {
    }

    template <typename Iterator>
    void setWarriorCreateOrder(Iterator beg, Iterator end)
    {
        while (beg != end)
            _warriorCreateOrder.push_back(*beg++);
    }

    size_t getBaseHp() const { return _baseHp; }
    ColorType getColor() { return _color; }
    size_t getWarriorId() { return _warriorId; }
    WarriorViewPtr getWarriorView(WarriorPtr ptr) { return _warriorViews[ptr]; }
    WeaponViewPtr getWeaponView(WeaponPtr ptr) { return _weaponViews[ptr]; }
    WarriorType getWarriorType() { return _warriorCreateOrder[_warriorOrderIndex]; }
    void nextWarriorType() { _warriorOrderIndex = (_warriorOrderIndex + 1) % _warriorCreateOrder.size(); }
    void nextWarriorId() { _warriorId++; }

    WarriorPtr createWarrior(WarriorType);                   //创建一个武士,注意此次创建一定是成功的
    WeaponPtr createWeapon(size_t number, WarriorType type); //给武士配备武器

private:
    size_t getWarriorCreateIndex() { return _warriorOrderIndex; }
};

/*************************HeadquartersView表示层*********************************/
class HeadquartersView
{
    Headquarters *_head;

public:
    HeadquartersView(Headquarters *head)
        : _head(head)
    {
    }

    void show()
    {
    }
};

} //end of namespace warcraft

#endif
