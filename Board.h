// Board.h
#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

using namespace std;

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE]; // Two paths
    static const int _MAX_PLAYERS = 4;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int _player_path[_MAX_PLAYERS]; // Stores the path choice for each player
    int _last_move[_MAX_PLAYERS]; // Stores the last move for each player
    void displayTile(int path_index, int pos);
    void initializeTiles(int path_index);
    bool isPlayerOnTile(int pos, int path_index, int &playerOnTile);
public:
    Board();
    Board(int player_count);
    void displayTrack(int path_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index, int steps);
    int getPlayerPosition(int player_index) const;
    void setPlayerPath(int player_index, int path_index);
    Tile getTileAtPlayerPosition(int player_index);
    int getPlayerPath(int player_index) const;
    int getLastMove(int player_index) const; // New method
};

#endif
