// Mustafa Enes Gedikoglu 27779

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

struct movie{
    string name, actor;
    double rating;
    int rating_occur=0;
};


void printMenu(){
    cout<<"---"<<endl;
    cout<<"MENU"<<endl;
    cout<<"1. Print the series"<<endl;
    cout<<"2. Search the series according to the rating"<<endl;
    cout<<"3. Add the series to the favorite list"<<endl;
    cout<<"4. Print the favorite list"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"---"<<endl;

}


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


vector<movie> SelectSort(vector<movie> & a){
    int j, k, maxIndex, numElts=a.size();
    double temp;
    string tempactor,tempname;
    for(k=0; k<numElts-1; k++){
        maxIndex=k;
        for(j=k+1;j<numElts;j++){
            if (a[j].rating > a[maxIndex].rating || (a[j].rating == a[maxIndex].rating && a[j].name < a[maxIndex].name)){
                maxIndex=j;
            }
        }
        temp=a[k].rating;
        a[k].rating=a[maxIndex].rating;
        a[maxIndex].rating=temp;
        
        tempname=a[k].name;
        a[k].name=a[maxIndex].name;
        a[maxIndex].name=tempname;
        
        tempactor=a[k].actor;
        a[k].actor=a[maxIndex].actor;
        a[maxIndex].actor=tempactor;
    }
    return a;
}


void option1(vector<movie> & list){
    cout<<"RANK,NAME,ACTOR,POINTS"<<endl;
    for(int x=0; x<list.size() ;x++){
        cout<<x+1<<","<<list[x].name<<","<<list[x].actor<<","<<list[x].rating<<endl;
    }
}


void option2(vector<movie> & list, double min){
    cout<<"RANK,NAME,ACTOR,POINTS"<<endl;
    for (int x=0; x<list.size();x++){
        if (list[x].rating>=min){
            cout<<x+1<<","<<list[x].name<<","<<list[x].actor<<","<<list[x].rating<<endl;
        }
    }
}


bool before_option3(vector<movie> & list, string fav){
    bool fav_check=false;
    for (int x=0;x<list.size();x++){
        if (list[x].name==fav){
            fav_check=true;
        }
    }
    return fav_check;
}


bool second_before_optin3(vector<movie> & list, string fav){
    bool fav_check=true;
    for (int x=0;x<list.size();x++){
        if (list[x].name==fav){
            fav_check=false;
        }
    }
    return fav_check;
}


vector <movie> option3(vector<movie> & list, string fav, vector<movie> favlist){
    for (int x=0;x<list.size();x++){
        if(list[x].name==fav){
            movie mv;
            mv.name=list[x].name;
            mv.actor=list[x].actor;
            mv.rating=list[x].rating;
            favlist.push_back(mv);
        }
    }
    return favlist;
}


void option4(vector<movie> & list){
    if (list.size()==0){
        cout<<"Your favorite list is currently empty!"<<endl;
    }
    else{
        cout<<"RANK,NAME,ACTOR,POINTS"<<endl;
        for(int x=0; x<list.size() ;x++){
            cout<<x+1<<","<<list[x].name<<","<<list[x].actor<<","<<list[x].rating<<endl;
        }
    }
}


