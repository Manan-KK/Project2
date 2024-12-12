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
    // Start tile at index 0: Y, End tile at index 51: O
    // Distinct distributions for path 0 and path 1
    int total_tiles = _BOARD_SIZE;
    _tiles[path_index][0].color = 'Y';
    _tiles[path_index][total_tiles-1].color = 'O';

    int specialCount = 0;
    for (int i = 1; i < total_tiles-1; i++) {
        char chosenColor = 'G'; 
        if (path_index == 0) {
            // Cub Training: more beneficial tiles
            int roll = rand()%100;
            if(roll < 15) { chosenColor='B'; specialCount++; }  
            else if(roll < 30) { chosenColor='P'; specialCount++; }
            else if(roll < 35) { chosenColor='U'; specialCount++; } 
            else if(roll < 40) { chosenColor='N'; specialCount++; } 
            else if(roll < 45) { chosenColor='R'; specialCount++; } 
            else { chosenColor='G'; }
        } else {
            // Straight to Pride Lands: more challenging tiles
            int roll = rand()%100;
            if(roll < 15) { chosenColor='R'; specialCount++; }
            else if(roll < 30) { chosenColor='N'; specialCount++; }
            else if(roll < 45) { chosenColor='U'; specialCount++; }
            else if(roll < 55) { chosenColor='B'; specialCount++; }
            else if(roll < 65) { chosenColor='P'; specialCount++; }
            else { chosenColor='G'; }
        }
        _tiles[path_index][i].color = chosenColor;
    }

    // Ensure at least 20 special tiles
    if(specialCount < 20) {
        for(int i=1; i<total_tiles-1 && specialCount<20; i++){
            if(_tiles[path_index][i].color=='G') {
                _tiles[path_index][i].color = (path_index==0?'B':'R');
                specialCount++;
            }
        }
    }
}

void Board::displayTile(int path_index, int pos) {
    string playerIcons = "";
    for(int i=0;i<_player_count;i++){
        if(_player_path[i] == path_index && _player_position[i] == pos) {
            playerIcons += to_string(i+1);
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

    if(playerIcons == "") {
        cout << color << "| |" << RESET;
    } else {
        cout << color << "|" << playerIcons << "|" << RESET;
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
