//
//  main.cpp
//  THE
//
//  Created by Mustafa on 16.10.2020.
//

#include <iostream>
using namespace std;

int main (){
    string name,course,first_time,current_grade,current_change,prev_grade,change2;
    
    cout <<"Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
    cin >> name;
    cout << "Hello "<<name<< "! Please enter the name of the course to be processed: ";
    cin >> course;
    cout <<"Hello "<<name<<"! If you take the "<< course <<" for the first time, enter YES otherwise NO: ";
    cin >> first_time;
    
    if (first_time=="YES" || first_time=="NO"){
        
        if (first_time=="YES"){
            cout<< "What is your grade from (A,B,C,D,F)? ";
            cin >> current_grade;
            
            if (current_grade=="A"||current_grade=="B"||current_grade=="C"||current_grade=="D"||current_grade=="F"){
                
                if (current_grade=="A"||current_grade=="B"||current_grade=="C"||current_grade=="D"){
                    cout<< "Do you want to switch your grade from "<<current_grade<<" to S (YES or NO)? ";
                    cin>>current_change;
                    
                    if (current_change=="YES"){
                        cout<<name<<", your final grade for "<<course<<" is S. Goodbye..."<<endl;
                    }
                    else if (current_change=="NO"){
                        cout<<name<<", your final grade for "<<course<<" is "<<current_grade<<". Goodbye..."<<endl;
                    }
                    else{
                        cout<<"Invalid grade selection. Goodbye..."<<endl;
                    }
                }
                else if (current_grade=="F"){
                    cout<< "Do you want to switch your grade from "<<current_grade<<" to U (YES or NO)? ";
                    cin>>current_change;
                    if (current_change=="YES"){
                        cout<<name<<", your final grade for "<<course<<" is U. Goodbye..."<<endl;
                    }
                    else if (current_change=="NO"){
                        cout<<name<<", your final grade for "<<course<<" is "<<current_grade<<". Goodbye..."<<endl;
                    }
                    else{
                        cout<<"Invalid grade selection. Goodbye..."<<endl;
                    }
                }
            }
            else{
                cout<<"Invalid grade selection. Goodbye..."<<endl;
            }
        }
        else if (first_time=="NO"){
            cout<<"Please enter your previous grade from (A,B,C,D,F,S,U): ";
            cin>>prev_grade;
            if (prev_grade=="A"||prev_grade=="B"||prev_grade=="C"||prev_grade=="D"||prev_grade=="F"||prev_grade=="S"||prev_grade=="U"){
                cout<<"Please enter your current grade from (A,B,C,D,F): ";
                cin>>current_grade;
                
                if(current_grade=="A"||current_grade=="B"||current_grade=="C"||current_grade=="D"||current_grade=="F"){
                    cout<<"Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
                    cin>>change2;
                    if (change2=="A"||change2=="B"||change2=="C"||change2=="D"||change2=="F"||change2=="S"||change2=="U"){
                    
                        

                        if(prev_grade=="U" && (current_grade=="A"||current_grade=="B"||current_grade=="C"||current_grade=="D") && !(change2=="S"||change2==current_grade)){
                            cout<<"Invalid grade selection. If you received U before, you may choose S or current letter grade."<<endl;
                        }
                        else if (prev_grade=="S"&&current_grade=="F"&&!(change2=="F")){
                            cout<<"Invalid grade selection. If you received S before and fail this semester, you get F."<<endl;
                        }
                        else if (prev_grade=="F"&&current_grade=="F"&&!(change2=="F")){
                            cout<<"Invalid grade selection. If you received F before, and fail this semester, you get F."<<endl;
                        }
                        
                        else if((current_grade=="A"||current_grade=="B"||current_grade=="C"||current_grade=="D")&& !(change2==current_grade||change2=="S")){
                            cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;
                        }
                        else if (current_grade=="F"&&!(change2=="F"||change2=="U")){
                            cout<<"Invalid grade selection. You cannot choose a higher or lower grade than you deserve."<<endl;
                        }
                        
                        else{
                            cout<<name<<", your final grade for "<<course<<" is "<<change2<<". Goodbye..."<<endl;
                        }
                    
                    }
                    else{
                        cout<<"Invalid grade selection. Goodbye..."<<endl;
                    }
                    
                }
                else{
                    cout<<"Invalid grade selection. Goodbye..."<<endl;
                }
            }
            else{
                cout<<"Invalid grade selection. Goodbye..."<<endl;
            }
        }
    else{
        cout<<"Invalid grade selection. Goodbye...";
    }

    }
    return 0;
}
