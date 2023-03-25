#include <Controller/ButtonTask.h>
#include <Controller/Controller.h>

bool ButtonTask::Callback()
{
    controller.stateMachine.executeButtonPressCheck();
    return true;
}