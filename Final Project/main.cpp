#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Tile.h"

using namespace std;

struct LoadResult {
    int count;
    bool success;
};
 

// Loading Individual Terms so can be displayed later
LoadResult loadCharacters(string names[], int ages[], int mights[], int ends[], int cunnings[]) {
    LoadResult result;
    result.count = 0;
    result.success = false;

    string filename = "characters.txt"; 
    ifstream file(filename.c_str());
    if(!file.is_open()) {
        cout << "[ERROR] Could not open characters.txt for reading characters.\n";
        return result;
    }

    cout << "[INFO] Loading characters from characters.txt\n";
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

        if(tokenCount==5) {
            names[result.count] = tokens[0];
            ages[result.count] = stoi(tokens[1]);
            mights[result.count] = stoi(tokens[2]);
            ends[result.count] = stoi(tokens[3]);
            cunnings[result.count] = stoi(tokens[4]);
            result.count++;
            if(result.count>=20) break;
        }
    }
    file.close();

    result.success = true;
    cout << "[INFO] Successfully loaded " << result.count << " characters.\n";
    return result;
}

LoadResult loadRandomEvents(RandomEvent events[]) {
    LoadResult result;
    result.count=0;
    result.success=false;

    string filename = "random_events.txt"; 
    ifstream file(filename.c_str());
    if(!file.is_open()) {
        cout << "[ERROR] Could not open random_events.txt for reading random events.\n";
        return result;
    }

    cout << "[INFO] Loading random events from random_events.txt\n";
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
            events[result.count].description=tokens[0];
            events[result.count].pathType=stoi(tokens[1]);
            events[result.count].advisor=stoi(tokens[2]);
            events[result.count].honorChange=stoi(tokens[3]);
            result.count++;
            if(result.count>=100) break;
        }
    }
    file.close();
    result.success = true;
    cout << "[INFO] Successfully loaded " << result.count << " random events.\n";
    return result;
}

LoadResult loadRiddles(Riddle riddles[]) {
    LoadResult result;
    result.count=0;
    result.success=false;

    string filename = "riddles.txt"; 
    ifstream file(filename.c_str());
    if(!file.is_open()) {
        cout << "[ERROR] Could not open riddles.txt for reading riddles.\n";
        return result;
    }

    cout << "[INFO] Loading riddles from riddles.txt\n";
    while(true){
        string questionLine, answerLine;
        if(!getline(file,questionLine)) break;
        if(!getline(file,answerLine)) break;
        if(questionLine=="" || answerLine=="") break;
        riddles[result.count].question=questionLine;
        riddles[result.count].answer=answerLine;
        result.count++;
        if(result.count>=50) break;
    }
    file.close();
    result.success = true;
    cout << "[INFO] Successfully loaded " << result.count << " riddles.\n";
    return result;
}

