// Mustafa Enes Gedikoglu 27779

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "favoriteseries.h"
#include "date.h"
using namespace std;

string upper_case(string word){
    string new_word="";
    for (char c: word){
        if (c<=122 && c>=97){
            c=c-32;
        }
        new_word+=c;
    }
    return new_word;
}

vector <episode> readepisodefile(){
    ifstream input1;
//    string episodeFile="/Users/mustafa/desktop/the6_1/the6_1/episodes.txt";
    string episodeFile="episodes.txt";
    input1.open(episodeFile.c_str());
    
    vector <episode> episodes;
    string lineEpisode, wordEpisode;
    
    while (getline(input1,lineEpisode)){
        istringstream lineStream(lineEpisode);
        
        int count=0, seriescode;
        string date, slot, episodename="";
        
        while (lineStream>>wordEpisode){
            if (count==0){
                stringstream code(wordEpisode);
                code >> seriescode;
                count+=1;
            }
            else if (count==1){
                date=wordEpisode;
                count+=1;
            }
            else if (count==2){
                slot=wordEpisode;
                count+=1;
            }
            else if (count>2){
                episodename+=wordEpisode+" ";
            }
        }
        
        int month,day,year;
        char sign = '/';
        int indx=0, k=0, coun=0;
        while (coun<2){
            k=date.find(sign,indx);
            string word=date.substr(indx,k-indx);
            indx=k+1;
            if (coun==0){
                stringstream in(word);
                in >> month;
                coun+=1;
            }
            else if (coun==1){
                stringstream in(word);
                in >> day;
                coun+=1;
            }
        }
        stringstream in(date.substr(indx,date.length()-indx));
        in >> year;
        
        Date d(month, day, year);
    
        episodename.erase(episodename.length()-1);
        episodename=upper_case(episodename);
        slot=upper_case(slot);
        episode ep;
        ep.episodeName=episodename;
        ep.slot=slot;
        ep.seriesCode=seriescode;
        ep.date=d;
        episodes.push_back(ep);
    }
    input1.close();

    return episodes;
}




vector <series> readseriesfile(vector <episode> episodes){
    ifstream input2;
//    string seriesFile="/Users/mustafa/desktop/the6_1/the6_1/series.txt";
    string seriesFile="series.txt";
    input2.open(seriesFile.c_str());
    
    vector <series> serie;
    string lineSeries, wordSeries, actor, seriename, word="";
    vector <string> actors;
    int seriescode;
    
    while (getline(input2,lineSeries)){
        istringstream lineStream(lineSeries);
        int count=0;
        
        
        while (lineStream>>wordSeries){
            if (count==0){
                stringstream code(wordSeries);
                code >> seriescode;
                count+=1;
            }
            else if (count>0){
                if (wordSeries.back()==';'){
                    word+=wordSeries;
                    seriename=word.erase(word.length()-1);
                    word="";
                }
                else if (wordSeries.back()==','){
                    word+=wordSeries;
                    word=word.erase(word.length()-1);
                    word=upper_case(word);
                    actors.push_back(word);
                    word="";
                }
                else{
                    word+=wordSeries+" ";
                }
            }
        }
        word=word.erase(word.length()-1);
        word=upper_case(word);
        actors.push_back(word);
        word="";
        
        seriename=upper_case(seriename);
        series seri;
        seri.seriesName=seriename;
        seri.seriesCode=seriescode;
        seri.actorNames=actors;
        
        vector <episode> serieepisodes;
        
        for (int x=0; x<episodes.size(); x++){
            if (seriescode==episodes[x].seriesCode){
                serieepisodes.push_back(episodes[x]);
            }
        }
        seri.episodes=serieepisodes;
        serie.push_back(seri);
        actors.clear();
    }
    return serie;
}


vector <episode> SelectSort(vector <episode> & a){
    int j, k, maxIndex, numElts=a.size();
    string episodeName, slot, slotchange, tempname, tempslot;
    int tempcode;
    Date date, tempdate;
    
    
    for (int x=0; x<numElts; x++){
        if (a[x].slot=="MORNING"){
            a[x].slot='a';
        }
        else if (a[x].slot=="AFTERNOON"){
            a[x].slot='b';
        }
        
        else if (a[x].slot=="EVENING"){
            a[x].slot='c';
        }
        else if (a[x].slot=="NIGHT"){
            a[x].slot='d';
        }
    }
    
    
    for(k=0; k<numElts-1; k++){
            maxIndex=k;
            for(j=k+1;j<numElts;j++){
                if (a[j].date < a[maxIndex].date || (a[j].date == a[maxIndex].date && a[j].slot < a[maxIndex].slot)|| (a[j].date == a[maxIndex].date && a[j].slot == a[maxIndex].slot && a[j].seriesCode < a[maxIndex].seriesCode)){
                    maxIndex=j;
                }
            }
            tempdate=a[k].date;
            a[k].date=a[maxIndex].date;
            a[maxIndex].date=tempdate;
            
            tempname=a[k].episodeName;
            a[k].episodeName=a[maxIndex].episodeName;
            a[maxIndex].episodeName=tempname;
            
            tempslot=a[k].slot;
            a[k].slot=a[maxIndex].slot;
            a[maxIndex].slot=tempslot;
            
            tempcode=a[k].seriesCode;
            a[k].seriesCode=a[maxIndex].seriesCode;
            a[maxIndex].seriesCode=tempcode;
    }
    
    for (int x=0; x<numElts; x++){
        if (a[x].slot=="a"){
            a[x].slot="MORNING";
        }
        else if (a[x].slot=="b"){
            a[x].slot="AFTERNOON";
        }
        
        else if (a[x].slot=="c"){
            a[x].slot="EVENING";
        }
        else if (a[x].slot=="d"){
            a[x].slot="NIGHT";
        }
    }

    return a;
}

