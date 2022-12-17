#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "QuadraticProbing.h"
using namespace std;
int ARRAY_SIZE = 4096;

int main( ){

    //    *********************************************
    //    *********************************************
    //    -----------    DECOMPRESSION   --------------
    //    *********************************************
    //    *********************************************


    //  *********************
    //  INITIALIZE HASH TABLE
    //  *********************

    HashTable<string> h1(4096);

    int idx = 0;

    for (int x=0; x<256 ; x++){
        h1.insert(string(1,x));
        idx++;
    }

    //  ***************************
    //  OPEN INPUT AND OUTPUT FILES
    //  ***************************

    string compoutFile ="compout";
    ifstream compout(compoutFile);

    ofstream outputFile;
    outputFile.open("decompout");

    char ch;
    string word ="";
    string prevText;
    int firstFlag=1;

    //  ***********************
    //  DECOMPRESSION ALGORITHM
    //  ***********************

    while (!compout.eof()){ //Loop until end of the file
        compout.get(ch);

        if (ch!=32){ // Check if the characther is space (" ")
            word+=ch;
        }else{
            
            if(!compout.eof()){
                stringstream stream;
                stream <<word;
                int code;
                stream>>code;
                
                
                if(firstFlag==1){ //check if it is the first characther if it set prevText
                    outputFile<<h1.stringInIndex(code);
                    prevText =h1.stringInIndex(code);
                    firstFlag=0;
                }else{
                    if (h1.isIndexActive(ARRAY_SIZE-1)!=1){

                        int activeFlag = 0;
                        if(h1.isIndexActive(code)){ //check if the index is empty
                            activeFlag=1;
                        }
                        
                        if(activeFlag==0){ // if index is empty set add to previous string + first char of previous text
                            string add =prevText+prevText.front();
                            h1.insert(add);
                            if (h1.contains(add)==3114){
                                string k = "s";
                            }
                            outputFile<<h1.stringInIndex(code); // add current code's string demcompout
                            prevText =h1.stringInIndex(code);
                        }else{ // if index is not empty set add to prev string + first char of current string
                            outputFile<<h1.stringInIndex(code); // add current code's string demcompout
                            
                            string add =prevText+h1.stringInIndex(code).front();
                            h1.insert(add);
                            if (h1.contains(add)==3114){
                                string k = "s";
                            }
                            prevText =h1.stringInIndex(code);
                        }
                        
                    }else{
                        int activeFlag = 0;
                        if(h1.isIndexActive(code)){ //check if the index is empty
                            activeFlag=1;
                        }
                        if(activeFlag==1){
                            outputFile<<h1.stringInIndex(code);
                        }
                        
                    }
                }
                word="";
            }
        }
    }
    outputFile.close();
    return 0;

}