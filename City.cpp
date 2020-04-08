#include "City.h"
#include <algorithm>

namespace warcraft
{
bool compBeforeFight(WeaponPtr lhs, WeaponPtr rhs)
{
    if (lhs->getType() < rhs->getType())
        return true;
    else if (lhs->getType() == ARROW && lhs->getType() == rhs->getType() && lhs->getDurability() < rhs->getDurability())
        return true;
    else
        return false;
}

bool compAfterFight(WeaponPtr lhs, WeaponPtr rhs)
{
    if (lhs->getType() < rhs->getType())
        return true;
    else if (lhs->getType() == ARROW && lhs->getType() == rhs->getType() && lhs->getDurability() > rhs->getDurability())
        return true;
    else
        return false;
}

bool City::Battle()
{
    //城市中没有对立的两武士，决斗失败
    if (!redWarrior.get() || !blueWarrior.get())
        return false;

    /****************************战前准备*******************************/
    //排列好武器
    vector<WeaponPtr> &redWeaponLib = redWarrior->getWeapons();
    if (!redWeaponLib.empty())
    std::sort(redWeaponLib.begin(), redWeaponLib.end(), compBeforeFight);
    
    vector<WeaponPtr> &blueWeaponLib = blueWarrior->getWeapons();
    if (!blueWeaponLib.empty())
    std::sort(blueWeaponLib.begin(), blueWeaponLib.end(), compBeforeFight);

    //如果双方都没有武器，则视为平局
    if (0 == redWeaponLib.size() && 0 == blueWeaponLib.size())
    {
        bothAlive();
        return true; //决斗成功
    }

    /****************************战中*******************************/
    //偶数编号城市，蓝方先攻击
    if (0 == _id % 2)
        blueWarriorAttackFirst();
    //奇数编号城市，红方先攻击
    else
        redWarriorAttackFirst();

    return true; //决斗成功
}


//某武士胜利之后
void City::win(WarriorPtr winner, WarriorPtr loser)
{
    cout << toString(winner->getColor()) << " " << winner->getName() << " " << winner->getId() <<" kills " << toString(loser->getColor()) << " " << loser->getName() << " " << loser->getId() << "in city " << loser->getCityId() << endl;

    //开始缴获敌人的武器, 当敌人没有武器的时候或者武器数量超过最大携带武器数时停止
    //首先胜者清理自己的武器
    vector<WeaponPtr>& winnerWeapons = winner->getWeapons();
    auto it = std::remove_if(winnerWeapons.begin(), winnerWeapons.end(), [](WeaponPtr& weapon){ return (weapon->getDurability()==0);  });
    winnerWeapons.erase(it, winnerWeapons.end());

    //缴获败者武器
    vector<WeaponPtr>& loserWeapons = loser->getWeapons();
    std::sort(loserWeapons.begin(), loserWeapons.end(), compAfterFight);
    for (auto &e :loserWeapons)
    {
        if (winnerWeapons.size() > MAX_WEAPON_SIZE)
            break;
        if (e->getDurability() > 0)
            winner->getNewWeapon(e);
    }

    //将败者的尸体扔出
    loser->getColor()==RED? (redWarrior.reset()):(blueWarrior.reset());

}


//完成决斗返回true， 反之返回false
bool City::judgeResult(bool &redHpFlag, bool &blueHpFlag)
{
    //如果双方的HP都没有变化，则平局
    if (false == redHpFlag && false == blueHpFlag)
    {
        bothAlive();
        return true;
    }

    else if (redWarrior->getHp() <= 0 && blueWarrior->getHp() <= 0)
    {
        bothdie();
        return true;
    }
    else if (redWarrior->getHp() <= 0)
    {
        win(blueWarrior, redWarrior);
        return true;
    }
    else if (blueWarrior->getHp() <= 0)
    {
        win(redWarrior, blueWarrior);
        return true;
    }
    else
        return false;
}

void City::blueWarriorAttackFirst()
{
    vector<WeaponPtr> &redWeaponLib = redWarrior->getWeapons();
    vector<WeaponPtr> &blueWeaponLib = blueWarrior->getWeapons();
    size_t redWeaponIndex = 0;
    size_t blueWeaponIndex = 0;
    //蓝武士先发动攻击
    while (1)
    {
        bool redWeaponFlag = false, blueWeaponFlag = false;
        bool redHpFlag = false, blueHpFlag = false;

        /****************************蓝武士*******************************/
        //查看是否有武器能使用
        for (size_t i = 0; i < blueWeaponLib.size(); i++)
            if (blueWeaponLib[i]->getDurability() > 0)
            {
                blueWeaponFlag = true;
                break;
            }
        //有武器能够使用的话进行攻击
        if (blueWeaponFlag)
        {
            while (blueWeaponLib[blueWeaponIndex]->getDurability() == 0)
                blueWeaponIndex = (blueWeaponIndex + 1) % blueWeaponLib.size();
            blueWarrior->attack(redWarrior, blueWeaponLib[blueWeaponIndex]);
            blueWeaponIndex = (blueWeaponIndex + 1) % blueWeaponLib.size();
            redHpFlag = true; //红方确定受到攻击
        }

        /****************************红武士*******************************/
        //查看是否有武器能使用
        for (size_t i = 0; i < redWeaponLib.size(); i++)
            if (redWeaponLib[i]->getDurability() > 0)
            {
                redWeaponFlag = true;
                break;
            }
        //有武器能够使用的话进行攻击
        if (redWeaponFlag)
        {
            while (0 == redWeaponLib[redWeaponIndex]->getDurability())
                redWeaponIndex = (redWeaponIndex + 1) % redWeaponLib.size();
            redWarrior->attack(blueWarrior, redWeaponLib[redWeaponIndex]);
            redWeaponIndex = (redWeaponIndex + 1) % redWeaponLib.size();
            blueHpFlag = true; //蓝方确定受到攻击
        }

        /****************************一轮攻击之后*******************************/
        if (judgeResult(redHpFlag, blueHpFlag))
            break;
    }
}

void City::redWarriorAttackFirst()
{
    vector<WeaponPtr> &redWeaponLib = redWarrior->getWeapons();
    vector<WeaponPtr> &blueWeaponLib = blueWarrior->getWeapons();
    size_t redWeaponIndex = 0;
    size_t blueWeaponIndex = 0;
    //蓝武士先发动攻击
    while (1)
    {
        bool redWeaponFlag = false, blueWeaponFlag = false;
        bool redHpFlag = false, blueHpFlag = false;

        /****************************红武士*******************************/
        //查看是否有武器能使用
        for (size_t i = 0; i < redWeaponLib.size(); i++)
            if (redWeaponLib[i]->getDurability() > 0)
            {
                redWeaponFlag = true;
                break;
            }
        //有武器能够使用的话进行攻击
        if (redWeaponFlag)
        {
            while (0 == redWeaponLib[redWeaponIndex]->getDurability())
                redWeaponIndex = (redWeaponIndex + 1) % redWeaponLib.size();
            redWarrior->attack(blueWarrior, redWeaponLib[redWeaponIndex]);
            

            redWeaponIndex = (redWeaponIndex + 1) % redWeaponLib.size();
            blueHpFlag = true; //蓝方确定受到攻击
        }

        /****************************蓝武士*******************************/
        //查看是否有武器能使用
        for (size_t i = 0; i < blueWeaponLib.size(); i++)
            if (blueWeaponLib[i]->getDurability() > 0)
            {
                blueWeaponFlag = true;
                break;
            }
        //有武器能够使用的话进行攻击
        if (blueWeaponFlag)
        {
            while (0 == blueWeaponLib[blueWeaponIndex]->getDurability())
                blueWeaponIndex = (blueWeaponIndex + 1) % blueWeaponLib.size();
            blueWarrior->attack(redWarrior, blueWeaponLib[blueWeaponIndex]);
            blueWeaponIndex = (blueWeaponIndex + 1) % blueWeaponLib.size();
            redHpFlag = true; //红方确定受到攻击
        }

        /****************************一轮攻击之后*******************************/
        if (judgeResult(redHpFlag, blueHpFlag))
            break;
    }
}




} // namespace warcraft