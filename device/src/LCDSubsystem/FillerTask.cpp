#include <LCDSubsystem/FillerTask.h>
#include <LCDSubsystem/LCDSubsystem.h>
#include <LiquidCrystal_I2C.h>

FillerTask::FillerTask(Scheduler &scheduler, LCDSubsystem &lcdSubsystem) : Task(0, TASK_FOREVER, &scheduler, false), lcdSubsystem(lcdSubsystem) {}

bool FillerTask::Callback()
{
    if (currentDots == 40) {
        lcdSubsystem.lcd.clear();
        currentDots = 0;
        currentIntervall = startIntervall;
        return true;
    }

    lcdSubsystem.lcd.write(1); // See LCDSubsystem::LCDSubsystem
    currentDots++;
    currentIntervall -= 10;
    setInterval(currentIntervall);
    return true;
}