int main() {
    srand((unsigned)time(0));
    const int MAX_PLAYERS=4;
    int numPlayers;
    cout << "====================================\n"
         << "  Welcome to the Warhammer 40K Trial!\n"
         << "====================================\n"
         << "Enter number of players (1-4): ";
    cin >> numPlayers;
    while(numPlayers<1||numPlayers>4){
        cout << "Invalid number. Enter 1-4: ";
        cin >> numPlayers;
    }

    Board gameBoard(numPlayers);
    Player players[MAX_PLAYERS];

    // Load characters
    string cNames[20]; 
    int cAges[20], cMight[20], cEnd[20], cCunn[20];
    for(int i=0;i<20;i++) cNames[i]="";

    LoadResult charRes = loadCharacters(cNames, cAges, cMight, cEnd, cCunn);
    if(!charRes.success || charRes.count==0) {
        cout << "[ERROR] No characters loaded from characters.txt. Cannot start the game.\n";
        return 1; // Exit if no characters available
    }

    // Track chosen characters
    bool chosenChars[20];
    for(int i=0;i<charRes.count;i++) chosenChars[i]=false;

    // Track advisor availability:
    // 1=Chapter Master,2=Ethereal,3=Ork Mek,4=Eldar Farseer,5=Necron Cryptek,0=None
    bool advisorTaken[6];
    for (int i=0; i<=5; i++) advisorTaken[i]=false;

    // Character Selection & Path for each player
    for(int playerIndex=0; playerIndex<numPlayers; playerIndex++){
        cout << "\nPlayer " << playerIndex+1 << ", enter your player name: ";
        string pName; cin >> pName;

        cout << "\nAvailable Characters:\n";
        cout << "--------------------------------------------------------\n";
        cout << " # | Name      | Age | Might | Endurance | Cunning\n";
        cout << "--------------------------------------------------------\n";
        for(int c=0;c<charRes.count;c++){
            if(!chosenChars[c]) {
                cout << (c+1) << " | " << cNames[c]
                     << " | " << cAges[c]
                     << " | " << cMight[c]
                     << " | " << cEnd[c]
                     << " | " << cCunn[c] << "\n";
            }
        }
        cout << "--------------------------------------------------------\n";
        cout << "Choose a character by number: ";
        int characterChoice; cin >> characterChoice;
        characterChoice--;
        while(characterChoice<0||characterChoice>=charRes.count||chosenChars[characterChoice]){
            cout << "Invalid. Choose again: ";
            cin >> characterChoice; characterChoice--;
        }
        chosenChars[characterChoice]=true;

        Player p(cNames[characterChoice], cAges[characterChoice], cMight[characterChoice],
                 cEnd[characterChoice], cCunn[characterChoice], 20000);

        cout << "\nChoose your path:\n"
             << "1. Chapter Training Grounds (-5000 Honor, +500 Might, +500 Endurance, +1000 Cunning)\n"
             << "2. Frontline Deployment (+5000 Honor, +200 all traits)\n"
             << "Your choice: ";
        int pathChoice; cin >> pathChoice;
        while(pathChoice!=1&&pathChoice!=2){
            cout << "Invalid.\n";
            cin >> pathChoice;
        }
        if(pathChoice==1){
            p.decHonor(5000);
            p.incMight(500);
            p.incEndurance(500);
            p.incCunning(1000);
            p.setPathType(0);
            cout << "Initial advisor selection:\n"
                 << "1. Chapter Master\n2. Ethereal\n3. Ork Mek\n4. Eldar Farseer\n5. Necron Cryptek\n0. None\nChoice: ";
            int advChoice; cin >> advChoice;
            while(advChoice<0||advChoice>5||(advChoice!=0 && advisorTaken[advChoice])){
                cout << "Invalid or Advisor taken. Choose again: ";
                cin >> advChoice;
            }
            if(advChoice!=0) advisorTaken[advChoice]=true;
            p.setAdvisor(advChoice);
        } else {
            p.incHonor(5000);
            p.incMight(200);
            p.incEndurance(200);
            p.incCunning(200);
            p.setPathType(1);
        }

        gameBoard.setPlayerPath(playerIndex,p.getPathType());
        p.setName(pName);
        cout << pName << " has chosen!\n";
        players[playerIndex]=p;
    }

    RandomEvent events[100];
    LoadResult eventRes = loadRandomEvents(events);

    Riddle riddles[50];
    LoadResult riddleRes = loadRiddles(riddles);

    bool gameOver=false;

    // Main Game Loop
    while(!gameOver){
        for(int currentPlayerIndex=0; currentPlayerIndex<numPlayers; currentPlayerIndex++){
            // Check if end reached
            for(int p=0;p<numPlayers;p++){
                if(gameBoard.getPlayerPosition(p)>=51){
                    gameOver=true;
                    break;
                }
            }
            if(gameOver) break;

            cout << "\n----------------------------------\n";
            cout << players[currentPlayerIndex].getName() << "'s turn.\n";
            if(!gameOver) {
                gameBoard.displayBoard();
            }

            bool endTurn=false;
            while(!endTurn && !gameOver){
                cout << "\n[MAIN MENU]\n"
                     << "1. Check Player Progress\n"
                     << "2. Review Character\n"
                     << "3. Check Position\n"
                     << "4. Review Advisor\n"
                     << "5. Move Forward\n"
                     << "Choose an option: ";
                int menuChoice; cin>>menuChoice;
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
                    if(!gameOver) gameBoard.displayBoard();
                } else if(menuChoice==4){
                    cout<<"Current Advisor: ";
                    int adv=players[currentPlayerIndex].getAdvisor();
                    switch(adv){
                        case 1:cout<<"Chapter Master";break;
                        case 2:cout<<"Ethereal";break;
                        case 3:cout<<"Ork Mek";break;
                        case 4:cout<<"Eldar Farseer";break;
                        case 5:cout<<"Necron Cryptek";break;
                        default:cout<<"None";break;
                    }
                    cout<<"\n";

                    // Switching advisors (if desired) would occur on a special tile, not here
                    // unless you add the logic similar to initial selection,
                    // checking advisorTaken[] and releasing/taking advisors as needed.
                } else if(menuChoice==5){
                    cout<<"Press Enter to spin...\n";
                    cin.ignore();
                    cin.get();
                    int moveDistance=rand()%6+1;
                    cout<<"You move "<<moveDistance<<" steps.\n";
                    bool reachedEnd=gameBoard.movePlayer(currentPlayerIndex,moveDistance);
                    cout<<"Position: "<<gameBoard.getPlayerPosition(currentPlayerIndex)<<".\n";
                    if(!gameOver) gameBoard.displayBoard();
                    endTurn=true;

                    Tile currentTile=gameBoard.getTileAtPlayerPosition(currentPlayerIndex);
                    int tileType=currentTile.getType();
                    Player updatedPlayer = players[currentPlayerIndex];
                    bool canChangeAdvisor=(players[currentPlayerIndex].getPathType()==1);

                    // Handle tile events
                    if(tileType==REGULAR_TILE){
                        updatedPlayer=Tile::handleRegularTile(updatedPlayer, events, eventRes.count);
                    } else if(tileType==OASIS_TILE){
                        Tile::OasisResult res=Tile::handleOasisTile(updatedPlayer);
                        updatedPlayer=res.player;
                        endTurn=res.endTurn; 
                    } else if(tileType==COUNSELING_TILE){
                        updatedPlayer=Tile::handleCounselingTile(updatedPlayer,canChangeAdvisor);
                        // If advisor switching allowed here, apply logic:
                        // int oldAdv = updatedPlayer.getAdvisor();
                        // cout << "Switch Advisor? Same logic as initial pick, check advisorTaken[].\n";
                        // int newAdv; // pick new advisor
                        // if(oldAdv!=0 && oldAdv!=newAdv) advisorTaken[oldAdv]=false;
                        // if(newAdv!=0) advisorTaken[newAdv]=true;
                        // updatedPlayer.setAdvisor(newAdv);

                    } else if(tileType==GRAVEYARD_TILE){
                        updatedPlayer=Tile::handleGraveyardTile(updatedPlayer);
                        gameBoard.movePlayer(currentPlayerIndex,-10);
                    } else if(tileType==HYENAS_TILE){
                        int lastMove=gameBoard.getLastMove(currentPlayerIndex);
                        updatedPlayer=Tile::handleHyenasTile(updatedPlayer,lastMove);
                        gameBoard.movePlayer(currentPlayerIndex,-lastMove);
                    } else if(tileType==CHALLENGE_TILE){
                        updatedPlayer=Tile::handleChallengeTile(updatedPlayer,riddles,riddleRes.count);
                    } else if(tileType==SHOP_TILE){
                        updatedPlayer=Tile::handleShopTile(updatedPlayer);
                    } else if(tileType==CASINO_TILE){
                        updatedPlayer=Tile::handleCasinoTile(updatedPlayer);
                    } else if(tileType==END_TILE){
                        cout<<"You reached the final tile! The trial ends.\n";
                        gameOver=true;
                    } else if(tileType==START_TILE){
                        cout<<"At the Start Tile.\n";
                    }

                    players[currentPlayerIndex]=updatedPlayer;

                    if(!gameOver && tileType!=END_TILE){
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

    // Determine winner
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
    cout << "Press Enter to Close this app\n";
    cin.ignore();
    cin.get();
    return 0;

}
