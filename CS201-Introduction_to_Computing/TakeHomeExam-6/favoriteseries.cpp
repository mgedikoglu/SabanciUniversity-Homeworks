#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "favoriteseries.h"
using namespace std;

FavoriteSeries::FavoriteSeries(string name, string surname){
    userName=name;
    userSurname=surname;
    vector <series> favSeries;
}


string FavoriteSeries::getFullName() const{
    string fullName=userName+" "+userSurname;
    return fullName;
}

void FavoriteSeries::addSeries(const series & a){
    favSeries.push_back(a);
}
void FavoriteSeries::dropSeriesSorted(int seriesCode){
    vector <series> tempfavseries;
    for (int x=0; x<favSeries.size(); x++){
        if(seriesCode!=favSeries[x].seriesCode){
            tempfavseries.push_back(favSeries[x]);
        }
    }
    favSeries=tempfavseries;
}

bool FavoriteSeries::ifExists(int seriesCode){
    for (int x=0; x<favSeries.size(); x++){
        if (seriesCode==favSeries[x].seriesCode){
            return true;
        }
    }
    return false;
}

bool FavoriteSeries::isListEmpty() const{
    if (favSeries.size()==0){
        return true;
    }
    else{
        return false;
    }
}

void FavoriteSeries::displayFavoriteList() const{
    
    vector <episode> a;
    for (int x=0; x<favSeries.size(); x++){
        for (int y=0; y<favSeries[x].episodes.size(); y++){
            a.push_back(favSeries[x].episodes[y]);
        }
    }

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
    cout<<"CODE,SERIES,EPISODE,DATE,SLOT"<<endl;
    
    for (int x=0; x<a.size(); x++){
        string seriesname;
        for(int y=0; y<favSeries.size(); y++){
            if (a[x].seriesCode==favSeries[y].seriesCode){
                seriesname=favSeries[y].seriesName;
            }
        }
        cout<<a[x].seriesCode<<","<<seriesname<<","<<a[x].episodeName<<","<<a[x].date<<","<<a[x].slot<<endl;
    }
}

void FavoriteSeries::displayFavoriteActors() const{
    vector <string> actorler;
    vector <int> a;
    bool check=false;
    int indx;
    
    for (int x=0; x<favSeries.size(); x++){
        for (int y=0; y<favSeries[x].actorNames.size(); y++){
            for (int b=0; b<actorler.size(); b++){
                if (actorler[b]==favSeries[x].actorNames[y]){
                    check=true;
                    a[b]+=1;
                }
            }
            if (check==false){
                actorler.push_back(favSeries[x].actorNames[y]);
                a.push_back(1);
            }
            check=false;
        }
        
    }
    
    int j, k, maxIndex, numElts=a.size();
    double temp;
    string tempactor,tempname;
    for(k=0; k<numElts-1; k++){
        maxIndex=k;
        for(j=k+1;j<numElts;j++){
            if (a[j] > a[maxIndex] || (a[j] == a[maxIndex] && actorler[j] < actorler[maxIndex])){
                maxIndex=j;
            }
        }
        temp=a[k];
        a[k]=a[maxIndex];
        a[maxIndex]=temp;
        
        tempname=actorler[k];
        actorler[k]=actorler[maxIndex];
        actorler[maxIndex]=tempname;
        
    }
    
    for (int c=0; c<actorler.size(); c++){
        cout<<actorler[c]<<": "<<a[c]<<endl;
    }
}



bool FavoriteSeries::isConflict(const series & a) const{
    for (int x=0; x<favSeries.size(); x++){
        for (int y=0; y<favSeries[x].episodes.size(); y++){
            for (int b=0; b<a.episodes.size(); b++){
                if (a.episodes[b].date==favSeries[x].episodes[y].date && a.episodes[b].slot==favSeries[x].episodes[y].slot){
                    return true;
                }
            }
        }
    }
    return false;
}
