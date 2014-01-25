/**
 * The 'COOL SAA1064 LIB' for arduino
 * An arduino library driving the NXP SAA1064 IC in a comfortable way.
 *
 * SAA1064 saa1064;
 * saa1064.sayCooL( );
 *
 * author:  Christian Scheiblich
 * email:   cscheiblich@gmail.com
 * license: Apache V 2.0, Jan 2004
 * created: 24.01.2014
 * edited:  25.01.2014
 * version: 0.8
 */

/**************************************80**************************************/
 
#include <Wire.h> // include I2C library not in header
#include "SAA1064.h" // class header file

/**************************************80**************************************/

#if defined(ARDUINO) && ARDUINO >= 100
#define printIIC(args) Wire.write((uint8_t)args)
#define readIIC() Wire.read()
#else
#define printIIC(args) Wire.send(args)
#define readIIC() Wire.receive()
#endif

/**************************************80**************************************/

// Constructor
SAA1064::SAA1064( void ) {

  _init( ); // init all

  Wire.begin( );

} // SAA1064

// Constructor
SAA1064::SAA1064( byte i2cAdress ) {
  
  _init( ); // init all

  _i2cAddress = i2cAdress; // overwrite i2c address set in _init( )
  
  Wire.begin( );
  
} // SAA1064

// Destructor
SAA1064::~SAA1064( void ) {

  if( _arrDigits != 0 )
    delete [ ] _arrDigits; // is allocated in member method _init( )

} // SAA1064

/**************************************80**************************************/

void // set to your own control byte
SAA1064::set( byte controlByte ) {

 _set( controlByte );
 
}  // SAA1064::set

/**************************************80**************************************/

void // switch all segmetns on for testing them with 3 mA
SAA1064::setTest( ) {

 _set( B00011111 );
  
} // SAA1064::setTest

/**************************************80**************************************/

void // set up to a static mode: 2 digits and 21 mA as maximum
SAA1064::setStatic( ) {
  
 _set( B01110110 );

} // SAA1064::setStatic

/**************************************80**************************************/

void // set up to dynamic mode: 4 digits and 21 mA as maximum
SAA1064::setDynamic( ) {
  
 _set( B01110111 );

} // SAA1064::setDynamic

/**************************************80**************************************/
  
void // set to output currents 3 mA
SAA1064::setDark( void ) {

  byte controlByte = _controlByte;
  controlByte = controlByte % B00001000; // isolation of config bytes
  controlByte += B00010000; // add position of 3 mA
  set( controlByte );

} // SAA1064::setDark

/**************************************80**************************************/

void // set to output currents 12 mA
SAA1064::setNormal( void ) {

  byte controlByte = _controlByte;
  controlByte = controlByte % B00001000; // isolation of config bytes
  controlByte += B01000000; // add position of 12 mA
  set( controlByte );

} // SAA1064::setNormal

/**************************************80**************************************/

void //  set to output currents 21 mA
SAA1064::setBright( void ) {

  byte controlByte = _controlByte;
  controlByte = controlByte % B00001000; // isolation of config bytes
  controlByte += B01110000; // add all pos of 3 + 6 + 12 mA
  set( controlByte );

} // SAA1064::setBright
  
/**************************************80**************************************/

void // switch off all segments
SAA1064::clear( ) {

 say( -1, -1, -1, -1 ); // use number methode; -1 is code for blank

} // SAA1064::clear

/**************************************80**************************************/

void  // update display directly by hex number: 0 .. F and -1 is blank
SAA1064::say( int h4, int h3, int h2, int h1 ) {

  byte b4 = 0, b3 = 0, b2 = 0, b1 = 0;
    
  if( h4 < 0 || h4 > _arrDigitsLength ) // secure a valid input of known digits
    b4 = 0; // blank this segment
  else
    b4 = _arrDigits[ h4 ]; // convert to digit to code in bytes

  if( h3 < 0 || h3 > _arrDigitsLength ) // secure a valid input of known digits
    b3 = 0; // blank this segment
  else
    b3 = _arrDigits[ h3 ]; // convert to digit to code in bytes

  if( h2 < 0 || h2 > _arrDigitsLength ) // secure a valid input of known digits
    b2 = 0; // blank this segment
  else
    b2 = _arrDigits[ h2 ]; // convert to digit to code in bytes

  if( h1 < 0 || h1 > _arrDigitsLength ) // secure a valid input of known digits
    b1 = 0; // blank this segment
  else
    b1 = _arrDigits[ h1 ]; // convert to digit to code in bytes

  _say( b4, b3, b2, b1 ); // cast them
  
} // SAA1064::say

/**************************************80**************************************/

void  // update display directly by hex number: 0 .. F and -1 is blank
SAA1064::say( byte b4, byte b3, byte b2, byte b1 ) {

  _say( b4, b3, b2, b1 ); // cast them
  
} // SAA1064::say

/**************************************80**************************************/

void // say byte on single digit: 0, 1, 2 or 3
SAA1064::say( int h, int digit ) {
  
  byte b = 0;

  if( h < 0 || h > _arrDigitsLength ) // secure a valid input of known digits
    b = 0; // blank this segment
  else
    b = _arrDigits[ h ]; // convert to digit to code in bytes
    
  _say( b, digit ); // say digit on chosen position
  
} // SAA1064::say

