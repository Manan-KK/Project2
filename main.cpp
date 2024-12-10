#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Tile.h"

using namespace std;

void loadCharacters(string filename, string names[], int ages[], int mights[], int ends[], int cunnings[], int &count) {
    ifstream file(filename.c_str());
    count = 0;
    if(!file.is_open()) return;
    string line;
    while(getline(file,line)) {
        if(line=="") continue;
        string tokens[5];
        int tokenCount=0;
        {
            string current="";
            for (int i = 0; i<(int)line.size(); i++) {
                if(line[i]=='|') {
                    if(tokenCount<5) tokens[tokenCount]=current;
                    tokenCount++;
                    current="";
                    if(tokenCount==4) {
                        tokens[tokenCount]=line.substr(i+1);
                        tokenCount++;
                        break;
                    }
                } else {
                    current+=line[i];
                }
            }
            if(tokenCount<5 && current!="") {
                tokens[tokenCount]=current;
                tokenCount++;
            }
        }

        if(tokenCount==5){
            names[count]=tokens[0];
            ages[count]=stoi(tokens[1]);
            mights[count]=stoi(tokens[2]);
            ends[count]=stoi(tokens[3]);
            cunnings[count]=stoi(tokens[4]);
            count++;
            if(count>=20) break;
        }
    }
    file.close();
}

void loadRandomEvents(string filename, RandomEvent events[], int &count) {
    ifstream file(filename.c_str());
    count=0;
    if(!file.is_open()) return;
    string line;
    while(getline(file,line)){
        if(line=="") continue;
        string tokens[4];
        int tokenCount=0;
        {
            string current="";
            for (int i = 0; i<(int)line.size(); i++) {
                if(line[i]=='|') {
                    if(tokenCount<4) tokens[tokenCount]=current;
                    tokenCount++;
                    current="";
                    if(tokenCount==3) {
                        tokens[tokenCount]=line.substr(i+1);
                        tokenCount++;
                        break;
                    }
                } else {
                    current+=line[i];
                }
            }
            if(tokenCount<4 && current!="") {
                tokens[tokenCount]=current;
                tokenCount++;
            }
        }

        if(tokenCount==4){
            events[count].description=tokens[0];
            events[count].pathType=stoi(tokens[1]);
            events[count].advisor=stoi(tokens[2]);
            events[count].honorChange=stoi(tokens[3]);
            count++;
            if(count>=100) break;
        }
    }
    file.close();
}

void loadRiddles(string filename, Riddle riddles[], int &count) {
    ifstream file(filename.c_str());
    count=0;
    if(!file.is_open()) return;
    while(true){
        string questionLine, answerLine;
        if(!getline(file,questionLine)) break;
        if(!getline(file,answerLine)) break;
        if(questionLine=="" || answerLine=="") break;
        riddles[count].question=questionLine;
        riddles[count].answer=answerLine;
        count++;
        if(count>=50) break;
    }
    file.close();
}

