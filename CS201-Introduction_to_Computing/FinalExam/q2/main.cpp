#include <iostream>
#include <string>
#include <vector>
using namespace std;



struct schedule{
    string day;
    string timeSlot;
    schedule(string Day="", string TimeSlot=""){
        Day=day;
        TimeSlot=timeSlot;
    }
};

struct course{
    string name;
    vector <schedule> times;
};

void printSchedule(vector <schedule> & a){
    int j, k, maxIndex, numElts=a.size();
    
    for (k=0; k<a.size(); k++){
        
        if (a[k].day=="Monday"){
            a[k].day="A";
        }
        else if (a[k].day=="Tuesday"){
            a[k].day="B";
        }
        else if (a[k].day=="Wednesday"){
            a[k].day="C";
        }
        else if (a[k].day=="Thursday"){
            a[k].day="D";
        }
        else if (a[k].day=="Friday"){
            a[k].day="F";
        }
        
    }
    
    for (k=0; k<a.size(); k++){
        
        if (a[k].timeSlot=="morning"){
            a[k].timeSlot="A";
        }
        else if (a[k].timeSlot=="afternoon"){
            a[k].timeSlot="B";
        }
        
    }
    
    string tempslot,tempday;
    for(k=0; k<numElts-1; k++){
        maxIndex=k;
        for(j=k+1;j<numElts;j++){
            if (a[j].day < a[maxIndex].day || (a[j].day == a[maxIndex].day && a[j].timeSlot < a[maxIndex].timeSlot)){
                maxIndex=j;
            }
        }

        tempday=a[k].day;
        a[k].day=a[maxIndex].day;
        a[maxIndex].day=tempday;
        
        tempslot=a[k].timeSlot;
        a[k].timeSlot=a[maxIndex].timeSlot;
        a[maxIndex].timeSlot=tempslot;
        
        for (k=0; k<a.size(); k++){
            
            if (a[k].day=="A"){
                a[k].day="Monday";
            }
            else if (a[k].day=="B"){
                a[k].day="Tuesday";
            }
            else if (a[k].day=="C"){
                a[k].day="Wednesday";
            }
            else if (a[k].day=="D"){
                a[k].day="Thursday";
            }
            else if (a[k].day=="F"){
                a[k].day="Friday";
            }
            
        }
        
        for (k=0; k<a.size(); k++){
            
            if (a[k].timeSlot=="A"){
                a[k].timeSlot="morning";
            }
            else if (a[k].timeSlot=="B"){
                a[k].timeSlot="afternoon";
            }
        }
    }
    for (int c=0; c<a.size(); c++){
        cout<< a[c].day<<" "<<a[c].timeSlot<<endl;
    }
}

bool isConflicting(vector <schedule> mysched, course mycourse){
    for(int k=0; k<mysched.size(); k++){
        if (mysched[k].day==mycourse.times[k].day && mysched[k].timeSlot==mycourse.times[k].timeSlot){
            return true;
        }
        
    }
    return false;
}

int main(){
 vector<schedule> mySchedule;
 course myCourse;
 mySchedule.push_back(schedule("Thursday","morning"));
 mySchedule.push_back(schedule("Friday","morning"));
 mySchedule.push_back(schedule("Monday","afternoon"));
 mySchedule.push_back(schedule("Thursday","afternoon"));
 mySchedule.push_back(schedule("Tuesday","afternoon"));
 mySchedule.push_back(schedule("Monday","morning"));
 mySchedule.push_back(schedule("Tuesday","morning"));
 
 cout << "Here is your schedule: " << endl;
 printSchedule(mySchedule);
 cout << "Please enter the course name you want to add: ";
 cin >> myCourse.name;
 schedule s;
 cout << "Enter the first day and time for " << myCourse.name << ": ";
 cin >> s.day >> s.timeSlot;
 myCourse.times.push_back(s);
 cout << "Enter the second day and time for " << myCourse.name << ": ";
 cin >> s.day >> s.timeSlot;
 myCourse.times.push_back(s);
 
 if ( isConflicting(mySchedule, myCourse) )
   cout << myCourse.name << " is conflicting with your schedule!\n";
 else {
   cout << "You can take " << myCourse.name << " as it is not conflicting with your schedule." << endl;
   cout << "Here is your new schedule: " << endl;
   mySchedule.push_back(myCourse.times[0]);
   mySchedule.push_back(myCourse.times[1]);
   printSchedule(mySchedule);
 }
 return 0;
}
