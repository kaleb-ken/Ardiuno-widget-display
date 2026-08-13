#include <Arduino.h>
#include <SD.h>

class Tamagotchi
{
public:
    void SetUp();
    void DrawCharacter(
        int x, int y,
        const char *fileName
    );

private:
    uint16_t read16(File f);
    uint32_t read32(File f);
};