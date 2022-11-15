#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
 
#include <macros.h>

LCD_DISCO_F469NI lcd;

Thread thread1;
Thread thread2;
Thread thread3;

bool txt1visible;
bool txt2visible;
bool txt3visible;

Mutex stdio_mutex;

void txt1_thread()
{
    while (true) {
        stdio_mutex.lock();
        if (!txt1visible) {
            lcd.SetTextColor(color1);
            lcd.DisplayStringAtLine(line1, (uint8_t *)text1);
        }
        else lcd.ClearStringLine(line1);
        stdio_mutex.unlock();
        txt1visible = !txt1visible;
        ThisThread::sleep_for(delay1);
    }
}
void txt2_thread()
{
    while (true) {
        stdio_mutex.lock();
        if (!txt2visible) {
            lcd.SetTextColor(color2);
            lcd.DisplayStringAtLine(line2, (uint8_t *)text2);
        }
        else lcd.ClearStringLine(line2);
        stdio_mutex.unlock();
        txt2visible = !txt2visible;
        ThisThread::sleep_for(delay2);
    }
}
void txt3_thread()
{
    while (true) {
        stdio_mutex.lock();
        if (!txt3visible) {
            lcd.SetTextColor(color3);
            lcd.DisplayStringAtLine(line3, (uint8_t *)text3);
        }
        else lcd.ClearStringLine(line3);
        stdio_mutex.unlock();
        txt3visible = !txt3visible;
        ThisThread::sleep_for(delay3);
    }
}
int main()
{
    txt1visible = false;
    txt2visible = false;
    txt3visible = false;

    thread1.start(txt1_thread);
    thread2.start(txt2_thread);
    thread3.start(txt3_thread);
}