int main(){
    srand((unsigned)time(0));
    const int MAX_PLAYERS=4;
    int numPlayers;
    cout<<"=========================================\n"
        <<"Welcome to the Warhammer 40K Honor Trial!\n"
        <<"=========================================\n"
        <<"Enter number of players (1-4): ";
    cin>>numPlayers;
    while(numPlayers<1||numPlayers>MAX_PLAYERS){
        cout<<"Invalid number. Enter 1-4: ";
        cin>>numPlayers;
    }

    Board gameBoard(numPlayers);
    Player players[MAX_PLAYERS];

    string cNames[20];int cAges[20];int cMight[20];int cEnd[20];int cCunn[20];int charCount=0;
    for(int i=0;i<20;i++){cNames[i]="";}
    loadCharacters("characters.txt",cNames,cAges,cMight,cEnd,cCunn,charCount);
    bool chosenCharacters[20];
    for(int i=0;i<20;i++) chosenCharacters[i]=false;

    for(int playerIndex=0;playerIndex<numPlayers;playerIndex++){
        cout<<"\nPlayer "<<playerIndex+1<<", enter your IRL name: ";
        string pName;cin>>pName;

        cout<<"\nAvailable characters:\n";
        for(int c=0;c<charCount;c++){
            if(!chosenCharacters[c]) cout<<c+1<<"."<<cNames[c]<<endl;
        }
        cout<<"Choose a character by number: ";
        int characterChoice;cin>>characterChoice;
        characterChoice--;
        while(characterChoice<0||characterChoice>=charCount||chosenCharacters[characterChoice]){
            cout<<"Invalid. Choose again: ";
            cin>>characterChoice;characterChoice--;
        }
        chosenCharacters[characterChoice]=true;
        Player p(cNames[characterChoice], cAges[characterChoice],
                 cMight[characterChoice], cEnd[characterChoice],
                 cCunn[characterChoice], 20000);

        cout<<"\nChoose your path:\n"
            <<"1. Chapter Training Grounds(-5000 Honor,+500M/+500E/+1000C)\n"
            <<"2. Frontline(+5000 Honor,+200 all)\n"
            <<"Your choice: ";
        int pathChoice;cin>>pathChoice;
        while(pathChoice!=1&&pathChoice!=2){
            cout<<"Invalid.\n";
            cin>>pathChoice;
        }
        if(pathChoice==1){
            p.decHonor(5000);
            p.incMight(500);
            p.incEndurance(500);
            p.incCunning(1000);
            p.setPathType(0);
            cout<<"Initial advisor selection:\n";
            cout<<"1. Chapter Master\n2. Ethereal\n3. Ork Mek\n4. Eldar Farseer\n5. Necron Cryptek\n0. None\nChoice: ";
            int advChoice;cin>>advChoice;
            if(advChoice<0||advChoice>5) advChoice=0;
            if(advChoice!=0)p.setAdvisor(advChoice);
        } else {
            p.incHonor(5000);
            p.incMight(200);
            p.incEndurance(200);
            p.incCunning(200);
            p.setPathType(1);
        }
        gameBoard.setPlayerPath(playerIndex,p.getPathType());
        p.setName(pName);
        cout<<pName<<" has chosen the character: "<<p.getName()<<"!\n";
        players[playerIndex]=p;
    }

    RandomEvent events[100];int eventCount=0;
    loadRandomEvents("random_events.txt",events,eventCount);

    Riddle riddles[50];int riddleCount=0;
    loadRiddles("riddles.txt",riddles,riddleCount);

    bool gameOver=false;

    while(!gameOver){
        for(int currentPlayerIndex=0; currentPlayerIndex<numPlayers; currentPlayerIndex++){
            for(int p=0;p<numPlayers;p++){
                if(gameBoard.getPlayerPosition(p)>=51){
                    gameOver=true;
                    break;
                }
            }
            if(gameOver) break;

            cout<<"\n----------------------------------\n";
            cout<<players[currentPlayerIndex].getName()<<"'s turn.\n";
            gameBoard.displayBoard();
            bool endTurn=false;
            while(!endTurn && !gameOver){
                cout<<"\n[MAIN MENU]\n"
                    <<"1. Check Progress\n"
                    <<"2. Review Character\n"
                    <<"3. Check Position\n"
                    <<"4. Review Advisor\n"
                    <<"5. Move Forward\n"
                    <<"Choose an option: ";
                int menuChoice;cin>>menuChoice;
                if(menuChoice==1){
                    players[currentPlayerIndex].displayStats();
                    cout<<"\n1. Convert Traits to Honor\n2. Back\nChoice: ";
                    int subMenu;cin>>subMenu;
                    if(subMenu==1){
                        players[currentPlayerIndex].convertTraitsToHonor();
                        cout<<"Traits converted to additional Honor.\n";
                    }
                } else if(menuChoice==2){
                    cout<<"Character: "<<players[currentPlayerIndex].getName()
                        <<", Age:"<<players[currentPlayerIndex].getAge()<<endl;
                } else if(menuChoice==3){
                    cout<<"Current Tile Position: "<<gameBoard.getPlayerPosition(currentPlayerIndex)<<endl;
                    gameBoard.displayBoard();
                } else if(menuChoice==4){
                    cout<<"Current Advisor: ";
                    int adv=players[currentPlayerIndex].getAdvisor();
                    if(adv==1)cout<<"Chapter Master";
                    else if(adv==2)cout<<"Ethereal";
                    else if(adv==3)cout<<"Ork Mek";
                    else if(adv==4)cout<<"Eldar Farseer";
                    else if(adv==5)cout<<"Necron Cryptek";
                    else cout<<"None";
                    cout<<"\nAdvisors can protect you from certain negative events.\n";
                } else if(menuChoice==5){
                    cout<<"Press Enter to spin the movement.\n";
                    cin.ignore();
                    cin.get();
                    int moveDistance=rand()%6+1;
                    cout<<"You move "<<moveDistance<<" steps.\n";
                    bool reachedEnd=gameBoard.movePlayer(currentPlayerIndex,moveDistance);
                    cout<<"You are now at tile position "<<gameBoard.getPlayerPosition(currentPlayerIndex)<<".\n";
                    gameBoard.displayBoard();
                    endTurn=true;

                    Tile currentTile=gameBoard.getTileAtPlayerPosition(currentPlayerIndex);
                    int tileType=currentTile.getType();
                    Player updatedPlayer = players[currentPlayerIndex];
                    bool canChangeAdvisor=(players[currentPlayerIndex].getPathType()==1);

                    if(tileType==REGULAR_TILE){
                        updatedPlayer=Tile::handleRegularTile(updatedPlayer,events,eventCount);
                    } else if(tileType==OASIS_TILE){
                        Tile::OasisResult res=Tile::handleOasisTile(updatedPlayer);
                        updatedPlayer=res.player;
                        endTurn=res.endTurn;
                    } else if(tileType==COUNSELING_TILE){
                        updatedPlayer=Tile::handleCounselingTile(updatedPlayer,canChangeAdvisor);
                    } else if(tileType==GRAVEYARD_TILE){
                        updatedPlayer=Tile::handleGraveyardTile(updatedPlayer);
                        gameBoard.movePlayer(currentPlayerIndex,-10);
                    } else if(tileType==HYENAS_TILE){
                        int lastMove=gameBoard.getLastMove(currentPlayerIndex);
                        updatedPlayer=Tile::handleHyenasTile(updatedPlayer,lastMove);
                        gameBoard.movePlayer(currentPlayerIndex,-lastMove);
                    } else if(tileType==CHALLENGE_TILE){
                        updatedPlayer=Tile::handleChallengeTile(updatedPlayer,riddles,riddleCount);
                    } else if(tileType==SHOP_TILE){
                        updatedPlayer=Tile::handleShopTile(updatedPlayer);
                    } else if(tileType==FIGHT_TILE){
                        updatedPlayer=Tile::handleFightTile(players,numPlayers,currentPlayerIndex,updatedPlayer);
                    } else if(tileType==CASINO_TILE){
                        updatedPlayer=Tile::handleCasinoTile(updatedPlayer);
                    } else if(tileType==END_TILE){
                        cout<<"You have reached the end tile!\n";
                        gameOver=true;
                    } else if(tileType==START_TILE){
                        cout<<"You are on the Start Tile.\n";
                    }

                    players[currentPlayerIndex]=updatedPlayer;
                    if(!gameOver && tileType!=END_TILE){
                        // Prepare arrays to determine same-tile battles
                        int positions[MAX_PLAYERS]; 
                        int paths[MAX_PLAYERS]; 
                        gameBoard.getAllPlayerPositions(numPlayers, positions);
                        gameBoard.getAllPlayerPaths(numPlayers, paths);

                        int pos=gameBoard.getPlayerPosition(currentPlayerIndex);
                        int path=gameBoard.getPlayerPath(currentPlayerIndex);
                        Player afterBattle=Tile::handleSameTileBattle(players,numPlayers,currentPlayerIndex,pos,path,positions,paths);
                        players[currentPlayerIndex]=afterBattle;
                    }

                    if(reachedEnd) gameOver=true;
                } else {
                    cout<<"Invalid choice.\n";
                }
            }
            if(gameOver) break;
        }
    }

    cout<<"\n----------------------------------\nGame Over!\n";
    for(int i=0;i<numPlayers;i++){
        players[i].convertTraitsToHonor();
    }

    int sortedPlayerOrder[MAX_PLAYERS];
    for(int i=0;i<numPlayers;i++) sortedPlayerOrder[i]=i;
    for(int i=0;i<numPlayers-1;i++){
        int maxIndex=i;
        for(int j=i+1;j<numPlayers;j++){
            if(players[sortedPlayerOrder[j]].getHonor()>players[sortedPlayerOrder[maxIndex]].getHonor()){
                maxIndex=j;
            }
        }
        int temp=sortedPlayerOrder[i];
        sortedPlayerOrder[i]=sortedPlayerOrder[maxIndex];
        sortedPlayerOrder[maxIndex]=temp;
    }

    cout<<"\n============== FINAL LEADERBOARD ==============\n";
    for(int i=0;i<numPlayers;i++){
        int playerPos=sortedPlayerOrder[i];
        cout<<i+1<<". "<<players[playerPos].getName()<<" - Honor: "<<players[playerPos].getHonor()<<endl;
    }
    cout<<"Winner: "<<players[sortedPlayerOrder[0]].getName()<<"!\n";

    ofstream out("game_results.txt");
    if(out.is_open()){
        out<<"Game Results:\n";
        for(int i=0;i<numPlayers;i++){
            int playerPos=sortedPlayerOrder[i];
            out<<i+1<<". "<<players[playerPos].getName()<<" - Honor: "<<players[playerPos].getHonor()<<"\n";
        }
        out.close();
        cout<<"Game results saved to game_results.txt\n";
    } else {
        cout<<"Could not save results.\n";
    }

    cout<<"Thank you for playing!\n";

    return 0;
}
