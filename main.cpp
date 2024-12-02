// main.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Tile.h"

using namespace std;

int main() {
    srand(time(0));

    const int MAX_PLAYERS = 4;
    int numPlayers;

    // Welcome message
    cout << "Welcome to the Warhammer 40K Board Game!" << endl;

    // Get number of players
    cout << "Enter number of players (1-" << MAX_PLAYERS << "): ";
    cin >> numPlayers;
    while (numPlayers < 1 || numPlayers > MAX_PLAYERS) {
        cout << "Invalid number of players. Please enter a number between 1 and " << MAX_PLAYERS << ": ";
        cin >> numPlayers;
    }

    // Initialize Board
    Board gameBoard(numPlayers);

    // Initialize Players
    vector<BaseC> players;
    vector<string> playerNames;

    // Read character data from file
    ifstream characterFile("characters.txt");
    if (!characterFile) {
        cout << "Error: Could not open characters.txt file." << endl;
        return 1;
    }

    vector<string> characterNames;
    vector<int> characterAges;
    vector<int> characterAttacks;
    vector<int> characterDefenses;
    vector<int> characterIntellects;

    // Read characters from file
    string line;
    while (getline(characterFile, line)) {
        // Format: CharacterName|age|attack|defense|intellect
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line); // Add the last token

        if (tokens.size() >= 5) {
            characterNames.push_back(tokens[0]);
            characterAges.push_back(atoi(tokens[1].c_str()));
            characterAttacks.push_back(atoi(tokens[2].c_str()));
            characterDefenses.push_back(atoi(tokens[3].c_str()));
            characterIntellects.push_back(atoi(tokens[4].c_str()));
        }
    }

    characterFile.close();

    // Now, let players choose their characters and paths
    vector<bool> characterChosen(characterNames.size(), false);

    for (int i = 0; i < numPlayers; i++) {
        string playerName;
        cout << "Player " << (i + 1) << ", enter your name: ";
        cin >> playerName;
        playerNames.push_back(playerName);

        // Display available characters
        cout << "Available characters:" << endl;
        for (size_t j = 0; j < characterNames.size(); j++) {
            if (!characterChosen[j]) {
                cout << j + 1 << ". " << characterNames[j] << endl;
            }
        }

        // Player chooses character
        int choice;
        cout << playerName << ", choose your character (enter the number): ";
        cin >> choice;
        while (choice < 1 || choice > (int)characterNames.size() || characterChosen[choice - 1]) {
            cout << "Invalid choice. Please choose an available character: ";
            cin >> choice;
        }

        // Mark character as chosen
        characterChosen[choice - 1] = true;

        // Create player with chosen character stats
        int age = characterAges[choice - 1];
        int attack = characterAttacks[choice - 1];
        int defense = characterDefenses[choice - 1];
        int intellect = characterIntellects[choice - 1];
        string characterName = characterNames[choice - 1];

        // Initialize player with default Victory Points
        BaseC player(characterName, age, attack, defense, intellect, 20000);

        // Prompt for path choice
        cout << "Choose your Path Type:" << endl;
        cout << "1. Specialized Training" << endl;
        cout << "2. Straight to the Battlefront" << endl;
        cout << "Enter the number of your choice: ";
        int pathChoice;
        cin >> pathChoice;
        while (pathChoice != 1 && pathChoice != 2) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> pathChoice;
        }

        // Update player's stats based on path choice
        if (pathChoice == 1) {
            // Specialized Training
            player.decreaseVictoryPoints(5000);
            player.increaseAttack(500);
            player.increaseDefense(500);
            player.increaseIntellect(1000);
            cout << "You have chosen Specialized Training." << endl;
            cout << "-5000 Victory Points, +500 Attack, +500 Defense, +1000 Intellect." << endl;
            // Advisor selection (to be implemented)
        } else if (pathChoice == 2) {
            // Straight to the Battlefront
            player.increaseVictoryPoints(5000);
            player.increaseAttack(200);
            player.increaseDefense(200);
            player.increaseIntellect(200);
            cout << "You have chosen Straight to the Battlefront." << endl;
            cout << "+5000 Victory Points, +200 Attack, +200 Defense, +200 Intellect." << endl;
        }

        // Set player's path type
        player.setPathType(pathChoice - 1); // 0 or 1

        // Set player's path in the board
        gameBoard.setPlayerPath(i, pathChoice - 1);

        // Add player to the list
        players.push_back(player);

        cout << playerName << " has chosen " << characterName << "!" << endl << endl;
    }

    // Game loop variables
    bool gameOver = false;

    // Main game loop
    while (!gameOver) {
        // For each player
        for (int i = 0; i < numPlayers; i++) {
            cout << "----------------------------------------" << endl;
            cout << playerNames[i] << "'s turn." << endl;

            // Display the board at the start of the player's turn
            cout << "Current Board:" << endl;
            gameBoard.displayBoard();

            // Display main menu
            bool endTurn = false;
            while (!endTurn) {
                cout << "Main Menu:" << endl;
                cout << "1. Check Player Progress" << endl;
                cout << "2. Review Character" << endl;
                cout << "3. Check Position" << endl;
                cout << "4. Review Advisor" << endl;
                cout << "5. Move Forward" << endl;
                cout << "Please choose an option: ";
                int menuChoice;
                cin >> menuChoice;

                switch (menuChoice) {
                    case 1:
                        // Check Player Progress
                        cout << "Player Progress:" << endl;
                        players[i].displayStats();
                        break;
                    case 2:
                        // Review Character
                        cout << "Character Name: " << players[i].getName() << endl;
                        cout << "Age: " << players[i].getAge() << endl;
                        break;
                    case 3:
                        // Check Position
                        cout << "Current Position: " << gameBoard.getPlayerPosition(i) << endl;
                        // Display board
                        cout << "Current Board:" << endl;
                        gameBoard.displayBoard();
                        break;
                    case 4:
                        // Review Advisor
                        // Placeholder for future implementation
                        cout << "Advisor: None (to be implemented)" << endl;
                        break;
                    case 5: {
                        // Move Forward
                        int move;
                        cout << "Press Enter to spin the spinner.";
                        cin.ignore();
                        cin.get(); // Wait for user to press Enter
                        move = rand() % 6 + 1; // Random number between 1 and 6
                        cout << "You spin the spinner and move " << move << " spaces." << endl;

                        // Move the player on the board
                        bool reachedEnd = gameBoard.movePlayer(i, move);
                        int currentPosition = gameBoard.getPlayerPosition(i);
                        cout << "You are now at position " << currentPosition << "." << endl;

                        // Display the board after moving
                        cout << "Current Board:" << endl;
                        gameBoard.displayBoard();

                        // Get the tile at the player's current position
                        Tile currentTile = gameBoard.getTileAtPlayerPosition(i);

                        // Process the tile effect
                        endTurn = true; // Assume turn ends unless changed by tile effect
                        currentTile.triggerEffect(players[i], gameBoard, players, i, endTurn);

                        // Check if player has reached the end
                        if (reachedEnd) {
                            cout << "You have reached the end of the board!" << endl;
                        }

                        break;
                    }
                    default:
                        cout << "Invalid choice. Please select a valid option." << endl;
                        break;
                }
            }

            // Check if game is over
            // Game is over when all players reach the end
            bool allPlayersAtEnd = true;
            for (int j = 0; j < numPlayers; j++) {
                if (gameBoard.getPlayerPosition(j) < 51) {
                    allPlayersAtEnd = false;
                    break;
                }
            }
            if (allPlayersAtEnd) {
                gameOver = true;
                break;
            }
        }
    }

    // Game over
    cout << "----------------------------------------" << endl;
    cout << "Game over!" << endl;

    // Convert Traits to Victory Points
    for (int i = 0; i < numPlayers; i++) {
        int totalTraits = players[i].getAttack() + players[i].getDefense() + players[i].getIntellect();
        int additionalPoints = (totalTraits / 100) * 1000;
        players[i].increaseVictoryPoints(additionalPoints);
    }

    // Leaderboard: sort players by Victory Points using selection sort
    vector<int> indices(numPlayers);
    for (int i = 0; i < numPlayers; i++) {
        indices[i] = i;
    }

    // Sorting algorithm
    for (int i = 0; i < numPlayers - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < numPlayers; j++) {
            if (players[indices[j]].getVictoryPoints() > players[indices[maxIdx]].getVictoryPoints()) {
                maxIdx = j;
            }
        }
        // Swap indices
        int temp = indices[i];
        indices[i] = indices[maxIdx];
        indices[maxIdx] = temp;
    }

    // Display leaderboard
    cout << "Leaderboard:" << endl;
    for (int i = 0; i < numPlayers; i++) {
        int idx = indices[i];
        cout << (i + 1) << ". " << players[idx].getName() << " - Victory Points: " << players[idx].getVictoryPoints() << endl;
    }

    // Congratulate the winner
    cout << "Congratulations, " << players[indices[0]].getName() << "! You are the winner!" << endl;

    // Write game stats to a file (file I/O)
    ofstream outFile("game_results.txt");
    if (outFile.is_open()) {
        outFile << "Game Results:\n";
        for (int i = 0; i < numPlayers; i++) {
            int idx = indices[i];
            outFile << (i + 1) << ". " << players[idx].getName() << " - Victory Points: " << players[idx].getVictoryPoints() << "\n";
        }
        outFile.close();
        cout << "Game results have been saved to game_results.txt" << endl;
    } else {
        cout << "Error: Could not write to game_results.txt" << endl;
    }

    return 0;
}
