#pragma once

#include <LiquidCrystal_I2C.h>
#include <TaskSchedulerDeclarationsWithSettings.h>
#include <LCDSubsystem/ScrollingTask.h>
#include <LCDSubsystem/DotAnimationTask.h>
#include <LCDSubsystem/FillerTask.h>

class LCDSubsystem
{
    friend ScrollingTask;
    friend DotAnimationTask;
    friend FillerTask;
public:
    LCDSubsystem(Scheduler &);
    LCDSubsystem(const LCDSubsystem &) = delete;
    void operator=(const LCDSubsystem &) = delete;

    void print(const String &string, bool enableBacklight = true);
    void print(const __FlashStringHelper *string, bool enableBacklight = true);
    void dotAnimation(const String &string, bool enableBacklight = true);
    void dotAnimation(const __FlashStringHelper *string, bool enableBacklight = true);
    void filler();
    void clear(bool clearBacklight = true);

private:
    LiquidCrystal_I2C lcd;
    ScrollingTask scrollingTask;
    DotAnimationTask dotAnimationTask;
    FillerTask fillerTask;

    String currentStringToPrint;
    const char *position = nullptr;
    char previousText[4][21]{0};

    bool Callback();
    void printNextAndMovePosition();
    void processNewString();
    void startScrolling(bool enableBacklight);
    void startDotAnimation(bool enableBacklight);
    void stopAllTasks();
    void clearPreviousTextArray();
};