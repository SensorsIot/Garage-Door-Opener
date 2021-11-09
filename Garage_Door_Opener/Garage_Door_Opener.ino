/* Creator Andreas Spiess
  9.2.2016
  Revision 8.11.2021
  Clone of a Garage Door Opener using a AD9850 module
  Based on work of https://zissisprojects.wordpress.com/2014/02/10/all-digital-fm-modulation-w-arduino-ad9850/

*/


#include <SPI.h>


#define FREQ 1397970960

bool v[] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

unsigned long entry;

uint32_t tword;    //tuning word
byte W[5] = {0, 0, 0, 0, 0};


void setup()
{
  DDRB  = B10000000;                         //define PORTB PD7 as output, PD7 is pin 7 (FU_UD pin)
  PORTB = B00000000;
  SPI.setDataMode(SPI_MODE0);                // mode 0 seems to be the right one
  SPI.setClockDivider(SPI_CLOCK_DIV2);       // this is pretty fast
  SPI.setBitOrder(LSBFIRST);                 // AD9850 wants LSB first
  SPI.begin();

}

void loop() {
  /*
    for (byte i = 0; i < 80; i++) {
    entry = micros();
    if (v[i])  tword = FREQ + 85900;       //calculating the high freqency tuning word for AD9850
    else  tword = FREQ - 85900;            //calculating the low freqency tuning word for AD9850
    W[0] = (byte) tword;
    W[1] = (byte) (tword >> 8);
    W[2] = (byte) (tword >> 16);           //convert it to bytes
    W[3] = (byte) (tword >> 24);
    W[4] = 0;                              //phase is zero
    //start sending with spi interface
    PORTB = B10000000;
    PORTB = B00000000;                     //pulse FU_UD
    for (int j = 0; j < 5; j++)
    {
      SPI.transfer(W[j]);                 //send the word
    }
    PORTB = B10000000;
    PORTB = B00000000;                    //pulse FU_UD
    while (micros() - entry <500); // wait till 500 uS are gone
    }
  */

  tword = FREQ - 85900;            //calculating the low freqency tuning word for AD9850
  W[0] = (byte) tword;
  W[1] = (byte) (tword >> 8);
  W[2] = (byte) (tword >> 16);           //convert it to bytes
  W[3] = (byte) (tword >> 24);
  W[4] = 0;                              //phase is zero
  //start sending with spi interface
  PORTB = B10000000;
  PORTB = B00000000;                     //pulse FU_UD
  for (int j = 0; j < 5; j++)
  {
    SPI.transfer(W[j]);                 //send the word
  }
  PORTB = B10000000;
  PORTB = B00000000;                    //pulse FU_UD
  while(1);
}
