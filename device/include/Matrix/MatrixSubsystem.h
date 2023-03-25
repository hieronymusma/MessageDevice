#pragma once

#include <TaskSchedulerDeclarations.h>
#include <MD_MAX72xx.h>
#include <Matrix/SlidingTask.h>
#include <Matrix/PulsatingTask.h>

class MatrixSubsystem
{
public:
    MatrixSubsystem(Scheduler &scheduler);
    MatrixSubsystem(const MatrixSubsystem&) = delete;
    void operator=(const MatrixSubsystem&) = delete;
    void slidingAnimation(const uint16_t character);
    void pulsatingAnimation(const uint16_t character);
    void draw(const bool leds[64]);
    void clear();

private:
    MD_MAX72XX mx;
    SlidingTask slidingTask;
    PulsatingTask pulsatingTask;
};