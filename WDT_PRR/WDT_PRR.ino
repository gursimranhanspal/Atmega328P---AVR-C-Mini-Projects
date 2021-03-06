//#include <avr/io.h>
//#include <avr/wdt.h>
//#include <avr/sleep.h>
//
//void powerReductionMode () {
//  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
//  MCUCR = bit (BODS) | bit (BODSE);  // turn on brown-out enable select
//  MCUCR = bit (BODS);
//  sleep_cpu ();
//}
//
//int main () {
//  DDRB |= 0x20;
//  cli ();
//  wdt_reset ();
//  wdt_enable (WDTO_1S);
//  WDTCSR |= 0x40;
//  sei ();
//  powerReductionMode ();
//  while (1){};
//  
//}
//
//ISR (WDT_vect) {
//  PORTB ^= 0x20;
//  wdt_reset ();
//  powerReductionMode ();
//}

#include <avr/io.h>
#include <avr/wdt.h>

void WDTsetup ()
{
  cli ();         // Disable Interrupts
  wdt_reset ();       // Reset WatchDog Timer
  // wdt_enable (WDTO_1S);    // Set WatchDog prescalar for a delay of 1000ms
  // WDTCSR = 0b01000000;     // Set WDIE to enable Interrupt mode
  MCUSR &= 0b11110111;      // Set MCUSR - WDRF to 0 so it doesnt override WDE in WDTCSR
  WDTCSR |= 0b00011000;
  WDTCSR = 0b01000110;     // WDIE = 1, WDP3:0 = 0110, W
  sei ();
}

// void powerReductionMode ()
// {

// }

int main ()
{
  DDRB |= 0b00100000;
  WDTsetup ();
  // powerReductionMode ();
  while (1){};
}

ISR (WDT_vect)
{
  PORTB ^= 0b00100000;
  wdt_reset ();
  // powerReductionMode ();
}
