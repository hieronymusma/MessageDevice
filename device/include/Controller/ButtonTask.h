#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>

class Controller;

class ButtonTask : public Task
{
public:
    ButtonTask(Scheduler &scheduler, Controller &controller) : Task{250 * TASK_MILLISECOND, TASK_FOREVER, &scheduler, true}, controller{controller} {}

private:
    Controller &controller;
    bool Callback();
};