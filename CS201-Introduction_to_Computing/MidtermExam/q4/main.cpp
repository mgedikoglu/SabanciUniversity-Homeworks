#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int sum_of_int(ifstream & input){
    int sum=0;
    char cha;
    while (input.get(cha)) {
        if (isdigit(cha)){
            sum+=int(cha)-48;
        }
    }
    return sum;
}

int main(){
    string filename;
    ifstream input;
    
    cout<<"Please enter a filename: ";
    cin>>filename;
    input.open(filename.c_str());
    
    if (input.fail()) {
        cout<<"Error: File not found!";
        return 0;
    }
    int a = sum_of_int(input);
    cout<<"The sum of digits in "<<filename<<" is "<<a<<endl;

    return 0;
}
