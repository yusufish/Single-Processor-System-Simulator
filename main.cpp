/* @Author
Student Name: Yusuf ŞAHİN
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>

// #include "ProcessRep.h"
#include "SchedulerRep.h"
// #include "CPURep.h"
// #include "FIFORep.h"


using namespace std;

typedef struct {
    string type;
    int id, arrivalTime, processTime;
} job;


void read_file(char*, SchedulerRep*);
SchedulerRep* simulate(SchedulerRep*, job*, int*, int);
void printProcess(SchedulerRep* , string);

int main(int argc, char* argv[]) {
	system("clear");

    char* fileName = argv[1]; 

    SchedulerRep* scheduleObj = new SchedulerRep();
    read_file(fileName, scheduleObj);
    
    delete scheduleObj;
    return EXIT_SUCCESS;
}


void read_file(char* fileName, SchedulerRep* scheduleObj)
{

    fstream file;
    file.open(fileName);
    string line, word;

    int initTime = 0;
    job* arrivingJob;

    while (getline(file, line))
    {

        stringstream str_strm(line);
        arrivingJob = new job();
        
        int iCol = 0;
        while (getline(str_strm, word,' ')) 
        {
            switch (iCol)
            { 
            case 0:{
                iCol++;
                arrivingJob->arrivalTime = stoi(word);
                break;
            }
            case 1:{
                iCol++;
                arrivingJob->type = word;
                break;
            }
            case 2:{
                iCol++;
                arrivingJob->id = stoi(word);
                break;
            }
            case 3:{
                iCol++;
                arrivingJob->processTime = stoi(word);
                break;
            }
            default:
                break;
            }
        }
        simulate(scheduleObj, arrivingJob, &initTime, arrivingJob->arrivalTime+1);
        delete arrivingJob;   
        
    }
    file.close();
}

SchedulerRep* simulate(SchedulerRep* scheduleObj ,job* job, int* initialTime, int endTime){
    for (int time = *initialTime; time < endTime; time++)
    {           
        if(job->arrivalTime == time){
            
            if(job->type == "PRINTALL"){
                printProcess(scheduleObj, "all");
                scheduleObj->schedule(NULL);       // send empty process for taking one step in the scheduler
            }
            else{                
                scheduleObj->schedule(job->type, job->id, job->arrivalTime, job->processTime);
            }
        }
        else{
            scheduleObj->schedule(NULL);           // send empty process for taking one step in the scheduler
        }  
           
    }
    *initialTime = endTime;
    return scheduleObj;
}

void printProcess(SchedulerRep* schedulerObj, string type){
    if(type == "all")
    {   
        
        cout<<"RP: ";
        if(schedulerObj->getRunningProcess()!=NULL)
        {
            cout << schedulerObj->getRunningProcess()->getProcessType() << schedulerObj->getRunningProcess()->getProcessID() << " ";
        }
        cout<<"WP: ";
        schedulerObj->getProcessFIFO(0)->printFIFO();
        schedulerObj->getProcessFIFO(1)->printFIFO();
        schedulerObj->getProcessFIFO(2)->printFIFO();
        cout<<"FP: ";
        schedulerObj->pCpuObj->getFinishedProcess()->printFIFO();
        // cout<<endl;
    }
    else{
        cout<<"Invalid type"<<endl;
    }
}

