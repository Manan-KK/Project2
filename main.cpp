#include <iostream>
#include "Board.cpp"
using namespace std;

int main(){
    Board b;
    b.initializeBoard();
    b.displayBoard();
    b.movePlayer(0);
    return 0;

}