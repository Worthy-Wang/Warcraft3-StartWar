#include "WarcraftWorld.h"

namespace warcraft
{

void WarcraftWorld::startGame()
{
    size_t deadline = GameConfig::getInstance()->getDeadline(_caseNum);
    while (GameTime::getInstance()->getTime() < deadline)
    {
        //1):武士降生
        GameTime::getInstance()->showTime();
        createAndShow(_red);
        createAndShow(_blue);
        GameTime::getInstance()->updateTime();

        //2):Lion逃跑
        GameTime::getInstance()->showTime();
        lionRun();
        GameTime::getInstance()->updateTime();

        //3):武士前进到某一城市
        GameTime::getInstance()->showTime();
        warriorMarch();
        GameTime::getInstance()->updateTime();

        //4):wolf抢敌人的武器
        GameTime::getInstance()->showTime();
        wolfStealing();
        GameTime::getInstance()->updateTime();

        //5):进行战斗并报告战斗情况
        GameTime::getInstance()->showTime();
        startFight();
        GameTime::getInstance()->updateTime();

        //6):龙开始欢呼
        GameTime::getInstance()->showTime();
        dragonCheer();
        GameTime::getInstance()->updateTime();

        //7):武士抵达敌方司令部
        GameTime::getInstance()->showTime();
        warriorArriveHeadquarters();
        GameTime::getInstance()->updateTime();

        //8):司令部被占领
        GameTime::getInstance()->showTime();
        occupyHeadquarters();
        GameTime::getInstance()->updateTime();

        //9):司令部报告生命元数量
        GameTime::getInstance()->showTime();
        headquartersReport();
        GameTime::getInstance()->updateTime();
    }
}

//9):司令部报告生命元数量
void WarcraftWorld::headquartersReport()
{
    //红方基地
    cout << _red->getBaseHp() << " elememts in red headquarters" << endl;
    //蓝方基地
    cout << _blue->getBaseHp() << " elememts in blue headquarters" << endl;
}

//8):司令部被占领
void WarcraftWorld::occupyHeadquarters()
{
    //蓝方基地
    WarriorPtr redWarrior = _citys[GameConfig::getInstance()->getCityNum(_caseNum) + 1]->getRedWarrior();
    if (redWarrior.get()){
        cout << "blue headquarter was taken" << endl;
        exit(0);
    }
    //红方基地
    WarriorPtr blueWarrior = _citys[0]->getBlueWarrior();
    if (blueWarrior.get())
    {
        cout << "red headquarter was taken" << endl;
        exit(0);
    }
}

//7):武士抵达敌方司令部
void WarcraftWorld::warriorArriveHeadquarters()
{
    //蓝方基地
    WarriorPtr redWarrior = _citys[GameConfig::getInstance()->getCityNum(_caseNum) + 1]->getRedWarrior();
    if (redWarrior.get())
        cout << "red " << redWarrior->getName() << " " << redWarrior->getId() << " reached blue headquarters with " << redWarrior->getHp() << " elements and force " << GameConfig::getInstance()->getInitWarriorAttack(_caseNum, redWarrior->getType()) << endl;
    //红方基地
    WarriorPtr blueWarrior = _citys[0]->getBlueWarrior();
    if (blueWarrior.get())
        cout << "blue " << blueWarrior->getName() << " " << blueWarrior->getId() << " reached red headquarters with " << blueWarrior->getHp() << " elements and force " << GameConfig::getInstance()->getInitWarriorAttack(_caseNum, blueWarrior->getType()) << endl;
}

//6):龙开始欢呼
void WarcraftWorld::dragonCheer()
{
    for (auto &e : _citys)
    {
        WarriorPtr redWarrior = e->getRedWarrior();
        WarriorPtr blueWarrior = e->getBlueWarrior();
        if (redWarrior.get() && DRAGON == redWarrior->getType())
        {
            redWarrior->cheer();
        }
        if (blueWarrior.get() && DRAGON == blueWarrior->getType())
        {
            blueWarrior->cheer();
        }
    }
}

//5):进行战斗并报告战斗情况
void WarcraftWorld::startFight()
{
    for (auto &e : _citys)
    {
        e->Battle();
    }
}

//4):wolf抢敌人的武器
void WarcraftWorld::wolfStealing()
{
    for (auto &e : _citys)
    {
        WarriorPtr redWarrior = e->getRedWarrior();
        WarriorPtr blueWarrior = e->getBlueWarrior();
        if (redWarrior.get() && WOLF == redWarrior->getType())
        {
            redWarrior->stealWeapons(blueWarrior);
        }
        if (blueWarrior.get() && WOLF == blueWarrior->getType())
        {
            blueWarrior->stealWeapons(redWarrior);
        }
    }
}

//3):武士前进到某一城市
void WarcraftWorld::warriorMarch()
{
    //让基地中，城市中的武士依次前进
    /***************************红武士*************************************/
    for (int i = GameConfig::getInstance()->getCityNum(_caseNum); i >= 0; i--)
    {
        WarriorPtr redWarrior = _citys[i]->getRedWarrior();
        //如果还活着，则前往下一个城市，如果是到达司令部，则在后面的事件中输出
        if (redWarrior.get())
        {
            redWarrior->march();
            _citys[redWarrior->getCityId()]->attach(redWarrior);
            //没有走到司令部，则输出事件
            if (redWarrior->getCityId() != (GameConfig::getInstance()->getCityNum(_caseNum) + 1))
                cout << "red " << redWarrior->getName() << " " << redWarrior->getId() << " marched to city " << redWarrior->getCityId() << " with " << redWarrior->getHp() << " elements and force " << GameConfig::getInstance()->getInitWarriorAttack(_caseNum, redWarrior->getType()) << endl;
        }
    }

    /***************************蓝武士*************************************/
    for (size_t i = 1; i <= GameConfig::getInstance()->getCityNum(_caseNum) + 1; i++)
    {
        WarriorPtr blueWarrior = _citys[i]->getBlueWarrior();
        //如果还活着，则前往下一个城市，如果是到达司令部，则在后面的事件中输出
        if (blueWarrior.get())
        {
            blueWarrior->march();
            _citys[blueWarrior->getCityId()]->attach(blueWarrior);
            //没有走到司令部，则输出事件
            if (blueWarrior->getCityId() != (GameConfig::getInstance()->getCityNum(_caseNum) + 1))
                cout << "blue " << blueWarrior->getName() << " " << blueWarrior->getId() << " marched to city " << blueWarrior->getCityId() << " with " << blueWarrior->getHp() << " elements and force " << GameConfig::getInstance()->getInitWarriorAttack(_caseNum, blueWarrior->getType()) << endl;
        }
    }
}

//2):Lion逃跑
void WarcraftWorld::lionRun()
{
    for (auto &e : _citys)
    {
        WarriorPtr redWarrior = e->getRedWarrior();
        if (redWarrior.get() && LION == redWarrior->getType() && redWarrior->getLoyalty() <= 0)
        {
            cout << " red lion " << redWarrior->getId() << " run away" << endl;
            e->detach(redWarrior);
        }

        WarriorPtr blueWarrior = e->getBlueWarrior();
        if (blueWarrior.get() && LION == blueWarrior->getType() && blueWarrior->getLoyalty() <= 0)
        {
            cout << " blue lion " << blueWarrior->getId() << " run away" << endl;
            e->detach(blueWarrior);
        }
    }
}

//1):武士降生
//创建勇士，成功返回true, 失败返回false
bool WarcraftWorld::createAndShow(Headquarters *head)
{
    //基地生命元少于当前创造的勇士生命值时 返回false
    while (head->getBaseHp() < GameConfig::getInstance()->getInitWarriorHp(_caseNum, head->getWarriorType()))
        return false;
    //创建勇士
    WarriorPtr warrior = head->createWarrior(head->getWarriorType());
    WarriorViewPtr warriorView;

    //设置武器
    switch (head->getWarriorType())
    {
    case DRAGON:
    {
        WeaponPtr weapon = head->createWeapon(head->getWarriorId() % 3, DRAGON);
        warrior->setWeapon(weapon);
        warriorView.reset(new DragonView(warrior));
        HeadquartersView headView(head);
        //show
        warriorView->show();
        cout << "It has a " << weapon->getName() << endl;
        break;
    }
    case ICEMAN:
    {
        WeaponPtr weapon = head->createWeapon(head->getWarriorId() % 3, ICEMAN);
        warrior->setWeapon(weapon);
        warriorView.reset(new IcemanView(warrior));
        HeadquartersView headView(head);
        //show
        warriorView->show();
        cout << "It has a " << weapon->getName() << endl;
        break;
    }
    case LION:
    {
        WeaponPtr weapon = head->createWeapon(head->getWarriorId() % 3, LION);
        warrior->setWeapon(weapon);
        warriorView.reset(new LionView(warrior));
        HeadquartersView headView(head);
        //show
        warriorView->show();
        break;
    }
    case NINJA:
    {
        WeaponPtr weapon1 = head->createWeapon(head->getWarriorId() % 3, NINJA);
        WeaponPtr weapon2 = head->createWeapon((head->getWarriorId() + 1) % 3, NINJA);
        warrior->setWeapon(weapon1);
        warrior->setWeapon(weapon2);
        warriorView.reset(new NinjaView(warrior));
        HeadquartersView headView(head);
        //show
        warriorView->show();
        cout << "It has a " << weapon1->getName() << " and a " << weapon2->getName() << endl;
        break;
    }
    case WOLF:
    {
        warriorView.reset(new WolfView(warrior));
        HeadquartersView headView(head);
        //show
        warriorView->show();
        break;
    }
    }
    if (head->getColor() == RED)
        _citys[0]->attach(warrior);
    else
        _citys[GameConfig::getInstance()->getCityNum(_caseNum) + 1]->attach(warrior);
    head->nextWarriorType();
    head->nextWarriorId();
    return true;
}

void WarcraftWorld::init()
{
    vector<WarriorType> initHpOrder{DRAGON, NINJA, ICEMAN, LION, WOLF}; //同时对生命值与攻击力顺序赋值
    vector<WarriorType> redCreateorder{ICEMAN, LION, WOLF, NINJA, DRAGON};
    vector<WarriorType> blueCreateorder{LION, DRAGON, NINJA, ICEMAN, WOLF};

    GameConfig::getInstance()->setInitWarriorOrder(initHpOrder.begin(), initHpOrder.end());
    GameConfig::getInstance()->readFromFile("warcraft.conf");
    GameConfig::getInstance()->print(); //进行检测

    _caseNum = GameConfig::getInstance()->currentGroupId();
    size_t baseHp = GameConfig::getInstance()->getInitBaseHp(_caseNum);
    _red = new Headquarters(RED, baseHp);
    _blue = new Headquarters(BLUE, baseHp);
    _red->setWarriorCreateOrder(redCreateorder.begin(), redCreateorder.end());
    _blue->setWarriorCreateOrder(blueCreateorder.begin(), blueCreateorder.end());

    CityPtr city(new City(0));
    _citys.push_back(city); //红方基地
    size_t i = 1;
    for (; i <= GameConfig::getInstance()->getCityNum(_caseNum); i++)
    {
        city.reset(new City(i));
        _citys.push_back(city);
    }
    city.reset(new City(i));
    _citys.push_back(city); //蓝方基地
}

} // namespace warcraft