#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
 
#include <macros.h>

LCD_DISCO_F469NI lcd;

Thread thread1;
Thread thread2;

void txt1_thread()
{
    lcd.SetTextColor(color1);
    lcd.DisplayStringAtLine(line1, (uint8_t *)text1);
    ThisThread::sleep_for(1s);
}
void txt2_thread()
{
    lcd.SetTextColor(color2);
    lcd.DisplayStringAtLine(line1, (uint8_t *)text2);
    ThisThread::sleep_for(1s);
}

int main()
{
    //while (true) {
        thread1.start(txt1_thread);
        thread1.join();
        lcd.Clear(LCD_COLOR_WHITE);
        ThisThread::sleep_for(1s);

        thread2.start(txt2_thread);
        thread2.join();
        lcd.Clear(LCD_COLOR_WHITE);
        ThisThread::sleep_for(2s);
    //}
}