/**
 * The 'COOL SAA1064 LIB' for arduino
 * An arduino library driving the NXP SAA1064 IC in a comfortable way.
 *
 * SAA1064 saa1064;
 * saa1064.sayCooL( );
 *
 * Some counter methods are called.
 *
 * author:  Christian Scheiblich
 * email:   cscheiblich@gmail.com
 * license: Apache V 2.0, Jan 2004
 * created: 24.01.2014
 * edited:  25.01.2014
 * version: 0.6
 */

/**************************************80**************************************/

#include <Wire.h>    // Wire.h must be included here
#include <SAA1064.h> // enable I2C bus

SAA1064 saa1064;

void setup( ) {

  saa1064.setTest( ); // switch on all segments by SAA1064 internal method
  
  delay( 250 );
  
  saa1064.setDynamic( ); // 4 digits and 12 mA of current (bright)
  
  saa1064.clear( ); // switch all segements off

  delay( 250 );
  
} // setup

void loop( ) {
  
  for( int i = 0; i < 10000; i++ ) {
    
   saa1064.say( i );
   delay( 10 );
  
  } // i
  
  saa1064.byteAll( );
  delay( 1000 );
 
  saa1064.clear( );
  delay( 1000 );
 
} // loop