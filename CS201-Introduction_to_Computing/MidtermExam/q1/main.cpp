#include <iostream>
using namespace std;


void double_order(double a, double b, double c){
    if(a<b && a<c && b<c){
        cout<<a<<" "<<b<<" "<<c<<endl;
    }
    else if(a<b && a<c && c<b){
        cout<<a<<" "<<c<<" "<<b<<endl;
    }
    else if(b<a && b<c && a<c){
        cout<<b<<" "<<a<<" "<<c<<endl;
    }
    else if(b<a && b<c && c<a){
        cout<<b<<" "<<c<<" "<<a<<endl;
    }
    else if(c<a && c<b && a<b){
        cout<<c<<" "<<a<<" "<<b<<endl;
    }
    else if(c<a && c<b && b<a){
        cout<<c<<" "<<b<<" "<<a<<endl;
    }
}



//int main(){
//    int a,b,c;
//    cout<<"Write 3 integers: ";
//    cin>>a>>b>>c;
//    if (a%2==0 && b%2==0 && c%2==1){
//        cout<<"BINGO";
//    }
//    else if (a%2==0 && b%2==1 && c%2==0){
//        cout<<"BINGO";
//    }
//    else if (a%2==1 && b%2==0 && c%2==0){
//        cout<<"BINGO";
//    }
//    return 0;
//}
