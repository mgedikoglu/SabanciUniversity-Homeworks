
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


void double_dot (string & dot_word, string & source){
    dot_word.erase(dot_word.length()-2);
    dot_word+=dot_word;
    int indx=0;
    int k=0;
    while (indx<source.length() && k!=string::npos){
        string search = dot_word + " ";
        k= source.find(search,indx);
        //find previous space
        int prev_space=source.rfind(" ",k);
        int last_space=source.find(" ",k);
        string word=source.substr(prev_space+1,last_space-prev_space-1);
        indx=k+1;
        if (k!=string::npos){
            cout<<"index: "<<k-1<< " word: "<<word<<endl;
        }
    }
}





//I couldn't be sure that you want main func or not, so i added it

int main(){
    string source, search, source_word;
    source="";
    cout<<"Enter source string: ";
    
    while (source_word!="END"){
        cin>>source_word;
        source += " " + source_word;
    }
    cout<<"Enter search string: ";
    cin>>search;
    while (search!="quit"){
        double_dot(search,source);
        cout<<"Enter search string: ";
        cin>>search;

    }
    return 0;
}
