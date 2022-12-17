#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "QuadraticProbing.h"
using namespace std;
int ARRAY_SIZE = 4096;

int main( ){

   //    *********************************************
   //    *********************************************
   //    ------------    COMPRESSION   ---------------
   //    *********************************************
   //    *********************************************


   //  *********************
   //  INITIALIZE HASH TABLE
   //  *********************


   HashTable<string> h1(ARRAY_SIZE);

   int idx=0;
   for (int x=0; x<256 ; x++){
       h1.insert(string(1,x));
       idx++;
   }

   char ch;
   string current_str="";

   //  ***************************
   //  OPEN INPUT AND OUTPUT FILES
   //  ***************************

   string compinFile ="compin";
   ifstream compin(compinFile);

   ofstream outputFile;
   outputFile.open("compout");

   //  *********************
   //  COMPRESSION ALGORITHM
   //  *********************

   while(!compin.eof()){ //Loop until end of the file
       compin.get(ch);
       if(!compin.eof()){ //After getting characther check again if it is end of the file
           string pre=current_str;
           current_str = current_str+ch;
           if (h1.isIndexActive(ARRAY_SIZE-1)!=1){
               if(!h1.containss(current_str)){ //If string is not in the hash table add pre to output file and insert current string to hash table
                   outputFile << to_string(h1.contains(pre))<<" ";
                   h1.insert(current_str);
                   current_str=ch;
               }
           }else{
               if(!h1.containss(current_str)){ //If string is not in the hash table add pre to output file and insert current string to hash table
                   outputFile << to_string(h1.contains(pre))<<" ";
                   current_str=ch;
               }
           }
       }
   }
   outputFile << to_string(h1.contains(current_str))<<" ";

   compin.close();


   outputFile.close();
   return 0;
}