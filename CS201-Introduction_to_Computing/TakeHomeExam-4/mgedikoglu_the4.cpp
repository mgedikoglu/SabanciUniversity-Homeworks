#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

int smillarty(string pool, string main){
    int indx=0;
    int smillarty=0;
    if (pool.length()==main.length()){
        for(char c_main: main){
            char c=pool[indx];
            if (c_main==c){
                smillarty+=1;
            }
            indx++;
        }
    }
    return smillarty;
}

string lower_case(string word){
    string new_word="";
    for (char c: word){
        if (c<=90 && c>=65){
            c=c+32;
        }
        new_word+=c;
    }
    return new_word;
}


int max_smillarity(string wordMain, string fileword){
    string lineStr2, wordPool, lineStr1;
    string new_wordMain=lower_case(wordMain);
    
    ifstream input1;
    input1.open(fileword.c_str());
    
    int max_smil=0;
    
    while(input1>>wordPool){
        string new_wordPool=lower_case(wordPool);
        int smil=smillarty(new_wordPool, new_wordMain);
        if (smil>=max_smil){
            max_smil=smil;
        }
    }
    return max_smil;
}


int numofchar(string text, char a){
    int num=0;
    for (char c: text){
        if (c==a){
            num++;
        }
    }
    return num;
}

string curlyParant(string new_wordMain, string new_wordPool, string curly, int max){

    
    if (new_wordMain!=new_wordPool && max<(double(new_wordPool.length())/2)){
        if (curly==""){
            curly+=new_wordMain;
        }
    }

    return curly ;
}

int main(){
    string fileword, filemain, lineStr2, wordMain, wordPool, lineStr1;
    ifstream input1, input2;
    
    string output = "";
    
    cout<<"Please enter a filename for the word pool: ";
    cin>>fileword;
    input1.open(fileword.c_str());

    while (input1.fail()) {
        cout<<"Cannot open the word pool file."<<endl;
        cout<<"Please enter a filename for the word pool: ";
        cin>>fileword;
        input1.open(fileword.c_str());
    }


    cout<<"Please enter a filename for the main text: ";
    cin>>filemain;
    input2.open(filemain.c_str());

    while (input2.fail()) {
        cout<<"Cannot open the main text file."<<endl;
        cout<<"Please enter a filename for the main text: ";
        cin>>filemain;
        input2.open(filemain.c_str());
    }


    while(getline(input2,lineStr2)){
        
        istringstream lineStream(lineStr2);

        while(lineStream>>wordMain){
            
            string new_wordMain=lower_case(wordMain);
            int max_smil=0;
            string paran="", curlyParan="";

            string curly="";
            string curly1="";
            while(input1>>wordPool){
                string new_wordPool=lower_case(wordPool);
                int smil=smillarty(new_wordPool, new_wordMain);
                
                
                if (smil>=max_smil){
                    max_smil=smil;
                }
                
                int max=max_smillarity(new_wordMain, fileword);
                

                if (new_wordMain==new_wordPool){
                    output+=new_wordMain+" ";
                }

                else if (new_wordMain!=new_wordPool && new_wordMain.length()==new_wordPool.length() && max>=(double(new_wordMain.length())/2) && smil==max){
                    paran+=new_wordPool+",";
                }
                else if(new_wordMain!=new_wordPool && max<(double(new_wordMain.length())/2) && curlyParan=="" ){
                    curlyParan+="{"+new_wordMain+"} ";
                }
   
            }

            char c= ',';
            int count= numofchar(paran, c);
            
            if (paran!="" && count>1){
                paran=paran.substr(0,paran.length()-1);
                output+="("+paran+") ";
            }
            
            else if (count==1){
                output+= paran.substr(0,paran.length()-1)+" ";
            }
            output+=curlyParan;
            
     
            input1.clear();
            input1.seekg(0);
        }
        if (output.back()!='\n'){
            output=output.substr(0,output.length()-1);
        }
        output+="\n";
    }

    
    
    cout<<"You may find the results below:"<<endl<<endl;
    cout<<output;
    return 0;
}