int main() {
    string actorFile, ratingFile;
    ifstream input1, input2;
    
    cout<<"Welcome to Netflix TV Series Ratings Calculator!"<<endl;
    cout<<"Please enter a filename for Series-Actor file: ";
    cin>>actorFile;

    input1.open(actorFile.c_str());
    
    while(input1.fail()){
        cout<<"Can not find the specified file."<<endl;
        cout<<"Please enter a filename for Series-Actor file: ";
        cin>>actorFile;
        input1.open(actorFile.c_str());
    }
    
    cout<<"Please enter a filename for Rating file: ";
    cin>>ratingFile;

    input2.open(ratingFile.c_str());
    
    while(input2.fail()){
        cout<<"Can not find the specified file."<<endl;
        cout<<"Please enter a filename for Rating file: ";
        cin>>ratingFile;
        input2.open(ratingFile.c_str());
    }
    
//    INSERT ACTOR FILE
    
    vector <movie> movies;
    string lineActor, wordActorfile;
    
    while (getline(input1,lineActor)){
        
        istringstream lineStream(lineActor);
        
        string movie_name="", actor_name="";

        bool semiColumn_check=false;
        
        while(lineStream>>wordActorfile){
            if (semiColumn_check==false){
                actor_name+=wordActorfile+" ";
            }
            else{
                movie_name+=wordActorfile+" ";
            }
            if (wordActorfile.back()==';'){
                semiColumn_check=true;
            }
        }
        
        actor_name.erase(actor_name.length()-2);
        movie_name.erase(movie_name.length()-1);
        movie_name=upper_case(movie_name);
        actor_name=upper_case(actor_name);
        movie mv;
        mv.name=movie_name;
        mv.actor=actor_name;
        movies.push_back(mv);
    }
    input1.close();
    
//    INSERT RATING FILE
    
    string lineRating, wordRatingfile;
    
    while (getline(input2,lineRating)){
        
        istringstream lineStream(lineRating);
        
        double rating;
        string movie_name;
        
        bool isFirst=true;
        
        while(lineStream>>wordRatingfile){
            
            if(isFirst==true){
                rating=stod(wordRatingfile);
                isFirst=false;
            }
            else{
                movie_name+=wordRatingfile+" ";
            }
        }
        movie_name.erase(movie_name.length()-1);
        movie_name=upper_case(movie_name);
        
        for (int x=0; x<movies.size(); x++){
            if (movie_name==movies[x].name){
                if (movies[x].rating_occur==0){
                    movies[x].rating=rating;
                    movies[x].rating_occur+=1;
                }
                else{
                    movies[x].rating=movies[x].rating*movies[x].rating_occur;
                    movies[x].rating+=rating;
                    movies[x].rating_occur+=1;
                    movies[x].rating=movies[x].rating/movies[x].rating_occur;
                }
            }
        }
    }
    input2.close();
    
    movies=SelectSort(movies);
    
    double choice;
    
    
    printMenu();
    cout<<"Enter your choice: ";
    cin>>choice;
    cout<<"---"<<endl;
    
    double minchoice;
    string fav, favend="";
    bool favCheck, favCheck2;
    vector<movie> favList;
    
    while (choice!=5){
        bool cinfailCheck=false;
        if(cin.fail()){
            cinfailCheck=true;
        }
        if(choice==1){
            option1(movies);
            printMenu();
            cout<<"Enter your choice: ";
            cin>>choice;
            cout<<"---"<<endl;
        }
        else if(choice==2){
            cout<<"Please enter the minimum rating: ";
            
            if (cin>>minchoice){
                if (minchoice>=0 && minchoice<=10){
                    option2(movies,minchoice);
                    
                    printMenu();
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    cout<<"---"<<endl;
                }
                else{
                    cout<<"This is not a valid rating!"<<endl;
                    printMenu();
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    cout<<"---"<<endl;

                }
            }
            else{
                cin.clear();
                string chc;
                cin>>chc;
                cout<<"This is not a valid rating!"<<endl;
                printMenu();
                cout<<"Enter your choice: ";
                cin>>choice;
                cout<<"---"<<endl;
            }
        }
        
        else if(choice==3){
            cin.clear();
//            cin.ignore();
            cout<<"Please enter the name of series: ";
            getline(cin, fav);
            getline(cin, fav);

            fav=upper_case(fav);
            favCheck=before_option3(movies, fav);
            favCheck2=second_before_optin3(favList,fav);
            
            if (favCheck==true&& favCheck2==true){
                favList=option3(movies, fav, favList);
                printMenu();
                cout<<"Enter your choice: ";
                cin>>choice;
                cout<<"---"<<endl;
            }
            
            else if (favCheck==true&& favCheck2==false){
                cout<<"Your favorite list already have "<<fav<<endl;
                printMenu();
                cout<<"Enter your choice: ";
                cin>>choice;
                cout<<"---"<<endl;
            }
            
            else{
                cout<<"There is no such TV series!"<<endl;
                printMenu();
                cout<<"Enter your choice: ";
                cin>>choice;
                cout<<"---"<<endl;
            }
        }
        
        else if (choice==4){
            favList=SelectSort(favList);
            option4(favList);
            printMenu();
            cout<<"Enter your choice: ";
            cin>>choice;
            cout<<"---"<<endl;
        }
        else if ((choice!=1 && choice!=2 && choice!=3 && choice!=4) && cinfailCheck==false){
            cout<<"This is not a valid option!"<<endl;
            printMenu();
            cout<<"Enter your choice: ";
            cin>>choice;
            cout<<"---"<<endl;
        }
        else{
            cin.clear();
            string chc;
            cin>>chc;
            cout<<"This is not a valid option!"<<endl;
            printMenu();
            cout<<"Enter your choice: ";
            cin>>choice;
            cout<<"---"<<endl;
        }
    }
    return 0;
}