void option1(vector <episode> episodes, vector <series> series){
    cout<<"CODE,SERIES,EPISODE,DATE,SLOT"<<endl;
    for (int x=0; x<episodes.size(); x++){
        string seriesname;
        for(int y=0; y<series.size(); y++){
            if (episodes[x].seriesCode==series[y].seriesCode){
                seriesname=series[y].seriesName;
            }
        }
        cout<<episodes[x].seriesCode<<","<<seriesname<<","<<episodes[x].episodeName<<","<<episodes[x].date<<","<<episodes[x].slot<<endl;
    }
}



void printMenu(){
    cout<<"---"<<endl;
    cout<<"MENU"<<endl;
    cout<<"1. Print all TV series"<<endl;
    cout<<"2. Add TV series"<<endl;
    cout<<"3. Drop TV series"<<endl;
    cout<<"4. Print your favorite series with schedule"<<endl;
    cout<<"5. Print all your favorite actors"<<endl;
    cout<<"6. Exit"<<endl;
    cout<<"---"<<endl;
}



int main(){
    string name, surname;
    cout<<"Welcome to my favorite TV series schedule program!"<<endl;
    cout<<"Please, enter your name and surname: ";
    cin>>name>>surname;
    
    vector <episode> episodes=readepisodefile();
    vector <series> series=readseriesfile(episodes);
    episodes=SelectSort(episodes);


    
    double choice;
        
    FavoriteSeries favs(name, surname);
    printMenu();
    cout<<"Please enter your choice: ";
    cin>>choice;
    while (choice!=6){
        if (choice==1){
            option1(episodes, series);
            printMenu();
            cout<<"Please enter your choice: ";
            cin>>choice;
        }
        else if (choice==2){
            int favcode;
            cout<<"Enter code for the TV series you want to add: ";
            cin>>favcode;
            
            struct series a;
            bool check=true;
            for (int x=0; x<series.size(); x++){
                if (favcode==series[x].seriesCode){
                    a=series[x];
                    check=false;
                }
            }
            
            if (favs.ifExists(favcode)==true){
                cout<<upper_case(favs.getFullName())<<", you can't add this TV series because you already added it!"<<endl;
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            else if(favs.isConflict(a)==true){
                cout<<upper_case(favs.getFullName())<<", you can't add this TV series because of a date and slot conflict!"<<endl;
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            else if(check){
                cout<<upper_case(favs.getFullName())<<", there is no such TV series in the database!"<<endl;
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            else{
                favs.addSeries(a);
                cout<<upper_case(favs.getFullName())<<", "<<a.seriesName<<" added to your schedule."<<endl;
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            
        }
        else if (choice==3){
            if(favs.isListEmpty()){
                cout<<upper_case(favs.getFullName())<<", you did not add any TV series yet!"<<endl;
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            else{
                int drop;
                cout<<"Enter code for the TV series you want to drop: ";
                cin>>drop;
                
                struct series a;
                bool check=true;
                for (int x=0; x<series.size(); x++){
                    if (drop==series[x].seriesCode){
                        a=series[x];
                        check=false;
                    }
                }
                
                if (favs.ifExists(drop)==false){
                    cout<<upper_case(favs.getFullName())<<", there is no such TV series in your favorite list!"<<endl;
                }
                else{
                    favs.dropSeriesSorted(drop);
                    cout<<upper_case(favs.getFullName())<<", "<<a.seriesName<<" has been dropped from your favorite list!"<<endl;
                }
                printMenu();
                cout<<"Please enter your choice: ";
                cin>>choice;
            }
            
        }
        else if (choice==4){
            if (favs.isListEmpty()==true){
                cout<<upper_case(favs.getFullName())<<", you did not add any TV series yet!"<<endl;
            }
            else{
                cout<<upper_case(favs.getFullName())<<", here is your favorite TV series:"<<endl;
                favs.displayFavoriteList();
            }
            printMenu();
            cout<<"Please enter your choice: ";
            cin>>choice;
        }
        else if (choice==5){
            if (favs.isListEmpty()==true){
                cout<<upper_case(favs.getFullName())<<", you did not add any TV series yet!"<<endl;
            }
            else{
                cout<<upper_case(favs.getFullName())<<", here is your favorite actors:"<<endl;
                favs.displayFavoriteActors();
            }
            printMenu();
            cout<<"Please enter your choice: ";
            cin>>choice;
        }
        else{
            cout<<"Invalid option!"<<endl;
            printMenu();
            cout<<"Please enter your choice: ";
            cin>>choice;
            
        }
    }
    cout<<"Goodbye, "<<upper_case(favs.getFullName())<<"!"<<endl;
    return 0;
}
