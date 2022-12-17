/*
Mustafa Enes Gedikoglu 27779 
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include "Mgedikoglu_Gedikoglu_MustafaEnes_hw7_DynIntQueue.h"

using namespace std;

HW7DynIntQueue fillingQueue;
HW7DynIntQueue packingQueue;
mutex fillingMutex, packingMutex, coutMutex;
int maximumFill=30; //random number
int maximumPack=30;

/* Begin: code taken from threads16.cpp */
int random_range(const int & min, const int & max)
{
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}
/* End: code taken from threads16.cpp */

void producer(int produceItem[]){
	maximumFill=produceItem[0];
	maximumPack=maximumFill;
	for (int i=0 ; i<produceItem[0]; i++){
		int id=i+1;

		/* Begin: code taken from threads8.cpp */
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
		struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
		localtime_s(ptm, &tt);
		/* End: code taken from threads8.cpp */

		ptm->tm_sec += random_range(produceItem[1], produceItem[2]);
		this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));
			
		fillingMutex.lock();

		fillingQueue.enqueue(id);

		coutMutex.lock();
		cout<<"Producer has enqueued a new box "<<id<<" to filling queue (filling queue size is "<<fillingQueue.getCurrentSize()<< "): "<< put_time(ptm,"%X") << endl;
		coutMutex.unlock();

		fillingMutex.unlock();
	}
}

void filler(int minFiller, int maxFiller, int numFiller){
	while (maximumFill>0){	
		int id = 0;
		
		fillingMutex.lock();
		if(!fillingQueue.isEmpty()){
	
			fillingQueue.dequeue(id);

			coutMutex.lock();
			/* Begin: code taken from threads8.cpp */
			time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
			struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
			localtime_s(ptm, &tt);
			/* End: code taken from threads8.cpp */
			cout<<"Filler "<<numFiller <<" started filling the box "<< id <<" (filling queue size is "<< fillingQueue.getCurrentSize() <<"): "<< put_time(ptm,"%X") << endl;
			coutMutex.unlock();

			fillingMutex.unlock();


			ptm->tm_sec += random_range(minFiller, maxFiller);
			this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));

			coutMutex.lock();
			cout<<"Filler "<< numFiller<<" finished filling the box " <<id << ": "<< put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			

			packingMutex.lock();
			packingQueue.enqueue(id); 
			coutMutex.lock();
			cout<<"Filler "<< numFiller<<" put box " <<id << " into the packeging queue (packageing queue size is "<< packingQueue.getCurrentSize()<<"): "<< put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			packingMutex.unlock();


			maximumFill--;

		}else{
			fillingMutex.unlock();
		}
	}
}

void packager(int minPackage, int maxPackage, int numPackager){
		while (maximumPack>0){	
			int id = 0;
			packingMutex.lock();
			if(!packingQueue.isEmpty()){

				packingQueue.dequeue(id);

				coutMutex.lock();
				/* Begin: code taken from threads8.cpp */
				time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
				struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
				localtime_s(ptm, &tt);
				/* End: code taken from threads8.cpp */
				cout<<"Packager "<< numPackager <<" started packaging the box "<< id <<" (packaging queue size is "<< packingQueue.getCurrentSize()<<"): "<< put_time(ptm,"%X") << endl;
				coutMutex.unlock();

				packingMutex.unlock();

				ptm->tm_sec += random_range(minPackage, maxPackage);
				this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));
			
				coutMutex.lock();
				cout<<"Packager "<< numPackager<<" finished packaging the box " <<id << ": "<< put_time(ptm,"%X") << endl;
				coutMutex.unlock();

				maximumPack--;
			}else{
				packingMutex.unlock();
		}

	}
}

int main(){
    int numItem, minProducer, maxProducer, minFiller, maxFiller, minPackage, maxPackage;
    cout<< "Please enter the total number of items: ";
    cin>>numItem;
    
    cout<< "Please enter the min-max waiting time range of producer:"<<endl;
    cout<<"Min: ";
    cin>>minProducer;
    cout<<"Max: ";
    cin>>maxProducer;
    
    cout<< "Please enter the min-max waiting time range of filler workers:"<<endl;
    cout<<"Min: ";
    cin>>minFiller;
    cout<<"Max: ";
    cin>>maxFiller;
    
    cout<< "Please enter the min-max waiting time range of packager workers:"<<endl;
    cout<<"Min: ";
    cin>>minPackage;
    cout<<"Max: ";
    cin>>maxPackage;

	int produceItem[3]={numItem, minProducer, maxProducer};

	/* Begin: code taken from threads8.cpp */
    time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures
	/* End: code taken from threads8.cpp */

	cout << "Simulation starts " << put_time(ptm,"%X") << endl;  //displaying the time  

	
	thread prodthread(&producer, produceItem);
	thread fillerthread1(&filler, minFiller, maxFiller, 1);
	thread fillerthread2(&filler, minFiller, maxFiller, 2);

	thread packagerthread1(&packager, minPackage, maxPackage, 1);
	thread packagerthread2(&packager, minPackage, maxPackage, 2);

	prodthread.join();
	fillerthread1.join();
	fillerthread2.join();
	packagerthread1.join();
	packagerthread2.join();

	/* Begin: code taken from threads8.cpp and updated */
	tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures
	/* End: code taken from threads8.cpp and updated */

    cout<<"End of the simulation ends: "<< put_time(ptm,"%X") << endl;;
    
    return 0;
}