#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Board.h"
#include "Player.h"

using namespace std;

// Structs for events and riddles
struct RandomEvent {
    string description;
    int pathType; //0,1,2
    int advisor;  //0-5
    int honorChange;
};

struct Riddle {
    string question;
    string answer;
};

// Load functions directly here (no separate class)
void loadCharacters(string filename, string names[], int ages[], int mights[], int ends[], int cunnings[], int &count) {
    ifstream file(filename.c_str());
    count=0;
    if(!file.is_open()) return;
    string line;
    while(getline(file,line)) {
        if(line.empty()) continue;
        string tokens[5];
        int idx=0;
        size_t pos=0;
        while((pos=line.find('|'))!=string::npos && idx<4) {
            tokens[idx]=line.substr(0,pos);
            line.erase(0,pos+1);
            idx++;
        }
        tokens[idx]=line;
        if(idx==4){
            names[count]=tokens[0];
            ages[count]=atoi(tokens[1].c_str());
            mights[count]=atoi(tokens[2].c_str());
            ends[count]=atoi(tokens[3].c_str());
            cunnings[count]=atoi(tokens[4].c_str());
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
        if(line.empty()) continue;
        string tokens[4];
        int idx=0;
        size_t pos=0;
        while((pos=line.find('|'))!=string::npos && idx<3){
            tokens[idx]=line.substr(0,pos);
            line.erase(0,pos+1);
            idx++;
        }
        tokens[idx]=line;
        if(idx==3){
            events[count].description=tokens[0];
            events[count].pathType=atoi(tokens[1].c_str());
            events[count].advisor=atoi(tokens[2].c_str());
            events[count].honorChange=atoi(tokens[3].c_str());
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
    string q,a;
    while(true){
        if(!getline(file,q)) break;
        if(!getline(file,a)) break;
        riddles[count].question=q;
        riddles[count].answer=a;
        count++;
        if(count>=50) break;
    }
    file.close();
}

bool askRiddle(Player &player, const Riddle riddles[], int rCount){
    if(rCount==0) return false;
    int r=rand()%rCount;
    cout<<"Puzzle: "<<riddles[r].question<<endl;
    cout<<"Answer: ";
    string ans;cin>>ans;
    if(ans==riddles[r].answer){
        cout<<"Correct!"<<endl;
        return true;
    } else {
        cout<<"Incorrect. The answer was "<<riddles[r].answer<<endl;
        return false;
    }
}

int advisorMenuChoice() {
    cout<<"Advisors:\n1.Chapter Master\n2.Ethereal\n3.Ork Mek\n4.Eldar Farseer\n5.Necron Cryptek\n0.None\nChoice: ";
    int c;cin>>c;
    if(c<0||c>5) c=0;
    return c;
}

// Regular tile event
void handleRegularTile(Player &player,const RandomEvent events[],int eCount){
    cout<<"Regular Tile encountered."<<endl;
    int chance=rand()%2;
    if(chance==0){
        cout<<"No event triggered."<<endl;
        return;
    }
    // Attempt to find suitable event
    for(int tries=0; tries<10; tries++){
        int idx=rand()%eCount;
        int pt=events[idx].pathType;
        if(pt==2||pt==player.getPathType()){
            int advNeeded=events[idx].advisor;
            int change=events[idx].honorChange;
            // Negative event
            if(change<0){
                if(advNeeded!=0 && player.getAdvisor()==advNeeded){
                    cout<<"Event: "<<events[idx].description<<". Your advisor protected you!"<<endl;
                    return;
                } else {
                    cout<<"Event: "<<events[idx].description<<endl;
                    cout<<"You lose "<<(-change)<<" Honor."<<endl;
                    player.decHonor(-change);
                    return;
                }
            } else {
                // positive event
                cout<<"Event: "<<events[idx].description<<endl;
                cout<<"You gain "<<change<<" Honor."<<endl;
                player.incHonor(change);
                return;
            }
        }
    }
    cout<<"No suitable event."<<endl;
}

void handleOasisTile(Player &player,bool &endTurn){
    cout<<"Oasis(Healing Shrine): +200 all traits, extra turn."<<endl;
    player.incMight(200);
    player.incEndurance(200);
    player.incCunning(200);
    endTurn=false;
}

void handleCounselingTile(Player &player,bool canChangeAdvisor){
    cout<<"Counseling Tile(Strategic Council): +300 all traits."<<endl;
    player.incMight(300);
    player.incEndurance(300);
    player.incCunning(300);
    if(canChangeAdvisor){
        cout<<"Change advisor?\n";
        int adv=advisorMenuChoice();
        if(adv!=0){
            player.setAdvisor(adv);
            cout<<"Advisor set."<<endl;
        } else cout<<"No advisor change."<<endl;
    }
}

void handleGraveyardTile(Player &player,Board &board,int currentPlayerIndex){
    cout<<"Graveyard(Cursed Battlefield): Move back 10, -100 all traits."<<endl;
    board.movePlayer(currentPlayerIndex,-10);
    player.decMight(100);
    player.decEndurance(100);
    player.decCunning(100);
}

void handleHyenasTile(Player &player,Board &board,int currentPlayerIndex){
    cout<<"Hyenas(Genestealers): Return to previous position, -300 Endurance."<<endl;
    int last=board.getLastMove(currentPlayerIndex);
    board.movePlayer(currentPlayerIndex,-last);
    player.decEndurance(300);
}

void handleChallengeTile(Player &player,const Riddle riddles[],int rCount){
    cout<<"Challenge(Black Library Puzzle): Answer riddle to gain 500 Cunning."<<endl;
    if(askRiddle(player,riddles,rCount)){
        player.incCunning(500);
    }
}

void handleShopTile(Player &player){
    cout<<"Shop(Forge Temple): Trade Honor for trait boosts.\n";
    bool shopping=true;
    while(shopping){
        cout<<"1.+100 Might(500 Honor)\n2.+100 Endurance(500)\n3.+100 Cunning(500)\n4.Exit\nChoice:";
        int ch;cin>>ch;
        if(ch==4) {shopping=false;break;}
        if(player.getHonor()<500){cout<<"Not enough Honor.\n";continue;}
        if(ch==1){player.decHonor(500);player.incMight(100);cout<<"Might+100\n";}
        else if(ch==2){player.decHonor(500);player.incEndurance(100);cout<<"Endurance+100\n";}
        else if(ch==3){player.decHonor(500);player.incCunning(100);cout<<"Cunning+100\n";}
        else cout<<"Invalid.\n";
    }
}

void handleFightTile(Player players[],int playerCount,int currentPlayerIndex,Player &currentPlayer){
    cout<<"Fight(Dueling Grounds): Challenge another player?\n1.Yes\n2.No\n";
    int ch;cin>>ch;
    if(ch==1){
        cout<<"Choose player:\n";
        for(int i=0;i<playerCount;i++){
            if(i!=currentPlayerIndex) cout<<i+1<<"."<<players[i].getName()<<endl;
        }
        int opp;cin>>opp;opp--;
        if(opp<0||opp>=playerCount||opp==currentPlayerIndex){cout<<"Invalid.\n";return;}
        Player &opponent=players[opp];
        int curPow=currentPlayer.getMight()+currentPlayer.getEndurance();
        int oppPow=opponent.getMight()+opponent.getEndurance();
        if(curPow>oppPow){
            cout<<"You win! +1000 Honor.\n";
            currentPlayer.incHonor(1000);
            opponent.decHonor(1000);
        } else if(curPow<oppPow){
            cout<<"You lose! -1000 Honor.\n";
            currentPlayer.decHonor(1000);
            opponent.incHonor(1000);
        } else cout<<"Tie.\n";
    }
    else cout<<"No fight.\n";
}

void handleCasinoTile(Player &player){
    cout<<"Casino(Roulette of Fate): Gamble 0-1000 Honor.\n";
    int amt;cin>>amt;
    if(amt<0)amt=0;if(amt>1000)amt=1000;
    if(amt>player.getHonor()) amt=player.getHonor();
    int out=rand()%6+1;
    if(out<=2){
        cout<<"Lose "<<amt<<" Honor.\n";
        player.decHonor(amt);
    } else if(out<=4){
        cout<<"Win "<<amt<<" Honor.\n";
        player.incHonor(amt);
    } else {
        cout<<"Jackpot! Win "<<amt*2<<" Honor.\n";
        player.incHonor(amt*2);
    }
}

// After player moves and triggers tile event, check if multiple players share tile.
// If so, they battle. We'll prompt the current player to choose who to fight if multiple present.
void handleSameTileBattle(Player players[],int playerCount,int currentPlayerIndex,const Board &board){
    int pos=board.getPlayerPosition(currentPlayerIndex);
    int path=board.getPlayerPath(currentPlayerIndex);
    // Find all players on same tile/path
    int same[4];int count=0;
    for(int i=0;i<playerCount;i++){
        if(i!=currentPlayerIndex && board.getPlayerPosition(i)==pos && board.getPlayerPath(i)==path){
            same[count]=i;count++;
        }
    }
    if(count==0) return; // no battle

    cout<<"Multiple players on the same tile! Time to battle!\n";
    // If more than one opponent, choose
    if(count>1) {
        cout<<"Choose opponent:\n";
        for(int i=0;i<count;i++){
            cout<<i+1<<"."<<players[same[i]].getName()<<endl;
        }
        int ch;cin>>ch;ch--;
        if(ch<0||ch>=count) ch=0;
        int oppi=same[ch];
        // simple fight logic
        Player &current=players[currentPlayerIndex];
        Player &opp=players[oppi];
        int curPow=current.getMight()+current.getEndurance();
        int oppPow=opp.getMight()+opp.getEndurance();
        if(curPow>oppPow){
            cout<<"You defeat "<<opp.getName()<<"! +500 Honor.\n";
            current.incHonor(500);
            opp.decHonor(500);
        } else if(curPow<oppPow){
            cout<<opp.getName()<<" defeats you! -500 Honor to you.\n";
            current.decHonor(500);
            opp.incHonor(500);
        } else {
            cout<<"Tie in battle.\n";
        }
    } else {
        // only one opponent
        int oppi=same[0];
        Player &current=players[currentPlayerIndex];
        Player &opp=players[oppi];
        int curPow=current.getMight()+current.getEndurance();
        int oppPow=opp.getMight()+opp.getEndurance();
        if(curPow>oppPow){
            cout<<"You defeat "<<opp.getName()<<"! +500 Honor.\n";
            current.incHonor(500);
            opp.decHonor(500);
        } else if(curPow<oppPow){
            cout<<opp.getName()<<" defeats you! -500 Honor.\n";
            current.decHonor(500);
            opp.incHonor(500);
        } else {
            cout<<"Tie in battle.\n";
        }
    }
}

int main(){
    srand(time(0));
    const int MAX_PLAYERS=4;
    int numPlayers;
    cout<<"Welcome to the Warhammer 40K Honor Trial Game!\n";
    cout<<"Enter number of players (1-4): ";
    cin>>numPlayers;
    while(numPlayers<1||numPlayers>MAX_PLAYERS){
        cout<<"Invalid. Enter 1-4: ";
        cin>>numPlayers;
    }

    Board gameBoard(numPlayers);
    Player players[MAX_PLAYERS];

    // Load characters
    string cNames[20];int cAges[20];int cMight[20];int cEnd[20];int cCunn[20];int cCount=0;
    loadCharacters("characters.txt",cNames,cAges,cMight,cEnd,cCunn,cCount);
    bool chosen[20];for(int i=0;i<20;i++) chosen[i]=false;

    for(int i=0;i<numPlayers;i++){
        cout<<"Player "<<i+1<<", enter your name: ";
        string pName;cin>>pName;

        cout<<"Available characters:\n";
        for(int j=0;j<cCount;j++){
            if(!chosen[j]) cout<<j+1<<"."<<cNames[j]<<endl;
        }
        int choice;cin>>choice;choice--;
        while(choice<0||choice>=cCount||chosen[choice]){
            cout<<"Invalid. choose again: ";
            cin>>choice;choice--;
        }
        chosen[choice]=true;
        Player p(cNames[choice],cAges[choice],cMight[choice],cEnd[choice],cCunn[choice],20000);

        cout<<"Choose your path:\n1.Chapter Training Grounds(-5000Honor,+500M/+500E/+1000C)\n2.Frontline(+5000Honor,+200all)\n";
        int pathC;cin>>pathC;
        while(pathC!=1&&pathC!=2){cout<<"Invalid.\n";cin>>pathC;}
        if(pathC==1){
            p.decHonor(5000);
            p.incMight(500);
            p.incEndurance(500);
            p.incCunning(1000);
            p.setPathType(0);
            cout<<"Choose initial advisor:\n";
            int adv=advisorMenuChoice();
            if(adv!=0)p.setAdvisor(adv);
        } else {
            p.incHonor(5000);
            p.incMight(200);
            p.incEndurance(200);
            p.incCunning(200);
            p.setPathType(1);
        }
        gameBoard.setPlayerPath(i,p.getPathType());
        players[i]=p;
        cout<<pName<<" chosen "<<p.getName()<<"!\n";
    }

    RandomEvent events[100];int eCount=0;
    loadRandomEvents("random_events.txt",events,eCount);

    Riddle riddles[50];int rCount=0;
    loadRiddles("riddles.txt",riddles,rCount);

    bool gameOver=false;

    while(!gameOver){
        for(int i=0;i<numPlayers;i++){
            // Check end condition: any player at end tile?
            for(int pp=0;pp<numPlayers;pp++){
                if(gameBoard.getPlayerPosition(pp)>=51){
                    gameOver=true;
                    break;
                }
            }
            if(gameOver) break;

            cout<<"----------------------------------\n";
            cout<<players[i].getName()<<"'s turn.\n";
            gameBoard.displayBoard();
            bool endTurn=false;
            while(!endTurn){
                cout<<"Main Menu:\n1.Check Progress\n2.Review Character\n3.Check Position\n4.Review Advisor\n5.Move Forward\nChoice:";
                int mc;cin>>mc;
                switch(mc){
                    case 1:{
                        players[i].displayStats();
                        cout<<"1.Convert Traits to Honor\n2.Back\n";
                        int sub;cin>>sub;
                        if(sub==1){
                            players[i].convertTraitsToHonor();
                            cout<<"Converted.\n";
                        }
                        break;}
                    case 2:
                        cout<<"Character: "<<players[i].getName()<<", Age:"<<players[i].getAge()<<endl;
                        break;
                    case 3:
                        cout<<"Position: "<<gameBoard.getPlayerPosition(i)<<endl;
                        gameBoard.displayBoard();
                        break;
                    case 4:{
                        cout<<"Advisor: ";
                        int adv=players[i].getAdvisor();
                        switch(adv){
                            case 1:cout<<"Chapter Master";break;
                            case 2:cout<<"Ethereal";break;
                            case 3:cout<<"Ork Mek";break;
                            case 4:cout<<"Eldar Farseer";break;
                            case 5:cout<<"Necron Cryptek";break;
                            default:cout<<"None";break;
                        }
                        cout<<"\nAdvisors protect from certain negative events.\n";
                        break;}
                    case 5:{
                        cout<<"Press Enter to spin.";
                        cin.ignore();
                        cin.get();
                        int move=rand()%6+1;
                        cout<<"Move "<<move<<" steps.\n";
                        bool reachedEnd=gameBoard.movePlayer(i,move);
                        cout<<"Now at "<<gameBoard.getPlayerPosition(i)<<"\n";
                        gameBoard.displayBoard();
                        endTurn=true;
                        // Trigger tile effect
                        Tile currentTile=gameBoard.getTileAtPlayerPosition(i);
                        int type=currentTile.getType();
                        switch(type){
                            case REGULAR_TILE:
                                handleRegularTile(players[i],events,eCount);
                                break;
                            case OASIS_TILE:
                                handleOasisTile(players[i],endTurn);
                                break;
                            case COUNSELING_TILE:
                                handleCounselingTile(players[i],true);
                                break;
                            case GRAVEYARD_TILE:
                                handleGraveyardTile(players[i],gameBoard,i);
                                break;
                            case HYENAS_TILE:
                                handleHyenasTile(players[i],gameBoard,i);
                                break;
                            case CHALLENGE_TILE:
                                handleChallengeTile(players[i],riddles,rCount);
                                break;
                            case SHOP_TILE:
                                handleShopTile(players[i]);
                                break;
                            case FIGHT_TILE:
                                handleFightTile(players,numPlayers,i,players[i]);
                                break;
                            case CASINO_TILE:
                                handleCasinoTile(players[i]);
                                break;
                            case END_TILE:
                                cout<<"Reached end!\n";
                                gameOver=true;
                                break;
                            case START_TILE:
                                cout<<"Start Tile.\n";
                                break;
                            default:
                                cout<<"Unknown tile.\n";
                        }
                        // After tile effect, if game not over, handle same-tile battle
                        if(!gameOver) handleSameTileBattle(players,numPlayers,i,gameBoard);
                        if(reachedEnd) gameOver=true;
                        break;}
                    default:cout<<"Invalid.\n";break;
                }
                if(gameOver) break;
            }
            if(gameOver) break;
        }
    }

    cout<<"----------------------------------\nGame Over!\n";
    // End game: convert traits again
    for(int i=0;i<numPlayers;i++){
        players[i].convertTraitsToHonor();
    }

    // Sort leaderboard
    int indices[MAX_PLAYERS];
    for(int i=0;i<numPlayers;i++) indices[i]=i;
    for(int i=0;i<numPlayers-1;i++){
        int maxIdx=i;
        for(int j=i+1;j<numPlayers;j++){
            if(players[indices[j]].getHonor()>players[indices[maxIdx]].getHonor()){
                maxIdx=j;
            }
        }
        int temp=indices[i];
        indices[i]=indices[maxIdx];
        indices[maxIdx]=temp;
    }

    cout<<"Leaderboard:\n";
    for(int i=0;i<numPlayers;i++){
        int idx=indices[i];
        cout<<i+1<<". "<<players[idx].getName()<<" - Honor: "<<players[idx].getHonor()<<endl;
    }
    cout<<"Winner: "<<players[indices[0]].getName()<<"!\n";

    ofstream out("game_results.txt");
    if(out.is_open()){
        out<<"Game Results:\n";
        for(int i=0;i<numPlayers;i++){
            int idx=indices[i];
            out<<i+1<<". "<<players[idx].getName()<<" - Honor: "<<players[idx].getHonor()<<"\n";
        }
        out.close();
        cout<<"Results saved.\n";
    } else {
        cout<<"Could not save results.\n";
    }

    return 0;
}
