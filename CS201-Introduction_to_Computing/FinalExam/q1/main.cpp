//
//  main.cpp
//  q1
//
//  Created by Mustafa on 25.01.2021.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int sumof(vector <int> i){
    int sum=0;
    if (i.size()==0){
        return 0;
    }
    else{
        for(int x=0; x<i.size(); x++){
            if(i[x]>0){
                sum+=i[x];
            }
        }
        return sum;
    }
}

void words(vector <string> s, int sumo){
    bool check=true;
    for(int x=0; x<s.size(); x++){
        if(s[x].length()>sumo){
            cout<<s[x]<<endl;
            check=false;
        }
    }
    if(check==true){
        cout<<"ERROR: No words are longer than "<<sumo<<" characters.";
    }
    
}


int main() {
    vector <int> integers;
    vector <string> strings;
    string word;
    int num;
    
    cout<<"Please enter new input: ";
    if(cin>>word){
        strings.push_back(word);
        cin.clear();
    }
    else if(cin>>num){
        integers.push_back(num);
        cin.clear();
    }
    
    
    while (word != "STOP"){
        cout<<"Please enter new input: ";
        if(cin>>word){
            strings.push_back(word);
            cin.clear();
        }
        else if(cin>>num){
            integers.push_back(num);
            cin.clear();
        }
    }

    if (strings.size()==0){
        cout<<"ERROR: String vector is empty.";
    }
    else{
        int sum =sumof(integers);
        words(strings, sum);
    }
        
    return 0;
}
