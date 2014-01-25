/**
 * The 'COOL SAA1064 LIB' for arduino
 * An arduino library driving the NXP SAA1064 IC in a comfortable way.
 *
 * SAA1064 saa1064;
 * saa1064.sayCooL( );
 *
 * Some Test methods are called.
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

  saa1064.sayCooL( );
  delay( 1000 );
 
  saa1064.sayOooh( );
  delay( 1000 );
 
  saa1064.sayUuuh( );
  delay( 1000 );
 
  saa1064.sayAAAh( );
  delay( 1000 );
 
  saa1064.sayHAhA( );
  delay( 1000 );
  
  saa1064.sayPoor( );
  delay( 1000 );  
  
  saa1064.sayGoLd( );
  delay( 1000 );  
  
  saa1064.sayTime( 5, 7 );
  delay( 1000 );
  
  saa1064.sayTime( 7, 42 );
  delay( 1000 );
  
  saa1064.sayTime( 12, 42 );
  delay( 1000 );
  
  saa1064.sayDate( 7, 1 );
  delay( 1000 );
  
  saa1064.sayDateUS( 7, 1 );
  delay( 1000 );
  
  saa1064.sayYear( 14 );
  delay( 1000 );

  saa1064.sayYear( 2014 );
  delay( 1000 );
  
  saa1064.say( 9 );
  delay( 1000 );
  saa1064.say( 49 );
  delay( 1000 );
  saa1064.say( 249 );
  delay( 1000 );
  saa1064.say( 5249 );
  delay( 1000 );
  
  saa1064.sayByZero( 9 );
  delay( 1000 );
  saa1064.sayByZero( 49 );
  delay( 1000 );
  saa1064.sayByZero( 249 );
  delay( 1000 );
  saa1064.sayByZero( 5249 );
  delay( 1000 );
 
  saa1064.clear( );
  delay( 1000 );
 
} // loop