/**************************************80**************************************/
  
void // say byte on single digit: 0, 1, 2 or 3
SAA1064::say( byte b, int digit ) {

  _say( b, digit );

} // SAA1064::say
  
/**************************************80**************************************/

void // say a number 0 .. 9999 : 42 => 42
SAA1064::say( int number ) {

  int digits[ 4 ]; // allocate memory for split2digit method
  
  _splitNum2Dig( number, digits ); // splt 2 array of digits

 if( digits[ 3 ] == 0 )
   digits[ 3 ] = -1; // library internal code for blanking segement
   
 if( digits[ 2 ] == 0 && number < 100 )
   digits[ 2 ] = -1; // library internal code for blanking segement
   
 if( digits[ 1 ] == 0 && number < 10 )
   digits[ 1 ] = -1; // library internal code for blanking segement
 
  say( digits[ 3 ], digits[ 2 ], digits[ 1 ], digits[ 0 ] );
  
} // SAA1064::say

/**************************************80**************************************/

void // say a number 0 .. 9999 : 42 => 0042
SAA1064::sayByZero( int number ) {

  int digits[ 4 ]; // allocate memory for split2digit method
  
  _splitNum2Dig( number, digits ); // splt 2 array of digits
 
  say( digits[ 3 ], digits[ 2 ], digits[ 1 ], digits[ 0 ] );
 
} // SAA1064::say

/**************************************80**************************************/

void // displays the time
SAA1064::sayTime( int hour, int minute ) {

	int digit1 = 0;
	int digit2 = 0;
	int digit3 = 0;
	int digit4 = 0;

	if( minute < 10 ) {
		
		digit1 = minute;
		digit2 = 0;
	
	} else {
	
		digit1 = minute % 10; // mod
		digit2 = minute / 10; // div
	
	} // if
	
	if( hour < 10 ) {
		
		digit3 = hour;
		digit4 = 0;
	
	} else {
	
	  digit3 = hour % 10; // mod
		digit4 = hour / 10; // div
		
	} // if
	
	say( digit4, digit3, digit2, digit1 );
	
} // SAA1064::sayTime

/**************************************80**************************************/

void // displays the date
SAA1064::sayDate( int day, int month ) {

	sayTime( day, month ); // same method, fliped positions

} // sayDate

/**************************************80**************************************/

void // displays the date
SAA1064::sayDateUS( int day, int month ) {

	sayTime( month, day ); // same method, fliped positions

} // sayDate

/**************************************80**************************************/

void  // say year in four digits
SAA1064::sayYear( int year ) {

	say( year );

} // SAA1064::sayYear

/**************************************80**************************************/

void // displays the word Cool
SAA1064::sayCooL( void ) {

	say( 12, 19, 19, 18 ); // Hex: 12 -> C, and internal codes for more digits

} // SAA1064::sayCooL

/**************************************80**************************************/

void // displays the word OooH
SAA1064::sayOooh( void ) {

	say( 0, 19, 19, 16 ); // Hex: 0 -> O, and internal codes for more digits

} // SAA1064::sayOooh

/**************************************80**************************************/

void // displays the word UuuH
SAA1064::sayUuuh( void ) {

	say( 23, 22, 22, 16 ); // internal codes for more digits

} // SAA1064::sayUuuh

/**************************************80**************************************/

void // displays the word AAAh
SAA1064::sayAAAh( void ) {

	say( 10, 10, 10, 16 ); // internal codes for more digits

} // SAA1064::sayAAAh

/**************************************80**************************************/

void // displays the word Cool
SAA1064::sayHAhA( void ) {

	say( 17, 10, 16, 10 ); // 17 -> H, and internal codes for more digits

} // SAA1064::sayCool

/**************************************80**************************************/

void // displays the word GoLd
SAA1064::sayGoLd( void ) {

	say( 6, 19, 18, 13 ); // 17 -> H, and internal codes for more digits

} // SAA1064::sayGoLd


/**************************************80**************************************/

void // displays the word Poor
SAA1064::sayPoor( void ) {

	say( 20, 19, 19, 21 ); // 17 -> H, and internal codes for more digits

} // SAA1064::sayPoor

/**************************************80**************************************/

void // displays a smiley 8-]
SAA1064::saySmiley( void ) {

  say( (byte)(0), (byte)(127), byte(64), byte(15) );

} // SAA1064::saySmiley

/**************************************80**************************************/
  
void // bytes through all segements by a loop
SAA1064::byteAll( void ) {

	for( int i = 0; i < 253; i++ ) {
	
	  _say( (byte)( i+3 ), (byte)( i+2 ), (byte)( i+1 ), (byte)( i ) );
	  delay( 100 );
	  
	} // i

} // SAA1064::byteAll


void // show the member _arrDigits with stored codes.
SAA1064::sayArrDigits( void ) {

 for( int i = 0; i < _arrDigitsLength; i++ ) {
  
  _say( _arrDigits[ i ], _arrDigits[ i ], _arrDigits[ i ], _arrDigits[ i ] );
   delay( 1000 );
   
  } // i

} // SAA1064::sayArrDigits

