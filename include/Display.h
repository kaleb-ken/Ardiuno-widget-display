#include <Arduino.h>

class Display 
{
public:
    void SetUp();
    void Clear();
    void DrawTitle(const String& title);
    // void DrawButton(
    //     int x, int y,
    //     int height, int width,
    //     const String& label);
    // void DrawText(
    //     int x, int y,
    //     const String& text
    // );
    void DrawImage(
        int x, int y,
        const char *FileName
    );
private:
    //static int GetCenter();
};