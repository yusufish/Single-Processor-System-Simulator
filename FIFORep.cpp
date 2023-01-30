/* @Author
Student Name: Yusuf ŞAHİN
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpTail = this->mpHead;
}


FIFORep::~FIFORep()
{
    delete this->mpHead;
}

void FIFORep::setHead(ProcessRep* head)
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    if (this->getHead() == NULL){ 
        this->setHead(p);
        this->setTail(p);
    }
    else {
        this->mpTail->setNext(p);
        this->setTail(p);
        this->getTail()->setNext(NULL);
    }
}

ProcessRep* FIFORep::dequeue()
{   
    ProcessRep* temp = NULL;
    if (this->getHead() == this->getTail()) { 
        temp = this->getHead();
        this->setHead(NULL);
        this->setTail(NULL);
    }

    else {
        temp = this->getHead();
        this->setHead(this->mpHead->getNext());
    }
    return temp;
}

ProcessRep* FIFORep::searchID(int id)
{   
    ProcessRep* temp = this->getHead();
    while (temp != NULL && temp->getProcessID() != id)
        temp = temp->getNext();
    return temp;
}

void FIFORep::printFIFO()
{
    ProcessRep* temp = this->getHead();

    if (temp == NULL){
        return;
    }
    
    while (temp != this->getTail()){
        cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
        temp = temp->getNext();
    }
    cout << temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " "; // Printing the tail process's information
}
