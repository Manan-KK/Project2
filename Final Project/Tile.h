#ifndef TILE_H
#define TILE_H

#include <string>
#include "Player.h" // Needed because OasisResult stores a Player by value

struct RandomEvent {
    std::string description;
    int pathType; //0,1,2
    int advisor;  //0-5
    int honorChange;
};

struct Riddle {
    std::string question;
    std::string answer;
};

class Tile {
public:
    char color;
    int position;
    Tile();
    int getType() const;

    struct OasisResult {
        Player player;
        bool endTurn;
    };

    static Player handleRegularTile(Player player, const RandomEvent events[], int eventCount);
    static OasisResult handleOasisTile(Player player);
    static Player handleCounselingTile(Player player, bool canChangeAdvisor);
    static Player handleGraveyardTile(Player player);
    static Player handleHyenasTile(Player player, int lastMoveDistance);
    static Player handleChallengeTile(Player player, const Riddle riddles[], int riddleCount);
    static Player handleShopTile(Player player);
    static Player handleCasinoTile(Player player);
    static Player handleSameTileBattle(Player players[], int playerCount, int currentPlayerIndex, int currentPosition, int currentPath, const int playerPositions[], const int playerPaths[]);
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
#define CASINO_TILE 10

#endif
