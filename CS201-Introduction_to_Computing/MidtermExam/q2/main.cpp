#include <iostream>
#include <string>
using namespace std;


int main() {
    int limit, number, sum_limit=0, sum=0, min=INT_MAX, max=INT_MIN, count=0, limit_count=0;
    cout<<"Enter the limit number: ";
    cin>>limit;
    cout<<"Enter sequence of integers: ";
    
    
    while(cin>>number){
        count+=1;
        sum+=number;
        if (number>limit){
            sum_limit+=number;
            limit_count+=1;
        }
        if (number<min){
            min=number;
        }
        if (number>max){
            max=number;
        }
        
    }
    double average=double(sum)/count;
    double average_limit=double(sum_limit)/limit_count;
    
    
    if (count==0){
        cout<<"There is no sequence"<<endl;
    }
    else{
        cout<<"The minimum: "<<min<<endl;
        cout<<"The maximum: "<<max<<endl;
        cout<<"The average: "<<average<<endl;
        
        
        if (limit_count==0){
            cout<<"There are no numbers greater than "<<limit<<endl;
        }
        else{
            cout<<"The average of numbers greater than "<<limit<<" is "<<average_limit<<endl;
        }
    }

    
    return 0;
    
}
