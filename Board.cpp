#include "Board.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

#define RED    "\033[48;2;230;10;10m"
#define GREEN  "\033[48;2;34;139;34m"
#define BLUE   "\033[48;2;10;10;230m"
#define PINK   "\033[48;2;255;105;180m"
#define BROWN  "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m"
#define GREY   "\033[48;2;128;128;128m"
#define CYAN   "\033[48;2;0;255;255m"
#define YELLOW  "\033[48;2;255;255;0m"
#define RESET  "\033[0m"

using namespace std;

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
    for (int i = _player_count; i < _MAX_PLAYERS; i++) {
        _player_position[i] = 0;
        _player_path[i] = 0;
        _last_move[i] = 0;
    }

    initializeBoard();
}

void Board::initializeBoard() {
    // Initialize each path (0 and 1) with different tile distributions
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
}

void Board::initializeTiles(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // First pass: Place start(Y), end(O), exactly 30 green(G) tiles,
    // and the rest randomly from B,P,N,R,U,S,F,C
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Last tile: Orange (O) for "Pride Rock"
            temp.color = 'O';
        }
        else if (i == 0) {
            // First tile: Grey (Y) start tile
            temp.color = 'Y';
        }
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            // Place green (G) tile
            temp.color = 'G';
            green_count++;
        }
        else {
            // Randomly choose from B,P,N,R,U,S,C
            int color_choice = rand() % 8;
            switch (color_choice) {
            case 0: temp.color = 'B'; break; // Blue (Oasis)
            case 1: temp.color = 'P'; break; // Pink (Counseling)
            case 2: temp.color = 'N'; break; // Brown (Hyenas)
            case 3: temp.color = 'R'; break; // Red (Graveyard)
            case 4: temp.color = 'U'; break; // Purple (Challenge)
            case 5: temp.color = 'S'; break; // Cyan (Shop))
            case 6: temp.color = 'C'; break; // Yellow (Casino)
            }
        }

        _tiles[player_index][i] = temp;
    }

    // Second pass: Distribution function to ensure at least 20 special tiles.
    // Special tiles: B,P,N,R,U,S,F,C
    int specialCount = 0;
    for (int i = 0; i < total_tiles; i++) {
        char c = _tiles[player_index][i].color;
        if (c=='B' || c=='P' || c=='N' || c=='R' || c=='U' || c=='S' || c=='F' || c=='C') {
            specialCount++;
        }
    }

    // If fewer than 20 special tiles, convert some G tiles to special ones depending on path
    if (specialCount < 20) {
        for (int i = 1; i < total_tiles - 1 && specialCount < 20; i++) {
            char &c = _tiles[player_index][i].color;
            if (c == 'G') {
                if (player_index == 0) {
                    // Cub Training path: beneficial set (B,P,S,C)
                    int roll = rand() % 4;
                    if (roll == 0) c='B';
                    else if (roll == 1) c='P';
                    else if (roll == 2) c='S';
                    else c='C';
                } else {
                    // Straight to Pride Lands: challenging set (R,N,U,F)
                    int roll = rand() % 4;
                    if (roll == 0) c='R';
                    else if (roll == 1) c='N';
                    else if (roll == 2) c='U';
                    else c='F';
                }
                specialCount++;
            }
        }
    }
}


void Board::displayTile(int path_index, int pos)
{
    // Gather player icons
    string playerIcons = "";
    for (int i = 0; i < _player_count; i++) {
        if (_player_path[i] == path_index && _player_position[i] == pos) {
            playerIcons += to_string(i+1);
        }
    }

    // Determine tile color background
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
    else if (c == 'C') color = YELLOW;

    // Print the tile and reset immediately after
    if (playerIcons == "") {
        cout << color << "| |" << RESET;
    } else {
        cout << color << "|" << playerIcons << "|" << RESET;
    }
}


void Board::displayTrack(int path_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(path_index, i);
        if (_tiles[path_index][i].color == 'O') {
            // We've hit the win tile, end this track here
            break;
        }
    }
    cout << RESET << "\n"; // Ensure line reset after finishing track
}


void Board::displayBoard() {
    displayTrack(0);
    cout << endl; // extra line between lanes
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
    for(int i=0; i<playerCount; i++){
        positions[i] = getPlayerPosition(i);
    }
}

void Board::getAllPlayerPaths(int playerCount, int paths[]) const {
    for(int i=0; i<playerCount; i++){
        paths[i] = getPlayerPath(i);
    }
}
