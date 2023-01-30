/* @Author
Student Name: Yusuf ŞAHİN
*/
#ifndef _SCHEDULERREP
#define _SCHEDULERREP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

class SchedulerRep
{
private:
    FIFORep* mpProcessFIFO[3];
    ProcessRep* mpRunningProcess;
     
public:
    CPURep* pCpuObj;
    int timeSliceCount;
    int totalTime;

    SchedulerRep();
    ~SchedulerRep();

    FIFORep* getProcessFIFO(int);
    void setProcessFIFO(FIFORep*, int);
    
    void setRunningProcess(ProcessRep*);
    ProcessRep* getRunningProcess();

    void pushProcess(ProcessRep*);
    ProcessRep* popProcess();
    
    bool checkTimeSlice();
    ProcessRep* sendProcessToCPU(ProcessRep*);
    void schedule(string, int, int, int);    
    void schedule(ProcessRep*);

};

#endif
