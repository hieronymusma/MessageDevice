#include <Matrix/PulsatingTask.h>

PulsatingTask::PulsatingTask(Scheduler &scheduler, MD_MAX72XX &mx) : Task{350 * TASK_MILLISECOND, TASK_FOREVER, &scheduler, false}, mx{mx} {}

bool PulsatingTask::Callback()
{
    mx.clear();
    mx.control(MD_MAX72XX::INTENSITY, animationData.oldIntensity);
    mx.setChar(animationData.position, animationData.character);

    animationData.oldIntensity += animationData.delta;

    if (animationData.oldIntensity == 0 || animationData.oldIntensity == PulsatingTask::maxIntenisty)
    {
        animationData.delta = -animationData.delta;
        animationData.position = animationData.position == 6 ? 5 : 6;
    }

    return true;
}

void PulsatingTask::start(const uint16_t character)
{
    animationData = AnimationData();
    animationData.character = character;
    mx.clear();
    enable();
}

void PulsatingTask::stop()
{
    disable();
}