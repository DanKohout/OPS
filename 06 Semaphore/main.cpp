#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
#include <stack>

#include <macros.h>
#include "mbed.h"

LCD_DISCO_F469NI lcd;
int width;
int height;

Semaphore semaphore(nSpots);
Mutex displayLock;
Mutex stackLock;

stack<int> freeSpots;

Thread cars[nCars];
PARAMS carParams[nCars];
uint32_t colors[] = {color1, color2, color3, color4, color5};

void colorSlot(int spot, int color) {    
    lcd.SetTextColor(color);
    lcd.FillRect(width / nSpots * spot, 0, width / nSpots, height);
}

void car_thread(PARAMS *params)
{
    std::chrono::milliseconds time = std::chrono::milliseconds(params->time);
    while (true) {
        semaphore.acquire();

        stackLock.lock();
        int spot = freeSpots.top();
        freeSpots.pop();
        stackLock.unlock();
        
        displayLock.lock();
        colorSlot(spot, params->color);
        displayLock.unlock();

        ThisThread::sleep_for(time);

        stackLock.lock();
        freeSpots.push(spot);
        stackLock.unlock();

        displayLock.lock();
        colorSlot(spot, colorEmpty);
        displayLock.unlock();

        semaphore.release();

        ThisThread::sleep_for(time);
    }
}

int main(void)
{
    width = lcd.GetXSize();
    height = lcd.GetYSize();

    lcd.SetTextColor(colorEmpty);
    lcd.FillRect(0, 0, width, height);

    for (int i = 0; i < nSpots; i++) {
        freeSpots.push(i);
    }

    for (int i = 0; i < nCars; i++) {
        carParams[i].color = colors[i];
        carParams[i].time = 1000 + i * 1000;
    }

    for (int i = 0; i < nCars; i++) {
        cars[i].start(callback(car_thread, &carParams[i]));
    }
}
