#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> //check
using namespace std;

void printpuzzle(vector<vector<string>> resultMatrix){
    for(int x=0; x<resultMatrix.size();x++){
        for (int y=0; y<resultMatrix[0].size();y++){
            cout<<resultMatrix[x][y]<<"\t";
        }
        cout<<endl;
    }
}

vector<vector<string>> puzzle(int row, int column, int startingRow,int startingColumn,
            string puzzleWord, string direction, string orintation,
            vector<vector<string>> resultMatrix){
    
    vector<vector<string>> oldMatrix=resultMatrix; //If fails return old version
    
    int bb=row-1; //bottom border
    int rb=column-1; //right border
    
    int currentCol=startingColumn;
    int currentRow=startingRow;
    bool fail=false;
    
//    First character check
    
    if(resultMatrix[currentRow][currentCol]=="-"){
        resultMatrix[currentRow][currentCol]=puzzleWord[0];
    }
    else{
        fail=true;
    }
    
//    Loop for each character
    
    for(int a=1; a<puzzleWord.length(); a++){
        
        if (direction=="r"){
//            Right
            if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                currentCol++;
            }
            else if(orintation=="CW"){
//                Down
                if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
//                Left
                else if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
//                Up
                else if(currentRow!=0 &&resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
                else{
                    fail=true;
                }
            }
            else if(orintation=="CCW"){
//                Up
                if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
//                Left
                else if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
//                Down   checkkkkkkkkkk
                else if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
                else{
                    fail=true;
                }
            }
        }
        
        
        else if (direction=="l"){
//          Left
            if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                currentCol--;
            }
            else if(orintation=="CW"){
//              Up
                if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
//              Right
                else if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
//              Down
                else if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
                else{
                    fail=true;
                }
            }
            else if(orintation=="CCW"){
//              Down
                if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
//              Right
                else if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
//              Up
                else if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
                else{
                    fail=true;
                }
            }
        }

        
        else if (direction=="u"){
//          Up
            if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                currentRow--;
            }
            else if(orintation=="CW"){
//              Right
                if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
//              Down
                else if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
//              Left
                else if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
                else{
                    fail=true;
                }

            }
            else if(orintation=="CCW"){
                
//              Left
                if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
//              Down
                else if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                    currentRow++;
                }
//              Right
                else if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
                else{
                    fail=true;
                }
            }
        }

        
        else if (direction=="d"){
//          Down
            if(currentRow!=bb && resultMatrix[currentRow+1][currentCol]=="-"){
                currentRow++;
            }
            else if(orintation=="CW"){
                
//              Left
                if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
//              Up
                else if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
//              Right
                else if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
                else{
                    fail=true;
                }
            }
            else if(orintation=="CCW"){
//              Right
                if(currentCol!=rb && resultMatrix[currentRow][currentCol+1]=="-"){
                    currentCol++;
                }
//              Up
                else if(currentRow!=0 && resultMatrix[currentRow-1][currentCol]=="-"){
                    currentRow--;
                }
//              Left
                else if(currentCol!=0 && resultMatrix[currentRow][currentCol-1]=="-"){
                    currentCol--;
                }
                else{
                    fail=true;
                }
            }
        }
        resultMatrix[currentRow][currentCol]=puzzleWord[a]; //add letter to puzzle
    }
    
    
//    Print info before matrix
    if(fail){
        cout<<"\""<<puzzleWord<<"\""<<" could not be put into the matrix with given starting point: "<<startingRow<<","<<startingColumn<<"\t direction: "<<direction<<"\t orientation: "<<orintation<<endl;
        return oldMatrix;
    }else{
        cout<<"\""<<puzzleWord<<"\""<<" was put into the matrix with given starting point: "<<startingRow<<","<<startingColumn<<"\t direction: "<<direction<<"\t orientation: "<<orintation<<endl;
        return resultMatrix;
    }
    
}

int main() {
    string fileName, lineStr, word;
    ifstream input;
    
    cout << "Please enter the name of the file: ";
    cin >> fileName;
    input.open(fileName);

    while (input.fail()){
        cout << "File name is incorrect, please enter again: " ;
        cin >> fileName;
        input.open(fileName);
    }

//    READING FILE
   
//    get first line of the input
    getline(input,lineStr);
    istringstream lineStream(lineStr);
    int number, row, column;
    int wordCount=1;
    
    while(lineStream>>number){
        if (wordCount==1 && number>0){
            row=number;
            wordCount+=1;
        }
        else if (wordCount==2 && number>0){
            column=number;
            wordCount+=1;
        }
        else{
            cout<<endl<<"Invalid number for row and/or column!"<<endl;
            return 0;
        }
    }
    
//    Create matrix
    vector<vector<string>> resultMatrix(row, vector<string>(column));
    for(int x=0; x<resultMatrix.size();x++){
        for (int y=0; y<resultMatrix[0].size();y++){
            resultMatrix[x][y]="-";
        }
    }

//    Get puzzle word lines of the input
    while(getline(input,lineStr)){
        istringstream lineStream(lineStr);
        
        int wordCount=1;
        string puzzleWord, orintation;
        string direction;
        int startingRow, startingColumn;
        
//        Get each word
        while(lineStream>>word){
            istringstream wordStream(word);
            if(wordCount==1){
                puzzleWord=word;
                wordCount+=1;
            }
            else if(wordCount==2){
                wordStream>>startingRow;
                wordCount+=1;
            }
            else if(wordCount==3){
                wordStream>>startingColumn;
                wordCount+=1;
            }
            else if(wordCount==4){
                wordStream>>direction;
                wordCount+=1;
            }
            else if(wordCount==5){
                wordStream>>orintation;
                wordCount+=1;
            }
            else{
                wordCount+=1;
            }
        }
        wordCount--;
        
//        INPUT CHECKS
//        Check number of values
        if (wordCount!=5){
            cout<<"Invalid line! Number of values is different than 5."<<endl;
        }
//        Check range
        else if(startingRow<0 || startingColumn<0 || startingRow>row-1 || startingColumn>column-1){
            cout<<"Starting point is out of range! Point: "<< startingRow <<","<< startingColumn << endl;
        }
//        Check direction
        else if(direction!="l" && direction!="r" && direction!="u" && direction!="d" ){
            cout<<"Invalid input for direction! Direction: "<<direction<<endl;
        }
//        Check orientation
        else if(orintation!="CCW" && orintation!="CW"){
            cout<<"Invalid input for orientation! Orientation: "<<orintation<<endl;
        }
//        If there is not an error call puzzle function
        else{
            resultMatrix = puzzle(row, column, startingRow, startingColumn, puzzleWord, direction, orintation, resultMatrix);
            printpuzzle(resultMatrix);
        }
    }
    return 0;
}