/**************************************80**************************************/
/**************************************80**************************************/
/**************************************80**************************************/

void // sets the MAPPING TABLE (number to bytes) FOR the used WIRING
SAA1064::_init( void ) {

  _i2cAddress = 0x70 >> 1; // shifted, due to pin 1 is grounded (VEE) -> 0x70

  _arrDigitsLength = 24; // length of available char for single segment
      
  _arrDigits = new byte[ _arrDigitsLength ]; // dynamic allocation -> del it!
    
	_arrDigits[  0 ] =  63; //  0  : 1+2+4+8+16+32    =  63
	_arrDigits[  1 ] =   6; //  1  :   2+4     	      =   6
	_arrDigits[  2 ] =  91; //  2  : 1+2  +8+16   +64 =  91
	_arrDigits[  3 ] =  79; //  3  : 1+2+4+8      +64 =  79
	_arrDigits[  4 ] = 102; //  4  :   2+4     +32+64 = 102
	_arrDigits[  5 ] = 109; //  5  : 1  +4+8   +32+64 = 109
	_arrDigits[  6 ] = 125; //  6  : 1  +4+8+16+32+64 = 125
	_arrDigits[  7 ] =   7; //  7  : 1+2+4            =   7
	_arrDigits[  8 ] = 127; //  8  : 1+2+4+8+16+32+64 = 127
	_arrDigits[  9 ] = 111; //  9  : 1+2+4+8+  +32+64 = 111
	_arrDigits[ 10 ] = 119; //  A  : 1+2+4  +16+32+64 = 119
	_arrDigits[ 11 ] = 124; //  b  :    +4+8+16+32+64 = 124
	_arrDigits[ 12 ] =  57; //  C  : 1    +8+16+32    =  57
	_arrDigits[ 13 ] =  94; //  d  :   2+4+8+16   +64 =  94
	_arrDigits[ 14 ] = 121; //  E  : 1    +8+16+32+64 = 121
	_arrDigits[ 15 ] = 113; //  F  : 1      +16+32+64 = 113
	_arrDigits[ 16 ] = 116; //  h  :     4  +16+32+64 = 116
	_arrDigits[ 17 ] = 118; //  H  :   2+4  +16+32+64 = 118
	_arrDigits[ 18 ] =  56; //  L  :      +8+16+32    =  56
	_arrDigits[ 19 ] =  92; //  o  :     4+8+16   +64 =  92
	_arrDigits[ 20 ] = 115; //  P  : 1+2    +16+32+64 = 115
	_arrDigits[ 21 ] =  80; //  r  :         16   +64 =  80
	_arrDigits[ 22 ] =  28; //  u  :     4+8+16       =  28
	_arrDigits[ 23 ] =  62; //  U  :   2+4+8+16+32    =  62

} // SAA1064::_init

/**************************************80**************************************/

void // set a control byte and keep it in mind
SAA1064::_set( byte controlByte ) {

  _controlByte = controlByte; // store given control byte to member var
 Wire.beginTransmission( _i2cAddress );
 Wire.write( B00000000 ); // instruction byte: 0 -> next is the control byte
 Wire.write( _controlByte ); // have a look in the data sheet for details
 Wire.endTransmission( );
 
}  // SAA1064::_set

/**************************************80**************************************/

void  // update display directly by bytes
SAA1064::_say( byte b4, byte b3, byte b2, byte b1 ) {

  Wire.beginTransmission( _i2cAddress );   
  Wire.write( B00000001 ); // instruction byte -> RHS digit, 2nd, 3rd, last
  Wire.write( b1 ); // digit 1 (RHS)
  Wire.write( b2 ); // digit 2 
  Wire.write( b3 ); // digit 3 
  Wire.write( b4 ); // digit 4 (LHS)
  Wire.endTransmission( );
  
} // SAA1064::_say

void // say byte on single digit: 1, 2, 3 or 4
SAA1064::_say( byte b, int digit ) {

  if( digit < 0 || digit > 3 )
    digit = 0;

  Wire.beginTransmission( _i2cAddress );   
  Wire.write( (byte)(digit + 1) ); // instruction byte -> 1st, 2nd, 3rd, last
  Wire.write( b ); // digit 4 (LHS)
  Wire.endTransmission( );


} // SAA1064::_say

/**************************************80**************************************/

void // and returns an array of length 4; allocated before !!!
SAA1064::_splitNum2Dig( int number, int* digits ) {

  int thousand = number / 1000; // 1234 -> 1
  int hundred = ( number - ( thousand * 1000 ) ) / 100; // 1234 -> 234 -> 2
  int ten = ( number - ( thousand * 1000 + hundred * 100 ) ) / 10;  // 1234 -> 34 -> 3
  int one = number - ( thousand * 1000 + hundred * 100 + ten * 10 ); // 1234 -> 4
 
  digits[ 3 ] = thousand;
  digits[ 2 ] = hundred;
  digits[ 1 ] = ten;
  digits[ 0 ] = one;
 
} // SAA1064::_splitNum2Dig

