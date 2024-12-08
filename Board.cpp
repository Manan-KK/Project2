// Board.cpp
#include "Board.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define CYAN "\033[48;2;0;255;255m"   /* Cyan for Shop Tile */
#define MAGENTA "\033[48;2;255;0;255m" /* Magenta for Fight Tile */
#define YELLOW "\033[48;2;255;255;0m" /* Yellow for Casino Tile */
#define RESET "\033[0m"

Board::Board()
{
    _player_count = 1;
    for (int i = 0; i < _MAX_PLAYERS; i++)
    {
        _player_position[i] = 0;
        _player_path[i] = 0;
        _last_move[i] = 0;
    }
    initializeBoard();
}

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player positions and paths
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
        _player_path[i] = 0; // Default path is 0
        _last_move[i] = 0;
    }

    initializeBoard();
}

void Board::initializeBoard()
{

    // Initialize tiles for both paths
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i); // This ensures each path has a unique tile distribution
    }
}

void Board::initializeTiles(int path_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 20 greens
    int green_tiles_needed = 20;
    int special_tiles_needed = 32; // Remaining tiles will be special tiles

    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1)
        {
            // Set the last tile as Orange for "End Tile"
            temp.color = 'O';
        }
        else if (i == 0)
        {
            // Set the first tile as Grey for "Start Tile"
            temp.color = 'Y';
        }
        else if (green_count < green_tiles_needed && (rand() % (total_tiles - i) < green_tiles_needed - green_count))
        {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the special tiles
            int color_choice = rand() % 8;
            switch (color_choice)
            {
            case 0:
                temp.color = 'B'; // Blue (Oasis)
                break;
            case 1:
                temp.color = 'P'; // Pink (Counseling)
                break;
            case 2:
                temp.color = 'N'; // Brown (Hyenas)
                break;
            case 3:
                temp.color = 'R'; // Red (Graveyard)
                break;
            case 4:
                temp.color = 'U'; // Purple (Challenge)
                break;
            case 5:
                temp.color = 'S'; // Cyan (Shop)
                break;
            case 6:
                temp.color = 'F'; // Magenta (Fight)
                break;
            case 7:
                temp.color = 'C'; // Yellow (Casino)
                break;
            }
        }
        temp.position = i;
        _tiles[path_index][i] = temp;
    }
}

void Board::displayTile(int path_index, int pos)
{
    string color = "";
    int playerOnTile = -1;

    // Determine color to display
    if (_tiles[path_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[path_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[path_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[path_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[path_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[path_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[path_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[path_index][pos].color == 'Y')
    {
        color = GREY;
    }
    else if (_tiles[path_index][pos].color == 'S')
    {
        color = CYAN;
    }
    else if (_tiles[path_index][pos].color == 'F')
    {
        color = MAGENTA;
    }
    else if (_tiles[path_index][pos].color == 'C')
    {
        color = YELLOW;
    }

    bool hasPlayer = isPlayerOnTile(pos, path_index, playerOnTile);

    if (hasPlayer)
    {
        cout << color << "|" << (playerOnTile + 1) << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int path_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(path_index, i);
    }
    cout << endl;
}

void Board::displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        cout << "Path " << i + 1 << ": ";
        displayTrack(i);
    }
}

bool Board::isPlayerOnTile(int pos, int path_index, int &playerOnTile)
{
    for (int i = 0; i < _player_count; i++)
    {
        if (_player_position[i] == pos && _player_path[i] == path_index)
        {
            playerOnTile = i;
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int player_index, int steps)
{
    int path = _player_path[player_index];
    _last_move[player_index] = steps; // Store the last move
    _player_position[player_index] += steps;
    if (_player_position[player_index] >= _BOARD_SIZE - 1)
    {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true; // Player reached end
    }
    if (_player_position[player_index] < 0)
    {
        _player_position[player_index] = 0;
    }
    return false;
}

int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index < _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}

void Board::setPlayerPath(int player_index, int path_index)
{
    if (player_index >= 0 && player_index < _player_count && path_index >= 0 && path_index < 2)
    {
        _player_path[player_index] = path_index;
    }
}

Tile Board::getTileAtPlayerPosition(int player_index)
{
    int position = _player_position[player_index];
    int path = _player_path[player_index];
    return _tiles[path][position];
}

int Board::getPlayerPath(int player_index) const
{
    if (player_index >= 0 && player_index < _player_count)
    {
        return _player_path[player_index];
    }
    return -1;
}

int Board::getLastMove(int player_index) const
{
    if (player_index >= 0 && player_index < _player_count)
    {
        return _last_move[player_index];
    }
    return 0;
}
