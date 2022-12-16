#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "dice.h"
#include "randgen.h"
using namespace std;

int main() {
    RandGen gen;
    Dice revolver;
    int unlucky= gen.RandInt(1, revolver.NumSides());
    int score;
    score=0;
    int playerturn=1;
    
    while (score != unlucky){
        if (playerturn==1){
            score=revolver.Roll();
            cout<<"Player 1 pulls "<<score<<endl;
            playerturn=2;
        }
        else if (playerturn==2){
            score=revolver.Roll();
            cout<<"Player 2 pulls "<<score<<endl;
            playerturn=1;
        }
    }
    if (playerturn==1){
        cout<<"Player 1 pulls "<<score<<endl;
        cout<<"Player 1 dies!"<<endl;
        cout<<"Player 2 survived after "<<revolver.NumRolls()<<endl;
    }
    else if(playerturn==2){
        cout<<"Player 2 pulls "<<score<<endl;
        cout<<"Player 2 dies!"<<endl;
        cout<<"Player 1 survived after "<<revolver.NumRolls()<<" turns"<<endl;
    }
    
    
    return 0;
}
