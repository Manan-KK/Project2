#include "Tile.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static bool askRiddle(Player player, const Riddle riddles[], int rCount) {
    if(rCount==0) return false;
    int randomIndex=rand()%rCount;
    cout<<"[CHALLENGE] "<<riddles[randomIndex].question<<"\nYour Answer: ";
    string userAnswer;cin>>userAnswer;
    if(userAnswer==riddles[randomIndex].answer){
        cout<<"Correct! Your cunning grows.\n";
        return true;
    } else {
        cout<<"Incorrect. The answer was: "<<riddles[randomIndex].answer<<"\n";
        return false;
    }
}

static int advisorMenuChoice() {
    cout<<"\n[ADVISOR SELECTION]\n"
        <<"1. Chapter Master\n"
        <<"2. Ethereal\n"
        <<"3. Ork Mek\n"
        <<"4. Eldar Farseer\n"
        <<"5. Necron Cryptek\n"
        <<"0. None\n"
        <<"Choose an advisor: ";
    int choice;cin>>choice;
    if(choice<0||choice>5) choice=0;
    return choice;
}

Tile::Tile() {
    color='G';
    position=0;
}

int Tile::getType() const {
    if (color=='G') return REGULAR_TILE;
    else if (color=='B') return OASIS_TILE;
    else if (color=='P') return COUNSELING_TILE;
    else if (color=='R') return GRAVEYARD_TILE;
    else if (color=='N') return HYENAS_TILE;
    else if (color=='U') return CHALLENGE_TILE;
    else if (color=='O') return END_TILE;
    else if (color=='Y') return START_TILE;
    else if (color=='S') return SHOP_TILE;
    else if (color=='F') return FIGHT_TILE;
    else if (color=='C') return CASINO_TILE;
    return -1;
}

Player Tile::handleRegularTile(Player player, const RandomEvent events[], int eventCount) {
    cout<<"You landed on a Regular Tile.\n";
    int chance=rand()%2;
    if(chance==0){
        cout<<"No event triggered this time.\n";
        return player;
    }
    for(int attempt=0; attempt<10; attempt++){
        int eventIndex=rand()%eventCount;
        int eventPathType=events[eventIndex].pathType;
        if(eventPathType==2||eventPathType==player.getPathType()){
            int advNeeded=events[eventIndex].advisor;
            int change=events[eventIndex].honorChange;
            cout<<"Event: "<<events[eventIndex].description<<"\n";
            if(change<0){
                if(advNeeded!=0 && player.getAdvisor()==advNeeded){
                    cout<<"Your advisor protects you from harm!\n";
                } else {
                    cout<<"You lose "<<(-change)<<" Honor.\n";
                    player.decHonor(-change);
                }
            } else {
                cout<<"You gain "<<change<<" Honor.\n";
                player.incHonor(change);
            }
            return player;
        }
    }
    cout<<"No suitable event found.\n";
    return player;
}

Tile::OasisResult Tile::handleOasisTile(Player player) {
    cout<<"[OASIS] +200 to Might, Endurance, Cunning. You get another turn.\n";
    player.incMight(200);
    player.incEndurance(200);
    player.incCunning(200);
    OasisResult result;
    result.player = player;
    result.endTurn = false;
    return result;
}

Player Tile::handleCounselingTile(Player player, bool canChangeAdvisor) {
    cout<<"[COUNSELING] +300 to Might, Endurance, Cunning.\n";
    player.incMight(300);
    player.incEndurance(300);
    player.incCunning(300);
    if(canChangeAdvisor){
        cout<<"You may choose a new advisor.\n";
        int adv=advisorMenuChoice();
        if(adv!=0){
            player.setAdvisor(adv);
            cout<<"Advisor changed successfully.\n";
        } else {
            cout<<"No advisor change made.\n";
        }
    }
    return player;
}

Player Tile::handleGraveyardTile(Player player) {
    cout<<"[GRAVEYARD] Move back 10 spaces and -100 to all traits.\n";
    player.decMight(100);
    player.decEndurance(100);
    player.decCunning(100);
    return player;
}

Player Tile::handleHyenasTile(Player player, int lastMoveDistance) {
    cout<<"[GENESTEALERS] Return to previous position ("<<lastMoveDistance<<" steps back) and -300 Endurance.\n";
    player.decEndurance(300);
    return player;
}

Player Tile::handleChallengeTile(Player player, const Riddle riddles[], int riddleCount) {
    cout<<"[CHALLENGE] Answer correctly to gain +500 Cunning.\n";
    bool correct=askRiddle(player,riddles,riddleCount);
    if(correct){
        player.incCunning(500);
    }
    return player;
}

Player Tile::handleShopTile(Player player) {
    cout<<"[FORGE TEMPLE] Trade Honor for stat boosts:\n";
    bool shopping=true;
    while(shopping){
        cout<<"\n1. +100 Might (500 Honor)\n"
            <<"2. +100 Endurance (500 Honor)\n"
            <<"3. +100 Cunning (500 Honor)\n"
            <<"4. Exit Shop\n"
            <<"Choose an option: ";
        int shopChoice;cin>>shopChoice;
        if(shopChoice==4) {
            shopping=false;
        } else {
            if(player.getHonor()<500){
                cout<<"Not enough Honor.\n";
            } else {
                if(shopChoice==1){player.decHonor(500);player.incMight(100);cout<<"Might +100\n";}
                else if(shopChoice==2){player.decHonor(500);player.incEndurance(100);cout<<"Endurance +100\n";}
                else if(shopChoice==3){player.decHonor(500);player.incCunning(100);cout<<"Cunning +100\n";}
                else cout<<"Invalid choice.\n";
            }
        }
    }
    return player;
}

