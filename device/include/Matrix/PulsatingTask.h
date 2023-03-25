#pragma once

#include <TaskSchedulerDeclarationsWithSettings.h>
#include <MD_MAX72xx.h>

class PulsatingTask : private Task
{
public:
    PulsatingTask(Scheduler &, MD_MAX72XX &);
    void start(const uint16_t character);
    void stop();

private:
    MD_MAX72XX &mx;
    bool Callback();

    static const uint8_t maxIntenisty{3};

    struct AnimationData
    {
        uint16_t character;
        uint8_t oldIntensity{0};
        uint8_t delta{1};
        uint8_t position{6};
    };
    AnimationData animationData;
};