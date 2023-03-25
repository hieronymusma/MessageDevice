#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>

class Controller;

class CallbackTask : public Task
{
public:
    CallbackTask(Scheduler &scheduler, Controller &controller) : Task{0, TASK_ONCE, &scheduler, false}, controller{controller} {}

private:
    Controller &controller;
    bool Callback();
};