#ifndef TILE_H
#define TILE_H

class Tile {
public:
    char color;
    int position;
    Tile();
    int getType() const;
};

#define REGULAR_TILE 0
#define OASIS_TILE 1
#define COUNSELING_TILE 2
#define GRAVEYARD_TILE 3
#define HYENAS_TILE 4
#define CHALLENGE_TILE 5
#define END_TILE 6
#define START_TILE 7
#define SHOP_TILE 8
#define FIGHT_TILE 9
#define CASINO_TILE 10

#endif
