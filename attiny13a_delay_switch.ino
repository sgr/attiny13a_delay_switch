/*
MIT License

Copyright (c) 2019 Shigeru Fujiwara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include <avr/sleep.h>

#define DELAY_MSEC 1000
#define DURATION_MSEC 50
#define TIMES 2

#define PRR _SFR_IO8(0x25)
#define PRADC 0
#define PRTIM0 1

#define BODCR _SFR_IO8(0x30)
#define BODSE 0
#define BODS 1

#define INPUT_PIN PB1  // 6
#define OUTPUT_PIN PB4 // 3

ISR(INT0_vect){}

void sleep_in()
{
  cli();
  // ADC off
  ACSR |= (1<<ACD);
  ACSR = ADMUX = ADCSRA = 0;

  // 電力削減レジスタ
  PRR = (1<<PRTIM0) | (1<<PRADC);

  // BOD off
  BODCR = (1<<BODS) | (1<<BODSE);
  BODCR = (1<<BODS);
  
  GIMSK |= (1<<INT0);
  sei();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // go to sleep
  sleep_enable();
  sleep_mode();
}

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);

}

void loop() {
  sleep_in();
  if (digitalRead(INPUT_PIN) == LOW) {
    digitalWrite(OUTPUT_PIN, LOW);
    for (int i = 1; i < TIMES; i++) {
      delay(DELAY_MSEC);
      digitalWrite(OUTPUT_PIN, HIGH);
      delay(DURATION_MSEC);
      digitalWrite(OUTPUT_PIN, LOW);
    }
  }
}
