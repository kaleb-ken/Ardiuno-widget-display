#include <Arduino.h>

class ClockWidget
{
public:
    void SetUp();
    void GetTime();
    void CurrentTime();
    void DrawClock();
private:
    void tick();
    void formatText();
    int Seconds;
    int Minutes;
    int Hours;
};