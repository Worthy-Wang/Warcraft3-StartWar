#ifndef _WARCRAFT_WARCRAFTWORLD_H_
#define _WARCRAFT_WARCRAFTWORLD_H_
#include "Headquarters.h"
#include "GameTime.h"
#include "City.h"

namespace warcraft
{

class WarcraftWorld
{
    Headquarters *_red;
    Headquarters *_blue;
    vector<CityPtr> _citys;
    size_t _caseNum; //读取数据组号
public:
    WarcraftWorld()
        : _red(NULL), _blue(NULL)
    {
        init();
    }

    ~WarcraftWorld()
    {
        if (_red)
            delete _red;
        if (_blue)
            delete _blue;
    }

    void startGame();

private:
    void init();
    bool createAndShow(Headquarters *);
    void lionRun();
    void warriorMarch();    
    void wolfStealing();
    void startFight();
    void dragonCheer();
    void warriorArriveHeadquarters();
    void occupyHeadquarters();
    void headquartersReport();
};



} //end of namespace warcraft

#endif