Player Tile::handleFightTile(Player players[], int playerCount, int currentPlayerIndex, Player currentPlayer) {
    cout<<"[DUELING GROUNDS] Challenge another player?\n1. Yes\n2. No\nYour choice: ";
    int fightChoice;cin>>fightChoice;
    if(fightChoice==1){
        cout<<"Choose a player to challenge:\n";
        for(int p=0;p<playerCount;p++){
            if(p!=currentPlayerIndex) cout<<p+1<<"."<<players[p].getName()<<endl;
        }
        int opponentChoice;cin>>opponentChoice;
        opponentChoice--;
        if(opponentChoice<0||opponentChoice>=playerCount||opponentChoice==currentPlayerIndex){
            cout<<"Invalid opponent.\n";
            return currentPlayer;
        }
        int currentPower=currentPlayer.getMight()+currentPlayer.getEndurance();
        int oppPower=players[opponentChoice].getMight()+players[opponentChoice].getEndurance();
        if(currentPower>oppPower){
            cout<<"You win the duel! +1000 Honor to you.\n";
            currentPlayer.incHonor(1000);
            Player opponentPlayer=players[opponentChoice];
            opponentPlayer.decHonor(1000);
            players[opponentChoice]=opponentPlayer;
        } else if(currentPower<oppPower){
            cout<<"You lost the duel. -1000 Honor.\n";
            currentPlayer.decHonor(1000);
            Player opponentPlayer=players[opponentChoice];
            opponentPlayer.incHonor(1000);
            players[opponentChoice]=opponentPlayer;
        } else {
            cout<<"It's a tie.\n";
        }
    } else {
        cout<<"You choose not to fight.\n";
    }
    return currentPlayer;
}

Player Tile::handleCasinoTile(Player player) {
    cout<<"[CASINO] Gamble between 0 and 1000 Honor:\nEnter amount: ";
    int gambleAmount;cin>>gambleAmount;
    if(gambleAmount<0)gambleAmount=0;
    if(gambleAmount>1000)gambleAmount=1000;
    if(gambleAmount>player.getHonor()) gambleAmount=player.getHonor();
    int outcome=rand()%6+1;
    if(outcome<=2){
        cout<<"You lose "<<gambleAmount<<" Honor.\n";
        player.decHonor(gambleAmount);
    } else if(outcome<=4){
        cout<<"You win "<<gambleAmount<<" Honor.\n";
        player.incHonor(gambleAmount);
    } else {
        cout<<"Jackpot! You win "<<gambleAmount*2<<" Honor.\n";
        player.incHonor(gambleAmount*2);
    }
    return player;
}

Player Tile::handleSameTileBattle(Player players[], int playerCount, int currentPlayerIndex, int currentPosition, int currentPath, const int playerPositions[], const int playerPaths[]) {
    Player current = players[currentPlayerIndex];
    int sameTilePlayers[4];
    int sameTileCount = 0;
    for (int p=0; p<playerCount; p++){
        if(p!=currentPlayerIndex && 
           playerPositions[p]==currentPosition && 
           playerPaths[p]==currentPath) {
            sameTilePlayers[sameTileCount]=p;
            sameTileCount++;
        }
    }

    if (sameTileCount == 0) {
        // No other players on the same tile
        return current;
    }

    cout << "[SAME TILE BATTLE] Multiple players share the tile! Time to fight.\n";
    int chosenOpponentIndex;

    if (sameTileCount > 1) {
        cout << "Choose an opponent:\n";
        for (int a = 0; a < sameTileCount; a++) {
            cout << a+1 << ". " << players[sameTilePlayers[a]].getName() << endl;
        }
        int opponentChoice;cin>>opponentChoice;
        opponentChoice--;
        if (opponentChoice < 0 || opponentChoice >= sameTileCount) opponentChoice = 0;
        chosenOpponentIndex = sameTilePlayers[opponentChoice];
    } else {
        chosenOpponentIndex = sameTilePlayers[0];
    }

    int currentPower = current.getMight() + current.getEndurance();
    int oppPower = players[chosenOpponentIndex].getMight() + players[chosenOpponentIndex].getEndurance();

    if (currentPower > oppPower) {
        cout << "You defeat " << players[chosenOpponentIndex].getName() << "! +500 Honor.\n";
        current.incHonor(500);
        Player opponentPlayer = players[chosenOpponentIndex];
        opponentPlayer.decHonor(500);
        players[chosenOpponentIndex] = opponentPlayer;
    } else if (currentPower < oppPower) {
        cout << players[chosenOpponentIndex].getName() << " defeats you! -500 Honor.\n";
        current.decHonor(500);
        Player opponentPlayer = players[chosenOpponentIndex];
        opponentPlayer.incHonor(500);
        players[chosenOpponentIndex] = opponentPlayer;
    } else {
        cout << "The battle ends in a tie.\n";
    }

    return current;
}
