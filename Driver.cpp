#include <iostream>
#include "Tile.h"
#include "Board.h"
#include "Player.h"

using namespace std;

int main(){
    BaseC character(100, 100, 100, 100);
    cout<<character.getAge()<<endl;
    cout<<character.getStrength()<<endl;
    cout<<character.getStamina()<<endl;
    cout<<character.getWisdom()<<endl;
    cout<<character.getPridePoints()<<endl;
    character.displayStats();
    Tile t;
    int index = 0;
    t.onStartTile();
    t.onEndTile();
    t.onChanceTile();
    t.onFightTile();
    t.onRiddleTile();
    t.getTypeOfTile(0);
    Board b;
}