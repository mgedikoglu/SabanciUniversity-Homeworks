//
//  main.cpp
//  q4
//
//  Created by Mustafa on 25.01.2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;


int main() {

    ifstream input1;
    string file="/Users/mustafa/desktop/q4/q4/dictionary.txt";
    input1.open(file.c_str());


    string word;
    string filee="";


    for (int x=97 ; x<122; x++){

        while (getline(input1,word)){
            
            istringstream lineStream(word);
            cout<<word;
            if (word.front()==x){
                filee+=word+"\n";
                
            }
        }
        
        ofstream output;
        string filename = word.front()+".txt";
        
        output.open(filename.c_str(), ios::app);
        output << filee << endl;
        output.close();
        
        filee="";
    }

    input1.close();
    return 0;
}


//#include <iostream>
//#include <string>
//#include <fstream>
//using namespace std;
//
//int main(){
//
//
//    ofstream output;
//    string filename = "out.txt";
//    string line;
//    output.open(filename.c_str(), ios::app);
//
//
//    for (int x=97 ; x<122; x++){
//
//        ifstream input1;
//        string file="/Users/mustafa/desktop/q4/q4/dictionary.txt";
//        input1.open(file.c_str());
//        string word;
//        while (getline(input1,line)){
//            istringstream lineStream(line);
//            lineStream>>word;
//            if (word.front()==x){
//                output << word << endl;
//            }
//        }
//    }
//
//
//
//    output.close();
//    return 0;
//}
