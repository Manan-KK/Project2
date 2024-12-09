#include "Tile.h"

Tile::Tile() {
    color='G';
    position=0;
}

int Tile::getType() const {
    if (color=='G') return REGULAR_TILE;
    else if (color=='B') return OASIS_TILE;
    else if (color=='P') return COUNSELING_TILE;
    else if (color=='R') return GRAVEYARD_TILE;
    else if (color=='N') return HYENAS_TILE;
    else if (color=='U') return CHALLENGE_TILE;
    else if (color=='O') return END_TILE;
    else if (color=='Y') return START_TILE;
    else if (color=='S') return SHOP_TILE;
    else if (color=='F') return FIGHT_TILE;
    else if (color=='C') return CASINO_TILE;
    return -1;
}
