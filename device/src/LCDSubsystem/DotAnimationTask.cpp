#include <LCDSubsystem/DotAnimationTask.h>
#include <LCDSubsystem/LCDSubsystem.h>

DotAnimationTask::DotAnimationTask(Scheduler &scheduler, LCDSubsystem &lcdSubsystem) : Task(500 * TASK_MILLISECOND, TASK_FOREVER, &scheduler, false), lcdSubsystem(lcdSubsystem) {}

bool DotAnimationTask::Callback()
{
    if (currentDots++ == 0) {
        lcdSubsystem.position = nullptr;
        lcdSubsystem.lcd.clear();
        lcdSubsystem.clearPreviousTextArray();
        lcdSubsystem.printNextAndMovePosition();
        return true;
    }
    if (currentDots > 3)
        currentDots = 0;
    lcdSubsystem.lcd.print(F("."));
    return true;
}