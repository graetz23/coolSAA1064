cool-SAA1064-lib
================

The 'Cool SAA1064 lib' driving the NXP SAA1064 IC
in a comfortable way as an arduino library ...
saa1064.sayCool( );

Necessary wiring for this library:

7-Segment:  a -> SAA1064: P1 and/or  P9 (pin: 10 and/or 15)
7-Segment:  b -> SAA1064: P2 and/or P10 (pin:  9 and/or 16)
7-Segment:  c -> SAA1064: P3 and/or P11 (pin:  8 and/or 17)
7-Segment:  d -> SAA1064: P4 and/or P12 (pin:  7 and/or 18)
7-Segment:  e -> SAA1064: P5 and/or P13 (pin:  6 and/or 19)
7-Segment:  f -> SAA1064: P6 and/or P14 (pin:  5 and/or 20)
7-Segment:  g -> SAA1064: P7 and/or P15 (pin:  4 and/or 21)
7-Segment: dp -> SAA1064: P8 and/or P16 (pin:  3 and/or 22)

            P1/P9
           -------
          |   a   |
   P6/P14 | f   b | P2/P10
          | P7/P15|
           -------
          |   g   |
   P5/P13 | e   c | P3/P11
          |   d   |
           -------. dp P8/P16
            P4/P12

How to calculate a digits is easy due to clean mapping:
a:  2^0 = 1
b:  2^1 = 2
c:  2^2 = 4
d:  2^3 = 8
e:  2^4 = 16
f:  2^5 = 32
g:  2^6 = 64
dp: 2^7 = 128

digit '7': a + b + c  = 1 + 2 + 4 = 7
digit '4': b + c + f + g = 2 + 4 + 32 + 64 = 38
digit 'b': c + d + e + f + g = 4 + 8 + 16 + 32 + 64 = 124
... see '_init( )' method in .cpp file for more!

Pin  1: Wire to ground (should work with IC2 address 0x70 >> 1)
Pin  2: Wire a 2 .. 3 nF capacitor to ground; even 10 nF works
Pin 11: Wire to any NPN-type transistor like N2222; I used: 2N 3704 
Pin 12: VEE - Ground; should be 0 Volts
Pin 13: VCC - 5 Volts
Pin 14: Wire to any NPN-type transistor like N2222; I used: 2N 3704
Pin 23: SDA of I2C bus; I added 1k Ohm pull up resistor to VCC
Pin 24: SCL of I2C bus; I added 1k Ohm pull up resistor to VCC

Control Bytes:
B00000000 - is send to mark that the next byte is a control byte:
B00011000 - all segments on for test, 3 mA segment current - dark
B00101000 - all segments on for test, 6 mA segment current - normal
B01001000 - all segments on for test, 12 mA segment current - bright
B01000110 - static mode on, digit 1, digit 2 on, 12mA segment current
B01000111 - dynamic mode on, digit 1+3, digit 2+4 on, 12mA segment current
