
#include <iostream>
#include <iomanip>
using namespace std;

bool source_check(string source){
    int i=0;
    
    while (i<source.length()){
        if((int(source[i])>=65 && int(source[i])<=90) || (int(source[i])>=97 && int(source[i])<=122) || int(source[i])==32 ||(int(source[i])>=48 && int(source[i])<=57)){
        }
        else{
            return false;
        }
        i+=1;
    }
    return true;
}


void pluss (string plus_word, string source){
    plus_word.erase(plus_word.length()-1);
    int indx=0;
    int k=0;
    while (indx<source.length() && k!=string::npos){
        string search = " " + plus_word;
        k= source.find(search,indx);
        //find next space
        int e=source.find(" ",k+1);
        string word=source.substr(k+1,e-k-1);
        indx=e;
        if (k!=string::npos){
            cout<<"index: "<<k<< " word: "<<word<<endl;
        }
    }
}

void dot (string dot_word, string source){
    dot_word.erase(dot_word.length()-1);
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

void star (string plus_word, string source){
    plus_word.erase(plus_word.length()-1);
    int indx=0;
    int k=0;
    while (indx<source.length() && k!=string::npos){
        string search = plus_word;
        k= source.find(search,indx);
        //find next space
        int prev_space=source.rfind(" ",k);
        int last_space=source.find(" ",k-1);
        string word=source.substr(prev_space+1,last_space-prev_space-1);
        indx=k+1;
        char space_check_1=source[k-1];
        char space_check_2=source[k+search.length()];
        
        string word_start= word.substr(0,search.length());
        string word_end= word.substr(word.length()-search.length(), search.length());
        if (k!=string::npos && int(space_check_1)!=32  && int(space_check_2)!=32 && word_start!=search && word_end!=search){
            cout<<"index: "<<k-1<< " word: "<<word<<endl;

        }
    }
}


void double_star (string plus_word, string source){
    plus_word.erase(plus_word.length()-1);
    plus_word.erase(plus_word.length()-1);
    int indx=0;
    int k=0;
    while (indx<source.length() && k!=string::npos){
        string search = plus_word;
        k= source.find(search,indx);
        //find next space
        int prev_space=source.rfind(" ",k);
        int last_space=source.find(" ",k);
        string word=source.substr(prev_space+1,last_space-prev_space-1);
        indx=k+1;
        if (k!=string::npos){
            cout<<"index: "<<k-1<< " word: "<<word<<endl;
        }
    }
}

int main() {
    string source, search, source_word;
    
    source="";
    cout<<"Enter source string: ";
    while (source_word!="END" && source_word!="end"){
        cin>>source_word;
        source += " " + source_word;
    }
    bool src_chc=source_check(source);
 
    while (src_chc==false){
        source_word="";
        source="";
        cout<<"Enter source string: ";
        while (source_word!="END"&&source_word!="end"){
            cin>>source_word;
            source += " " + source_word;
        }
        src_chc=source_check(source);
    }

    cout<<"Enter search string: ";
    cin>>search;
    char sign= search.back();
    string double_star_check=search.substr(search.length()-2,2);
    
    while (search != "quit"  && int(search.back())!=21 && search != "QUIT"){
        if (sign == 43){
            pluss(search,source);
            cout<<"Enter search string: ";
            cin>>search;
            sign= search.back();
            double_star_check=search.substr(search.length()-2,2);
        }
        else if (sign == 46){
            dot(search,source);
            cout<<"Enter search string: ";
            cin>>search;
            sign= search.back();
            double_star_check=search.substr(search.length()-2,2);
        }
        else if (sign == 42 && double_star_check=="**"){
            double_star(search,source);
            cout<<"Enter search string: ";
            cin>>search;
            sign= search.back();
            double_star_check=search.substr(search.length()-2,2);
        }
        else if (sign == 42 && double_star_check!="**"){
            star(search,source);
            cout<<"Enter search string: ";
            cin>>search;
            sign= search.back();
            double_star_check=search.substr(search.length()-2,2);
        }
        else {
            cout<<"Enter search string: ";
            cin>>search;
            sign= search.back();
            double_star_check=search.substr(search.length()-2,2);
        }
    }
    return 0;
}
