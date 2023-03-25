#include <Matrix/SlidingTask.h>

SlidingTask::SlidingTask(Scheduler &scheduler, MD_MAX72XX &mx) : Task(300 * TASK_MILLISECOND, TASK_FOREVER, &scheduler, false), mx(mx) {}

void SlidingTask::start(uint16_t character)
{
    animationData.character = character;
    animationData.currentPosition = 0;
    enable();
}

void SlidingTask::stop()
{
    disable();
}

bool SlidingTask::Callback()
{
    mx.clear();
    mx.setChar(animationData.currentPosition++ % 13, animationData.character);
    return true;
}