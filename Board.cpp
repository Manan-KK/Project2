#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define RESET "\033[0m"
#define CYAN    "\033[48;2;0;255;255m"
#define MAGENTA "\033[48;2;255;0;255m"
#define YELLOW  "\033[48;2;255;255;0m"

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
        _player_path[i]=0;
        _last_move[i]=0;
    }
    for(int i=_player_count;i<_MAX_PLAYERS;i++){
        _player_position[i]=0;_player_path[i]=0;_last_move[i]=0;
    }

    initializeBoard();
}

void Board::initializeBoard() {
    srand((unsigned)time(0));
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
}

void Board::initializeTiles(int path_index) {
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    for (int i = 0; i < total_tiles; i++) {
        if (i == total_tiles - 1) {
            temp.color = 'O'; // end
        } else if (i == 0) {
            temp.color = 'Y'; // start
        } else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        } else {
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0: temp.color = 'B'; break; // Blue
                case 1: temp.color = 'P'; break; // Pink
                case 2: temp.color = 'N'; break; // Brown
                case 3: temp.color = 'R'; break; // Red
                case 4: temp.color = 'U'; break; // Purple
            }
        }
        _tiles[path_index][i] = temp;
    }
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    return (_player_position[player_index] == pos);
}

void Board::displayTile(int path_index, int pos) {
    bool player_present = false;
    int whichPlayer = -1;
    for(int i=0;i<_player_count;i++){
        if(_player_path[i]==path_index && _player_position[i]==pos){
            player_present=true;
            whichPlayer=i;
            break;
        }
    }

    char c = _tiles[path_index][pos].color;
    string color = "";
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

    if (player_present) {
        cout << color << "|" << (whichPlayer+1) << "|" << RESET;
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
    displayTrack(0);
    cout << endl;
    displayTrack(1);
}

bool Board::movePlayer(int player_index, int steps) {
    _last_move[player_index] = steps;
    _player_position[player_index] += steps;

    if (_player_position[player_index] >= _BOARD_SIZE - 1) {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true;
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

void Board::getAllPlayerPositions(int playerCount, int positions[]) const {
    for(int i=0;i<playerCount;i++){
        positions[i]=getPlayerPosition(i);
    }
}

void Board::getAllPlayerPaths(int playerCount, int paths[]) const {
    for(int i=0;i<playerCount;i++){
        paths[i]=getPlayerPath(i);
    }
}
