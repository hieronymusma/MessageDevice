#include <LCDSubsystem/WordWrapHandling.h>

void WordWrapHandling::insertLinebreaksForWordwrap(String &string)
{
    uint8_t currentColumn = 1;
    uint32_t wordlength = 0;
    char *character = string.begin();
    while (*character)
    {
        wordlength++;

        if (*character == '\n')
        {
            currentColumn = 1;
            wordlength = 0;
            character++;
            continue;
        }

        if (*character == ' ')
            wordlength = 0;

        if (currentColumn == 20 && character[1] != 0)
        {
            // Check if we need to wordwrap
            char lastCharacterInLine = character[0];
            char nextCharacterInLine = character[1];
            if (lastCharacterInLine != ' ' && lastCharacterInLine != '\n' && nextCharacterInLine != ' ' && nextCharacterInLine != '\n' && wordlength < 20)
            {
                character -= wordlength;
                *character = '\n';
                character++;
                currentColumn = 1;
                wordlength = 0;
                continue;
            }
        }

        currentColumn++;
        if (currentColumn > 20)
            currentColumn = 1;
        character++;
    }
}

void WordWrapHandling::fillDisplayRowsArray(const char *&position, char displayRows[4][21])
{
    // fill array
    for (uint8_t row = 0; row < 4; row++)
    {
        // Don't print spaces at the beginning of the line
        if (*position == ' ')
            position++;

        for (uint8_t column = 0; column < 20; column++)
        {
            if (*position == 0)
            {
                row = 4;
                break;
            }
            if (*position == '\n')
            {
                position++;
                break;
            }
            displayRows[row][column] = *position++;
        }
    }

    if (*position == 0)
        position = nullptr;
}