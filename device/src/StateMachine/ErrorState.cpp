#include <StateMachine/StateMachine.h>
#include <Controller/Controller.h>

void ErrorState::onEnter(Controller &controller)
{
    firstCall = true;

    if (errorMessage)
    {
        controller.lcd.print(errorMessage);
    }
    else
    {
        controller.lcd.print(F(ERR_MSG("Oooops, an error ocurred... Press any key or wait some seconds...")));
    }
}

State &ErrorState::callback(Controller &controller)
{
    if (firstCall) {
        firstCall = false;
        return *this;
    }

    return InitialState::the();
}

State &ErrorState::buttonPressCheck(Controller &controller)
{
    return InitialState::the();
}

void ErrorState::onExit(Controller &controller)
{
    controller.lcd.clear();
}