#include <LCDSubsystem/LCDSubsystem.h>
#include <LCDSubsystem/WordWrapHandling.h>

static const char heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
static const char bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};

LCDSubsystem::LCDSubsystem(Scheduler &scheduler) : lcd(0x27, 20, 4), scrollingTask(scheduler, *this), dotAnimationTask(scheduler, *this), fillerTask(scheduler, *this)
{
    lcd.init();
    lcd.begin(20, 4);
    lcd.createChar(1, bell);
    lcd.createChar(2, heart);
    lcd.clear();
}

void LCDSubsystem::print(const String &string, bool enableBacklight)
{
    currentStringToPrint = string;
    startScrolling(enableBacklight);
}

void LCDSubsystem::print(const __FlashStringHelper *string, bool enableBacklight)
{
    currentStringToPrint = string;
    startScrolling(enableBacklight);
}

void LCDSubsystem::dotAnimation(const String &string, bool enableBacklight)
{
    currentStringToPrint = string;
    startDotAnimation(enableBacklight);
}

void LCDSubsystem::dotAnimation(const __FlashStringHelper *string, bool enableBacklight)
{
    currentStringToPrint = string;
    startDotAnimation(enableBacklight);
}

void LCDSubsystem::filler()
{
    stopAllTasks();
    lcd.clear();
    fillerTask.start();
}

void LCDSubsystem::processNewString()
{
    clearPreviousTextArray();
    WordWrapHandling::insertLinebreaksForWordwrap(currentStringToPrint);
    position = nullptr;
    lcd.clear();
}

void LCDSubsystem::clear(bool clearBacklight)
{
    stopAllTasks();
    lcd.clear();
    if (clearBacklight)
        lcd.noBacklight();
    position = nullptr;
    currentStringToPrint.clear();
}

void LCDSubsystem::printNextAndMovePosition()
{
    // Reset to beginning
    if (!position)
        position = currentStringToPrint.c_str();

    char text[4][21] = {0};

    WordWrapHandling::fillDisplayRowsArray(position, text);

    // If we print the same text as before ignore it
    if (strncmp(previousText[0], text[0], 20) == 0 &&
        strncmp(previousText[1], text[1], 20) == 0 &&
        strncmp(previousText[2], text[2], 20) == 0 &&
        strncmp(previousText[3], text[3], 20) == 0)
        return;

    lcd.clear();

    auto printRow = [this, &text](uint8_t row)
    {
        if (text[row][0] == 0)
            return;
        lcd.setCursor(0, row);
        lcd.print(text[row]);
        strncpy(previousText[row], text[row], 20);
    };

    printRow(0);
    printRow(1);
    printRow(2);
    printRow(3);
}

void LCDSubsystem::startScrolling(bool enableBacklight)
{
    stopAllTasks();
    processNewString();
    printNextAndMovePosition();
    lcd.setBacklight(enableBacklight);
    scrollingTask.start();
}

void LCDSubsystem::startDotAnimation(bool enableBacklight)
{
    stopAllTasks();
    processNewString();
    printNextAndMovePosition();
    lcd.setBacklight(enableBacklight);
    dotAnimationTask.start();
}

void LCDSubsystem::stopAllTasks()
{
    scrollingTask.stop();
    dotAnimationTask.stop();
    fillerTask.stop();
}

void LCDSubsystem::clearPreviousTextArray()
{
    memset(previousText[0], 0, 20);
    memset(previousText[1], 0, 20);
    memset(previousText[2], 0, 20);
    memset(previousText[3], 0, 20);
}