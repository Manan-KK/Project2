// Tile.cpp
#include "Tile.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

// Function to handle Shop Tile interaction
void shopInteraction(BaseC &player) {
    cout << "Welcome to the Shop!" << endl;
    cout << "You can spend Victory Points to increase your attributes." << endl;
    cout << "1. Increase Attack by 100 (Cost: 500 Victory Points)" << endl;
    cout << "2. Increase Defense by 100 (Cost: 500 Victory Points)" << endl;
    cout << "3. Increase Intellect by 100 (Cost: 500 Victory Points)" << endl;
    cout << "4. Exit Shop" << endl;
    bool shopping = true;
    while (shopping) {
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                if (player.getVictoryPoints() >= 500) {
                    player.decreaseVictoryPoints(500);
                    player.increaseAttack(100);
                    cout << "Attack increased by 100." << endl;
                } else {
                    cout << "Not enough Victory Points." << endl;
                }
                break;
            case 2:
                if (player.getVictoryPoints() >= 500) {
                    player.decreaseVictoryPoints(500);
                    player.increaseDefense(100);
                    cout << "Defense increased by 100." << endl;
                } else {
                    cout << "Not enough Victory Points." << endl;
                }
                break;
            case 3:
                if (player.getVictoryPoints() >= 500) {
                    player.decreaseVictoryPoints(500);
                    player.increaseIntellect(100);
                    cout << "Intellect increased by 100." << endl;
                } else {
                    cout << "Not enough Victory Points." << endl;
                }
                break;
            case 4:
                shopping = false;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

// Function to handle riddles
bool askedriddle(BaseC &player){
    cout<<"Answer thy riddle:"<<endl;
    string chosenRiddle;
    ifstream file("riddles.txt");
    if(!file.is_open()){
        cout<<"Error. Unable to open riddles file."<<endl;
        return false;
    }
    string r1, r2, r3, r4, r5;
    string answer1, answer2, answer3, answer4, answer5;
    string line;
    int placeholder = 0;
    while(getline(file, line)){
        switch(placeholder){
            placeholder++;
            case 1:
                r1 = line;
                break;
            case 2:
                answer1 = line;
                break;
            case 3:
                answer2 = line;
                break;
            case 4:
                r2 = line;
                break;
            case 5:
                answer3 = line;
                break;
            case 6:
                r3 = line;
                break;
            case 7:
                answer4 = line;
                break;
            case 8:
                r4 = line;
                break;
            case 9:
                answer5 = line;
                break;
            case 10:
                r5 = line;
                break;
        }
    }
    int riddle = rand() % 5 + 1;
    string answer;
    switch(riddle){
        case 1:
            cout<<r1<<endl;
            cin>>answer;
            if(answer==answer1){
                return true;
            }
            break;
        case 2:
            cout<<r2<<endl;
            cin>>answer;
            if(answer==answer2){
                return true;
            }
            break;
        case 3:
            cout<<r3<<endl;
            cin>>answer;
            if(answer==answer3){
                return true;
            }
            break;
        case 4:
            cout<<r4<<endl;
            cin>>answer;
            if(answer==answer4){
                return true;
            }
            break;
        case 5:
            cout<<r5<<endl;
            cin>>answer;
            if(answer==answer5){
                return true;
            }
            break;
    }
    return false;
}

// Function to handle Fight Tile interaction
void fightInteraction(BaseC &player, vector<BaseC> &players, int currentPlayerIndex) {
    cout << "You have landed on a Fight Tile!" << endl;
    cout << "Would you like to challenge another player? (1 for Yes, 2 for No): ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "Choose a player to fight:" << endl;
        for (int i = 0; i < players.size(); i++) {
            if (i != currentPlayerIndex) {
                cout << i + 1 << ". " << players[i].getName() << endl;
            }
        }
        int opponentIndex;
        cin >> opponentIndex;
        opponentIndex--; // Adjust for zero-based indexing
        if (opponentIndex >= 0 && opponentIndex < players.size() && opponentIndex != currentPlayerIndex) {
            BaseC &opponent = players[opponentIndex];
            cout << "You challenge " << opponent.getName() << " to a fight!" << endl;
            // Simple fight logic based on Attack and Defense
            int playerPower = player.getAttack() + player.getDefense();
            int opponentPower = opponent.getAttack() + opponent.getDefense();
            if (playerPower > opponentPower) {
                cout << "You win the fight!" << endl;
                player.increaseVictoryPoints(1000);
                opponent.decreaseVictoryPoints(1000);
            } else if (playerPower < opponentPower) {
                cout << "You lose the fight!" << endl;
                player.decreaseVictoryPoints(1000);
                opponent.increaseVictoryPoints(1000);
            } else {
                cout << "It's a tie!" << endl;
                // No change in Victory Points
            }
        } else {
            cout << "Invalid player selected." << endl;
        }
    } else {
        cout << "You chose not to fight." << endl;
    }
}

// Function to handle Casino Tile interaction
void casinoInteraction(BaseC &player) {
    cout << "Welcome to the Casino!" << endl;
    cout << "You can gamble your Victory Points for a chance to win big!" << endl;
    cout << "Enter the amount of Victory Points you want to gamble (0 to 1000): ";
    int amount;
    cin >> amount;
    while (amount < 0 || amount > 1000 || amount > player.getVictoryPoints()) {
        cout << "Invalid amount. Please enter a value between 0 and " << min(1000, player.getVictoryPoints()) << ": ";
        cin >> amount;
    }
    cout << "Rolling the dice..." << endl;
    int outcome = rand() % 6 + 1; // Random number between 1 and 6
    if (outcome <= 2) {
        // Lose amount
        player.decreaseVictoryPoints(amount);
        cout << "You lost " << amount << " Victory Points." << endl;
    } else if (outcome <= 4) {
        // Win amount
        player.increaseVictoryPoints(amount);
        cout << "You won " << amount << " Victory Points!" << endl;
    } else {
        // Win double
        player.increaseVictoryPoints(amount * 2);
        cout << "Jackpot! You won " << amount * 2 << " Victory Points!" << endl;
    }
}

bool randomEvent(BaseC &player){
    int chances = rand() % 20 + 1;
    switch(chances){
        case 1:
            cout<<"A Necron fleet has been encountered!"<<endl;
            if(player.getDefense() > 600){
                cout<<"Your defense was able to hold them off! You savor your sweet victory. You gained 500 victory points." << endl;
                player.increaseVictoryPoints(500);
            }
            break;
        case 2:
            cout<<""
            break;
        case 3:
            break;
        default:
            return false;
    }
}

Tile::Tile() {
    color = 'G'; // Default color
    position = 0;
}

int Tile::getType() {
    if (color == 'G') // Green
        return REGULAR_TILE;
    else if (color == 'B') // Blue
        return OASIS_TILE;
    else if (color == 'P') // Pink
        return COUNSELING_TILE;
    else if (color == 'R') // Red
        return GRAVEYARD_TILE;
    else if (color == 'N') // Brown
        return HYENAS_TILE;
    else if (color == 'U') // Purple
        return CHALLENGE_TILE;
    else if (color == 'O') // Orange
        return END_TILE;
    else if (color == 'Y') // Grey
        return START_TILE;
    else if (color == 'S') // Cyan - Shop Tile
        return SHOP_TILE;
    else if (color == 'F') // Magenta - Fight Tile
        return FIGHT_TILE;
    else if (color == 'C') // Yellow - Casino Tile
        return CASINO_TILE;
    else
        return -1; // Unknown type
}

void Tile::triggerEffect(BaseC &player, Board &board, vector<BaseC> &players, int currentPlayerIndex, bool &endTurn) {
    int move = 0; // For movement adjustments
    switch (getType()) {
        case REGULAR_TILE:
            // Handle regular tile
            cout << "You have landed on a regular tile." << endl;
            randomEvent();
            // Implement random event affecting Victory Points
            // Placeholder for random event
            break;
        case OASIS_TILE:
            // Handle oasis tile
            cout << "You have found a supply cache!" << endl;
            // Increase player's stats
            player.increaseAttack(200);
            player.increaseDefense(200);
            player.increaseIntellect(200);
            cout << "Your Attack, Defense, and Intellect have each increased by 200." << endl;
            // Grant extra turn
            endTurn = false;
            break;
        case COUNSELING_TILE:
            // Handle counseling tile
            cout << "You have met a mentor!" << endl;
            // Increase player's stats
            player.increaseAttack(300);
            player.increaseDefense(300);
            player.increaseIntellect(300);
            cout << "Your Attack, Defense, and Intellect have each increased by 300." << endl;
            // Advisor selection or change (to be implemented)
            break;
        case GRAVEYARD_TILE:
            // Handle graveyard tile
            cout << "You have entered a dangerous battlefield!" << endl;
            // Move back 10 tiles
            board.movePlayer(currentPlayerIndex, -10);
            cout << "You have been pushed back 10 spaces." << endl;
            // Decrease stats
            player.decreaseAttack(100);
            player.decreaseDefense(100);
            player.decreaseIntellect(100);
            cout << "Your Attack, Defense, and Intellect have each decreased by 100." << endl;
            break;
        case HYENAS_TILE:
            // Handle enemy ambush tile
            cout << "You have been ambushed by enemies!" << endl;
            // Return to previous position
            cout << "You have been forced back to your previous position." << endl;
            board.movePlayer(currentPlayerIndex, -1 * (board.getLastMove(currentPlayerIndex)));
            // Decrease Defense
            player.decreaseDefense(300);
            cout << "Your Defense has decreased by 300." << endl;
            break;
        case CHALLENGE_TILE:
            // Handle challenge tile
            cout << "You have encountered a challenge!" << endl;
            // Implement challenge (e.g., riddle)
            // Placeholder for challenge
            if(askedriddle(player)){
                player.increaseIntellect(500);
                cout << "You solved the challenge! Your Intellect increases by 500." << endl;
            }
            else{
                cout << "Incorrect. Better luck next time." << endl;
            }
            break;
        case SHOP_TILE:
            // Handle shop tile
            shopInteraction(player);
            break;
        case FIGHT_TILE:
            // Handle fight tile
            fightInteraction(player, players, currentPlayerIndex);
            break;
        case CASINO_TILE:
            // Handle casino tile
            casinoInteraction(player);
            break;
        case END_TILE:
            // Player has reached the end
            cout << "You have reached the end of the board!" << endl;
            // No action needed; handled in main loop
            break;
        default:
            cout << "You have landed on an unknown tile." << endl;
            break;
    }
}

