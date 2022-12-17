//  mgedikoglu 27779
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <queue>

using namespace std;

int main() {
//  ---------------------
//    READ CONFIG FILE
//  ---------------------
    ifstream config;
    string fileName;
    string configLine;
    
    cout<<"Please enter the process folder name: ";
    cin>>fileName;
    
    string configFile = fileName+"/configuration.txt";
    
    cout<<"When all processes are completed, you can find execution sequence in \""<<fileName<<"/output.txt\".\n";
    config.open(configFile.c_str());
    
    vector <int> conf;
    
    while (getline(config,configLine)){
        stringstream strtoint(configLine);
        int p;
        strtoint >> p ;
        conf.push_back(p);
    }
    config.close();
    int numOfQueues = conf[0], numOfProcesses = conf[1], sizeS = conf[2];
    
//  ---------------------
//   READ PROCESS FILES
//  ---------------------
    
    vector <queue <string>> processes;
    for(int x=1; x<=numOfProcesses; x++){
        queue <string> process;
        string processNumber, proLine;
        string processFileName = fileName + "/p" + to_string(x) + ".txt";
        ifstream pro;
        pro.open(processFileName.c_str());
        while(getline(pro, proLine)){
            process.push(proLine);
        }
        processes.push_back(process);
    }

//  ---------------------
//      CREATE QUEUES
//  ---------------------
    vector <queue <int>> queues;
    for(int x=0; x<numOfQueues ;x++){
        queue <int> q;
        queues.push_back(q);
    }
    
//  ---------------------
//    INITIALIZE QUEUES
//  ---------------------
    
    for(int x=1; x<=numOfProcesses; x++){
        queues[0].push(x);
    }
    
//  ---------------------
//     MAIN ALGORITHM
//  ---------------------
    
    int currentProcessID;
    string operation;
    string location;

    int existsProcesses = numOfProcesses;
    
    ofstream outputFile;
    outputFile.open("sample_run_1/output.txt");
    
    
    while (existsProcesses>0){
        int counterS=0;
        int queueCount=0;
        while(counterS<sizeS && !(existsProcesses==0)){
            while(!queues[queueCount].empty() && counterS<sizeS){
                currentProcessID=queues[queueCount].front();
                queues[queueCount].pop();
                if(processes[currentProcessID-1].front()=="1"){
                    processes[currentProcessID-1].pop();
                    operation="1";
                    counterS++;
//                    TERMINATE
                    if(processes[currentProcessID-1].front()=="-"){
                        processes[currentProcessID-1].pop();
                        operation="E";
                        location = "QX";
                        existsProcesses--;
                        if(existsProcesses==0){
                            outputFile<<operation<<", PC"<<currentProcessID<<", "<<location;
                        }else{
                            outputFile<<operation<<", PC"<<currentProcessID<<", "<<location<<"\n";
                        }
                    }else{
                        queues[queueCount+1].push(currentProcessID);
                        outputFile<<operation<<", PC"<<currentProcessID<<", Q"<<to_string(3-queueCount)<<"\n";
                    }
                }else if(processes[currentProcessID-1].front()=="0"){
                    processes[currentProcessID-1].pop();
                    operation="0";
                    counterS++;
//                    TERMINATE
                    if(processes[currentProcessID-1].front()=="-"){
                        processes[currentProcessID-1].pop();
                        operation="E";
                        location = "QX";
                        existsProcesses--;
                        if(existsProcesses==0){
                            outputFile<<operation<<", PC"<<currentProcessID<<", "<<location;
                        }else{
                            outputFile<<operation<<", PC"<<currentProcessID<<", "<<location<<"\n";
                        }
                    }else{
                        queues[queueCount].push(currentProcessID);
                        outputFile<<operation<<", PC"<<currentProcessID<<", Q"<<to_string(4-queueCount)<<"\n";
                    }
                }
            }
            queueCount++;
        }
        queueCount=1;
        //   MOVE ALL PROCESSES TO HIGHEST PRIORTY QUEUE
        while(!(queues[0].size()==existsProcesses)){
            while(!queues[queueCount].empty() && queueCount<numOfQueues){
                currentProcessID=queues[queueCount].front();
                queues[queueCount].pop();
                queues[0].push(currentProcessID);
                operation="B";
                location="Q4";
                outputFile<<operation<<", PC"<<currentProcessID<<", "<<location<<"\n";
            }
            queueCount++;
        }
        queueCount=0;
    }
    outputFile.close();
    return 0;
}
