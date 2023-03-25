#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>
#include <MD_MAX72xx.h>

class SlidingTask : private Task
{
public:
    SlidingTask(Scheduler &, MD_MAX72XX &);
    SlidingTask(const SlidingTask &) = delete;
    void operator=(const SlidingTask &) = delete;

    void start(uint16_t character);
    void stop();

private:
    MD_MAX72XX &mx;
    struct AnimationData
    {
        uint8_t currentPosition;
        uint8_t character;
    };
    AnimationData animationData;
    bool Callback();
};