// Board.h
#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board {
private:
    static const int _BOARD_SIZE = 52;
    static const int _MAX_PLAYERS = 4;
    Tile _tiles[2][_BOARD_SIZE]; // Two paths
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int _player_path[_MAX_PLAYERS]; 
    int _last_move[_MAX_PLAYERS];

    void displayTile(int path_index, int pos);
    void initializeTiles(int path_index);
    bool isPlayerOnTile(int pos, int path_index, int &playerOnTile);

public:
    Board();
    Board(int player_count);
    void initializeBoard();
    void displayTrack(int path_index);
    void displayBoard();
    bool movePlayer(int player_index, int steps);
    int getPlayerPosition(int player_index) const;
    void setPlayerPath(int player_index, int path_index);
    Tile getTileAtPlayerPosition(int player_index);
    int getPlayerPath(int player_index) const;
    int getLastMove(int player_index) const;
};

#endif
