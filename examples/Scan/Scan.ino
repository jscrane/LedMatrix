#include <SimpleTimer.h> 
#include <LedMatrix.h> 
 
const uint8_t anodes[] = { 9, 14, 15, 16, 17, 18, 10 }; 
const uint8_t gnds[] = { 8, 7, 6, 5, 4, 3, 2 }; 
 
LedMatrix leds(sizeof(anodes), anodes, gnds); 
SimpleTimer timer; 
 
void next() { 
        static uint8_t r, c; 
        leds.clr(r, c); 
        c = leds.next(c); 
        if (c == 0)
                r = leds.next(r);
        leds.set(r, c);
}

void setup() {
        leds.begin();
        leds.set(0, 0);
        timer.setInterval(100, next);
}

void loop() {
        timer.run();
        leds.refresh();
}
