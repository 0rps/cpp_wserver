#include "taskscheduler.h"

#include <iostream>

TaskScheduler::TaskScheduler(const std::list<int> &_workersPIds):
    m_workerPIds(_workersPIds)
{

}

TaskScheduler::~TaskScheduler()
{

}

void TaskScheduler::sendSocket(const int fd)
{
    std::cout << "TaskScheduler: sendSocket with fd=" << fd << std::endl;
}
