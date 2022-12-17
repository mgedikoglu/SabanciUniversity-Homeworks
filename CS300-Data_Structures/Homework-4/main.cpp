//
//  main.cpp
//  hw4cs300meg
//
//  Created by Mustafa Enes GEDİKOĞLU on 22.12.2021.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

//Read File
vector <string> readFile(istream & input){
    vector <string> words;
    string line;
    
    while(input >> line){
        words.push_back(line);
    }
    return words;
}

// Retrurns true if word1 and word2 differs one char
bool oneCharDiff( const string & word1, const string & word2 ){
    string mainWord;
    if( word1.length( ) == word2.length( ) ){ //if word1 and word2 same length cheks difference between them
        int diff = 0;
        for (int x = 0; x<word1.length(); x++){
            if(word1[x] != word2[x]){
                diff++;
            }
        }
        if(diff == 1){ //if difference one char returns true
            return true;
        }
    }else if(word1.length( ) > word2.length( )){ //if word1 is longer than word2 deletese each char from word1 and checks if it is equal to word2
        for (int x = 0; x< word1.length(); x++){
            string temp = word1;
            temp.erase(x,1);
            if (temp == word2){
                return true;
            }
        }
    }else{ //if word2 is longer than word1
        for (int x = 0; x< word2.length(); x++){
            string temp = word2;
            temp.erase(x,1);
            if (temp == word1){
                return true;
            }
        }
    }
    return false;
}


unordered_map < string, vector <string> > wordsOneOp(const vector<string> & words ){ //creates an unordered map with string and vector which consists words differ one char from string
    
    unordered_map<string,vector<string>> wordsOneO;
    
    for(int x=0; x<words.size(); x++){
        vector <string> adjWords;
        for(int y=0; y<words.size(); y++){
            if(oneCharDiff(words[x], words[y])){
                wordsOneO[words[x]].push_back(words[y]);
            }
        }
    }
    
    return wordsOneO;
}


struct element {
    string vertex;
    int distance;
};

unordered_map<string, string> bfs(unordered_map<string, vector <string>> & graph, string word1, string word2){ //returns word an its predecessor
    
    deque<element> queue;
    unordered_map<string, bool> visited;
    unordered_map<string, string> preds;
    queue.push_front({word1, 0});
    int dist=0;
    bool found = false;
    
    string pred = word1; //
    
    while(queue.size()>0 || found== false){
        element current_element = queue.back();
        string current = current_element.vertex;
        dist = current_element.distance;
        queue.pop_back();
        visited[current]=true;
        pred = current; //
        for (int i=0 ; i<graph[current].size(); i++){
            if(visited[graph[current][i]] ==false){
                if(graph[current][i] == word2){
                    found = true;
                    preds[word2] = pred; //
                    return preds;
                }else{
                    queue.push_front({graph[current][i], 1+dist});
                    if(preds.find(graph[current][i]) == preds.end()){
                        preds[graph[current][i]] = pred;
                    }
//                    preds[graph[current][i]] = pred;
                }
            }
        }
    }
    return preds;
}


int bfsCheck(unordered_map<string, vector <string>> & graph, string word1, string word2){ //return 0 if there is no path from word1 to word2
    
    deque<element> queue;
    unordered_map<string, bool> visited;
    unordered_map<string, string> preds;
    queue.push_front({word1, 0});
    int dist=0;
    bool found = false;
    
    while(queue.size()>0 || found== true){
        element current_element = queue.back();
        string current = current_element.vertex;
        dist = current_element.distance;
        queue.pop_back();
        visited[current]=true;
        for (int i=0 ; i<graph[current].size(); i++){
            if(visited[graph[current][i]] ==false){
                if(graph[current][i] == word2){
                    found = true;
                    return dist + 1;
                }else{
                    queue.push_front({graph[current][i], 1+dist});
                }
            }
        }
    }
    return 0;
}


string printFormat(string word1,string word2){ //return a string of operation that made while changin word
    string result = "";
    
    if(word1.length() == word2.length()){ //change operation
        int indexCahnge;
        for (int x = 0; x< word1.length(); x++){
            if(word1[x] != word2[x]){
                indexCahnge = x;
                result = "(change ";
                result += word1[x];
                result += " at position ";
                result += to_string(x+1);
                result += " to ";
                result += word2[x];
                result += ")";
                return result;
            }
        }
    }else if(word1.length() > word2.length()){ //delete operation
        int indexDelete;
        for (int x = 0; x< word1.length(); x++){
            string temp=word1;
            temp.erase(x,1);
            if(temp == word2){
                indexDelete = x;
                result = "(delete ";
                result += word1[x];
                result += " at position ";
                result += to_string(x+1);
                result += ")";
                return result;
            }
        }
    }else{ //insert operation
        int indexInsert;
        for (int x = 0; x< word2.length(); x++){
            string temp=word2;
            temp.erase(x,1);
            if(temp == word1){
                indexInsert = x+1;
                result = "(insert ";
                result += word2[x];
                result += " after position ";
                result += to_string(x);
                result += ")";
                return result;
            }
        }
    }
    
    return result;
}

void printShortestPath(unordered_map < string, vector <string> > graph, string word1, string word2){ // prints shortes path
    
    vector <string> print;

    if (word1.length() >= word2.length()){
        unordered_map<string, string> preds = bfs(graph, word1, word2);
        
        string word = word2;
        
        print.push_back(word2);
        while(preds[word] != ""){
            print.push_back(preds[word]);
            word = preds[word];
        }
        
        string first = print[print.size()-1];
        
        cout<< print[print.size()-1]<<endl;
        for (int x = print.size()-2; x>=0; x--){
            string second = print[x];
            cout<< print[x]<< " " <<printFormat(first, second)  <<endl;
            first=second;
        }

    }else{
        
        string temp = word1;
        word1 = word2;
        word2 = temp;
        
        unordered_map<string, string> preds = bfs(graph, word1, word2);
        
        string word = word2;
        print.push_back(word2);
        while(preds[word] != ""){
            print.push_back(preds[word]);
            word = preds[word];
        }
        
        string first = print[0];
        cout<< first<<endl;
        
        for (int x = 1; x<print.size(); x++){
            string second = print[x];
            cout<< print[x]<< " " <<printFormat(first, second)  <<endl;
            first=second;
        }
    }
}

bool existCheck(vector <string> words, string word1, string word2){ //return true if both word in words.txt
//    int count = 0;
//    for (int x = 0; x<words.size(); x++){
//        if(words[x]==word1 || words[x] == word2){
//            count++;
//        }
//    }
//    if(count==2){
//        return true;
//    }
    if (!(count(words.begin(), words.end(), word1) && count(words.begin(), words.end(), word2))){
        return false;
    }
    return true;
}



int main() {
    ifstream input;
    input.open("words.txt");
    vector<string> words = readFile(input);
    
    unordered_map < string, vector <string> > wordsVector;
    wordsVector = wordsOneOp(words);
    
    string word1=" ", word2;
    
    while(word1.at(0) != '*'){
        cout <<"Enter two words: ";
        cin>>word1>>word2;
        
        if(word1.at(0) != '*'){
            if(existCheck(words, word1, word2)){
                if (bfsCheck(wordsVector, word1, word2) != 0){
                    printShortestPath(wordsVector, word1, word2);
                }else{
                    cout<<"No sequence of one letter transformations exists."<<endl;
                }
            }else{
                cout<<"Both words must be in words.txt"<<endl;
            }
        }
    }
    
    return 0;
}
