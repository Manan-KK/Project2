#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <cstdlib> 
#include <ctime>

class Tile{
    public:
    char color;
    int position;
    void onStartTile();
    void onEndTile();
    void onChanceTile();
    void onGambleTile();
    void onFightTile();
    void onRiddleTile();
};
#endif

