#include <Controller/CallbackTask.h>
#include <Controller/Controller.h>

bool CallbackTask::Callback()
{
    controller.stateMachine.executeCallback();
    return true;
}