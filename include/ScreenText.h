#include <Arduino.h>

class ScreenText 
{
public:
    void SetUp();
    void Clear();
    void DrawTitle(const String& title);
    // void DrawButton(
    //     int x, int y,
    //     int height, int width,
    //     const String& label
    // );
    void DrawText(
        int x, int y,
        const String& text
    );
private:
    //static int GetCenter();
};