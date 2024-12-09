// Board.cpp
#include "Board.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

#define RED     "\033[48;2;230;10;10m"
#define GREEN   "\033[48;2;34;139;34m"   /* Grassy Green (34,139,34) */
#define BLUE    "\033[48;2;10;10;230m"
#define PINK    "\033[48;2;255;105;180m"
#define BROWN   "\033[48;2;139;69;19m"
#define PURPLE  "\033[48;2;128;0;128m"
#define ORANGE  "\033[48;2;230;115;0m"   /* Orange (230,115,0) */
#define GREY    "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define CYAN    "\033[48;2;0;255;255m"   /* Cyan (Shop) */
#define MAGENTA "\033[48;2;255;0;255m"   /* Magenta (Fight) */
#define YELLOW  "\033[48;2;255;255;0m"   /* Yellow (Casino) */
#define RESET   "\033[0m"

Board::Board() {
    _player_count = 1;
    for (int i = 0; i < _MAX_PLAYERS; i++) {
        _player_position[i] = 0;
        _player_path[i] = 0;
        _last_move[i] = 0;
    }
    initializeBoard();
}

Board::Board(int player_count) {
    if (player_count > _MAX_PLAYERS) {
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    for (int i = 0; i < _player_count; i++) {
        _player_position[i] = 0;
        _player_path[i] = 0; 
        _last_move[i] = 0;
    }

    initializeBoard();
}

void Board::initializeBoard() {
    srand(time(0));
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
}

void Board::initializeTiles(int path_index) {
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    int green_tiles_needed = 20;
    // Note: special_tiles_needed not strictly enforced here, but present in original code comments.
    int special_tiles_needed = 32; 

    for (int i = 0; i < total_tiles; i++) {
        if (i == total_tiles - 1) {
            // Last tile: Orange (End)
            temp.color = 'O';
        } else if (i == 0) {
            // First tile: Grey (Start)
            temp.color = 'Y';
        } else if (green_count < green_tiles_needed &&
                   (rand() % (total_tiles - i) < green_tiles_needed - green_count)) {
            // Assign a green tile
            temp.color = 'G';
            green_count++;
        } else {
            // Assign a special tile
            int color_choice = rand() % 8;
            switch (color_choice) {
                case 0: temp.color = 'B'; break; // Blue (Oasis)
                case 1: temp.color = 'P'; break; // Pink (Counseling)
                case 2: temp.color = 'N'; break; // Brown (Hyenas)
                case 3: temp.color = 'R'; break; // Red (Graveyard)
                case 4: temp.color = 'U'; break; // Purple (Challenge)
                case 5: temp.color = 'S'; break; // Cyan (Shop)
                case 6: temp.color = 'F'; break; // Magenta (Fight)
                case 7: temp.color = 'C'; break; // Yellow (Casino)
            }
        }
        temp.position = i;
        _tiles[path_index][i] = temp;
    }
}

bool Board::isPlayerOnTile(int pos, int path_index, int &playerOnTile) {
    for (int i = 0; i < _player_count; i++) {
        if (_player_position[i] == pos && _player_path[i] == path_index) {
            playerOnTile = i;
            return true;
        }
    }
    return false;
}

void Board::displayTile(int path_index, int pos) {
    string color = "";
    int playerOnTile = -1;
    char c = _tiles[path_index][pos].color;

    if      (c == 'R') color = RED;
    else if (c == 'G') color = GREEN;
    else if (c == 'B') color = BLUE;
    else if (c == 'U') color = PURPLE;
    else if (c == 'N') color = BROWN;
    else if (c == 'P') color = PINK;
    else if (c == 'O') color = ORANGE;
    else if (c == 'Y') color = GREY;
    else if (c == 'S') color = CYAN;
    else if (c == 'F') color = MAGENTA;
    else if (c == 'C') color = YELLOW;

    bool hasPlayer = isPlayerOnTile(pos, path_index, playerOnTile);
    if (hasPlayer) {
        cout << color << "|" << (playerOnTile + 1) << "|" << RESET;
    } else {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int path_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(path_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 2; i++) {
        cout << "Path " << i + 1 << ": ";
        displayTrack(i);
    }
}

bool Board::movePlayer(int player_index, int steps) {
    _last_move[player_index] = steps;
    _player_position[player_index] += steps;

    if (_player_position[player_index] >= _BOARD_SIZE - 1) {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true; // Reached end
    }
    if (_player_position[player_index] < 0) {
        _player_position[player_index] = 0;
    }
    return false;
}

int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index < _player_count) {
        return _player_position[player_index];
    }
    return -1;
}

void Board::setPlayerPath(int player_index, int path_index) {
    if (player_index >= 0 && player_index < _player_count &&
        path_index >= 0 && path_index < 2) {
        _player_path[player_index] = path_index;
    }
}

Tile Board::getTileAtPlayerPosition(int player_index) {
    int position = _player_position[player_index];
    int path = _player_path[player_index];
    return _tiles[path][position];
}

int Board::getPlayerPath(int player_index) const {
    if (player_index >= 0 && player_index < _player_count) {
        return _player_path[player_index];
    }
    return -1;
}

int Board::getLastMove(int player_index) const {
    if (player_index >= 0 && player_index < _player_count) {
        return _last_move[player_index];
    }
    return 0;
}
