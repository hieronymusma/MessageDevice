#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>

class LCDSubsystem;

class ScrollingTask : private Task
{
public:
    ScrollingTask(Scheduler &, LCDSubsystem &);
    ScrollingTask(const ScrollingTask&) = delete;
    void operator=(const ScrollingTask&) = delete;
    void start() { enableDelayed(); }
    void stop() { disable(); }

private:
    LCDSubsystem &lcdSubsystem;
    bool Callback();
};