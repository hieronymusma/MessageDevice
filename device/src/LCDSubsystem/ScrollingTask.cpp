#include <LCDSubsystem/ScrollingTask.h>
#include <LCDSubsystem/LCDSubsystem.h>

ScrollingTask::ScrollingTask(Scheduler &scheduler, LCDSubsystem &lcdSubsystem) : Task(4 * TASK_SECOND, TASK_FOREVER, &scheduler, false), lcdSubsystem(lcdSubsystem) {}

bool ScrollingTask::Callback() {
    lcdSubsystem.printNextAndMovePosition();
    return true;
}