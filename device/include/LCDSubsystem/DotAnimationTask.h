#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>

class LCDSubsystem;

class DotAnimationTask : private Task
{
public:
    DotAnimationTask(Scheduler &, LCDSubsystem &);
    DotAnimationTask(const DotAnimationTask &) = delete;
    void operator=(const DotAnimationTask &) = delete;

    void start() { 
        currentDots = 0;
        enable(); 
    }
    void stop() { disable(); }

private:
    LCDSubsystem &lcdSubsystem;
    uint8_t currentDots = 0;
    bool Callback() override;    
};