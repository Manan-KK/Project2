#include "Board.h"
#include <iostream>

using namespace std;

// Color Definitions
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"
#define CYAN    "\033[48;2;0;255;255m"   /* Cyan (Shop) */
#define MAGENTA "\033[48;2;255;0;255m"   /* Magenta (Fight) */
#define YELLOW  "\033[48;2;255;255;0m"   /* Yellow (Casino) */

void Board::initializeBoard() {
    srand(time(0)); // Seed random number generator
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void Board::initializeTiles(int player_index) {
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    for (int i = 0; i < total_tiles; i++) {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } else if (i == 0) {
            // Set the first tile as Grey (Start)
            temp.color = 'Y';
        } else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        } else {
            // Assign one of the other colors randomly
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0: temp.color = 'B'; break; // Blue
                case 1: temp.color = 'P'; break; // Pink
                case 2: temp.color = 'N'; break; // Brown
                case 3: temp.color = 'R'; break; // Red
                case 4: temp.color = 'U'; break; // Purple
            }
        }
        _tiles[player_index][i] = temp;
    }
}

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
    }

    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    if (_player_position[player_index] == pos){
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos) {
    string color = "";
    bool player_present = isPlayerOnTile(player_index, pos);

    char c = _tiles[player_index][pos].color;

    // Map colors
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

    // Display the tile
    if (player_present) {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    } else {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 2; i++) {
        displayTrack(i);
        if (i == 0) {
            cout << endl; // Add a line between the two tracks
        }
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