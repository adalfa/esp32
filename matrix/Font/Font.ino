
#include "WS_Flow.h"

// English: Please note that the brightness of the lamp bead should not be too high, which can easily cause the temperature of the board to rise rapidly, thus damaging the board !!!
// Chinese: 请注意，灯珠亮度不要太高，容易导致板子温度急速上升，从而损坏板子!!! 
char Text[] ="Waveshare ESP32-S3-Matrix Text Testing!";
void setup()
{
  Matrix_Init();
}
void loop() {
  Text_Flow(Text);
  delay(100);
}
