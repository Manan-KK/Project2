#include <iostream>
#include <cstdlib> 
#include <ctime>

struct Tile{
    char color;
};

class StartTile{
    private:
        int position = 0;
    public:
    StartTile(){
        position = 0;
    }

};
class EndTile{
    private:
        int position = 52;
    public:
        EndTile(){
            position = 52;
        }

};
//a tile that the player can land on and "pull" a "card" that will either help or hurt them
class ChanceTile{
    private:
        int num; //number that will dictate what "card" the player will pull
    public:
        ChanceTile(){
            srand(time(0));
            num = rand() % 6 + 1; //Generates number between 1 and 6
            switch(num){
                case(1):
                case(2):
                case(3):
                case(4):
                case(5):
                case(6):
            }
        }
};
//a tile that the player can choose how many 
//points they wish to put on the line in order to earn or lose points*/

class GambleTile{
    private:
        int points;
    public:
        GambleTile(){
            points = 0;
        }
        int gamble(int p){
            //conditional to check whether p is a non-negative and less than the players max points
            int 
            srand(time(0));
            int random = rand() % 5 + 1; //generates number between 1 and 5
            switch(random){
                case(1): //Lose 50% of their points gambled
                case(2): //Lose 25% of their points gambled
                case(3): //Player doesn't lose anything
                case(4): //Gains 25% of their points gambled
                case(5): //Gains 50% of their points gambled
            }
        }


};
class FightTile(){
    private:
    public:
        FightTile(){}
        void fight(){
            //the player can choose whether they want to fight the other player
            //the stats of either player will decide who wins
            //points are taken from loser and given to winner - amount of points will be decided
        }
};
//this tile randomly pushes the character either 1-3 spots behind or 1-3 spots in front
//these tiles will not be near the start or end tiles
class RandomTile(){
    private:
    public:
        RandomTile(){
            srand(time(0));
            int num = rand() % 6 + 1;
            switch(num){
                case(1)://pushes back 3
                case(2)://pushes back 2
                case(3)://pushes back 1
                case(4)://pushes forward 1
                case(5)://pushes forward 2
                case(6)://pushes forward 3
            }
        }
};
//this tile gives the player a chance to trade in points for other attribute points
//may also give chances for the player to buy special items (possible inventory implementation)
class ShopTile(){
    private:
    public:
        ShopTile(){
            //gives the player a list of what they can buy
        }
};
class BattleTile(){
    private:
    public:
        BattleTile(){
            //gives the player a chance to battle the other player if they choose for a chance to win rewards
            //will further add more attributes to the class for specifics
        }
}
