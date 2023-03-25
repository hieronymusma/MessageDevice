#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class WordWrapHandling
{
public:
    WordWrapHandling() = delete;
    WordWrapHandling(const WordWrapHandling&) = delete;
    void operator=(const WordWrapHandling&) = delete;

    static void insertLinebreaksForWordwrap(String&);
    static void fillDisplayRowsArray(const char *&position, char displayRows[4][21]);
};