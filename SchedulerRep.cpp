/* @Author
Student Name: Yusuf ŞAHİN
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    // Initializing our visual schedule
    for (int i = 0; i < 3; ++i)
        mpProcessFIFO[i] = new FIFORep();
    
    this->mpRunningProcess = NULL;
    this->pCpuObj = new CPURep();
    this->timeSliceCount = 0;
    this->totalTime = 0;
}
SchedulerRep::~SchedulerRep()
{
    for (int i = 0; i < 3; ++i)
        delete mpProcessFIFO[i];
    delete pCpuObj;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    if (p != NULL){
        if (p->startTime == -1) // Checking whether the initial value of start time is changed
            p->startTime = this->totalTime;
    }
    this->timeSliceCount = 0;
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p) // This function will push the process to proper location of the schedule
{   
    if (p == NULL)
        return;

    string type = p->getProcessType(); // This type of implementation provides less function calls than calling getProcessType() in every check

    if (type == "A")
        this->mpProcessFIFO[0]->queue(p);

    else if (type == "B")
        this->mpProcessFIFO[1]->queue(p);

    else if (type == "C")
        this->mpProcessFIFO[2]->queue(p);
}

ProcessRep* SchedulerRep::popProcess() // This function will pop the proper process to be processed
{
    // These NULL checks whether mpProcessFIFO of a specific index is empty

    if (this->mpProcessFIFO[0]->getHead() != NULL)
        return this->mpProcessFIFO[0]->dequeue();

    else if (this->mpProcessFIFO[1]->getHead() != NULL)
        return this->mpProcessFIFO[1]->dequeue();

    else if (this->mpProcessFIFO[2]->getHead() != NULL)
        return this->mpProcessFIFO[2]->dequeue();

    return NULL;
}

bool SchedulerRep::checkTimeSlice() // This function checks whether Quantum time limitation has been reached
{ 
    if (getRunningProcess() == NULL) // Checking whether the CPU is empty
        return false;

    string type = this->getRunningProcess()->getProcessType(); // This type of implementation provides less function calls than calling getProcessType() in every check

    if (type == "A") {
        if (this->timeSliceCount == 2)
            return true;
    }

    else if (type == "B"){
        if (this->timeSliceCount == 4)
            return true;
    }

    else if (type == "C") {
        if (this->timeSliceCount == 8)
            return true;
    }

    return false;
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
    return this->pCpuObj->runCPU(p, this->totalTime); // Processing the process sent to CPU by decreasing remaining time by 1
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    ProcessRep* process = new ProcessRep(type, id, arrivalTime, processTime); // Creating a new process using given values
    schedule(process);
}

void SchedulerRep::schedule(ProcessRep* p)
{
    if (p != NULL) { // Placing the process to schedule properly
        this->pushProcess(p);
    }

    if (getRunningProcess() == NULL) { 
        this->setRunningProcess(popProcess()); // Assigning new running process
    }

    if (this->checkTimeSlice()) { // The case of reacing Quantum time limitation
        this->pushProcess(getRunningProcess());
        this->setRunningProcess(popProcess());
    }

    if(p != NULL && this->getRunningProcess() != NULL){
        if (getRunningProcess()->getProcessType() > p->getProcessType()) { // The case of priority between the process come from the file and the process already at the CPU
            this->pushProcess(getRunningProcess());
            this->setRunningProcess(popProcess());
        }
    }

    ++(this->totalTime);
    ++(this->timeSliceCount);
    if (sendProcessToCPU(getRunningProcess()) != NULL) { // Checking whether the process on the CPU is done
        this->setRunningProcess(popProcess());
    }
}
