//
//  main.cpp
//  the2
//
//  Created by Mustafa on 9.11.2020.
//

#include <iostream>
#include <iomanip>
#include "strutils.h"
using namespace std;


bool check_input(string color, float length,float width, float height){
    if (length>0 && width>0 && height>0) {
        
        return true;
    }
    else {
        return false;
    }
}


void checkCubeandDisplay(string color,float length,float width, float height){
    if (length==width && length==height){
        cout<<color<<" cuboid is a cube.";
    }
    else {
        cout<<color<<" cuboid is not a cube.";
    }
}


void display(string color,float area,float volume){
    cout<<"Results for the "<<color<<" cuboid:"<<endl;
    cout<<"Area: "<<area<<endl;
    cout<<"Volume: "<<volume<<endl;
}


void calculator(string color, float length, float width, float height, float & area,float & volume){
    volume=height*width*length;
    area=2*(height*width + width*length + height*length);
    display(color, area, volume);
    checkCubeandDisplay(color, length, width, height);
    cout<<endl<<endl;
}

string compare(string color1,string color2,string metric_type,float metric1,float metric2){
    if (metric1>metric2){
        return color1 + " has the largest " + metric_type +".";
    }
    else if(metric2>metric1){
        return color2 + " has the largest " + metric_type +".";
    }
    else{
        return "Two cuboids have the same " + metric_type +".";
    }
}

int main() {
    string color1, color2;
    float length1, width1, height1, length2, width2, height2, area1, volume1, area2, volume2;
    bool a,b;
    cout.setf(ios::fixed);
    cout.precision(2);
    cout<<"Hello! This program compares two cuboids..."<<endl;
    cout<<"Please enter colors for the two cuboids: ";
    cin>> color1>> color2;
    if(LowerString(color1)!=LowerString(color2)){
        cout<<"Please enter length, width and height of the "<<color1 <<" cuboid: ";
        cin>>length1>> width1>> height1;
        a=check_input(color1, length1, width1, height1);
        if (a==1){
            cout<<"Please enter length, width and height of the "<<color2 <<" cuboid: ";
            cin>> length2>> width2>> height2;
            b=check_input(color2, length2, width2, height2);
            if (b==1){
                calculator(color1, length1, width1, height1, area1, volume1);
                calculator(color2, length2, width2, height2, area2, volume2);
                cout<<"Comparison of the two cuboids:"<<endl;
                cout<<compare(color1, color2, "volume", volume1, volume2)<<endl;
                cout<<compare(color1, color2, "area", area1, area2)<<endl;
            }
            else{
                cout<<"Invalid entry for "<<color2<<" cuboid. Dimensions should be positive real numbers!"<<endl;
                return 0;
            }
        }
        else{
            cout<<"Invalid entry for "<<color1<<" cuboid. Dimensions should be positive real numbers!"<<endl;
            return 0;
        }
    }
    else {
        cout<<"Color names cannot be the same, good bye..."<<endl;
    }
    return 0;
}
