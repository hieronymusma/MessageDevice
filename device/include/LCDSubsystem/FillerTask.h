#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>

class LCDSubsystem;

class FillerTask : private Task
{
public:
    FillerTask(Scheduler &, LCDSubsystem &);

    void start()
    {
        currentDots = 0;
        currentIntervall = startIntervall;
        setInterval(currentIntervall);
        enable();
    }
    void stop() { disable(); }

private:
    LCDSubsystem &lcdSubsystem;
    uint8_t currentDots = 0;
    bool Callback();
    unsigned long currentIntervall;
    static const unsigned long startIntervall{500 * TASK_MILLISECOND};
};