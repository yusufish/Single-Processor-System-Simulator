/* @Author
Student Name: Yusuf ŞAHİN
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep() // Deallocating the allocated heap memory allocated by the CPURep class
{
    delete this->mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    if (p != NULL) {
        --(p->remainingTime);
        if (p->remainingTime == 0){ // Checking whether the process is done
            p->endTime = time;
            this->getFinishedProcess()->queue(p); // Pushing the done process to the mFinishedProcess
            return p;
        }
        return NULL;
    }
    return NULL;

}

FIFORep* CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}
