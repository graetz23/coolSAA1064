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
 * version: 0.86
 */

/**************************************80**************************************/

#include <Wire.h>    // Wire.h must be included here
#include <SAA1064.h> // enable I2C bus

SAA1064 saa1064;

void setup( ) {

  saa1064.setTest( );
  
  delay( 1000 );
  
  saa1064.setDynamic( );
  
  delay( 1000 );

  saa1064.clear( );
  delay( 1000 );
  
} // setup

void loop( ) {

  
  saa1064.setDark( ); // set output currents to 3 mA
  
  for( int i = 0; i < 3; i++ ) {
    
    saa1064.sayCooL( ); // say CooL
    delay( 750 );

    saa1064.say( -1, 5, 10, 10 ); // say _SAA
    delay( 750 );

    saa1064.say( 1064 ); // say 1064
    delay( 750 );
    
    saa1064.saySmiley( ); // say a smiley
    delay( 750 );
    
    if( i == 0 )
      saa1064.setNormal( ); // set output currents to 12 mA
    
    if( i == 1 )
      saa1064.setBright( ); // set output currents to 21 mA
    
  } // i
  
  saa1064.sayOooh( );
  delay( 1000 );
 
  saa1064.sayUuuh( );
  delay( 1000 );
 
  saa1064.sayAAAh( );
  delay( 1000 );
 
  saa1064.sayHAhA( );
  delay( 1000 );
  
  saa1064.sayJAJA( );
  delay( 1000 );  
  
  saa1064.sayFoo( );
  delay( 1000 );  
  
  saa1064.saybAr( );
  delay( 1000 );  
  
  // scroll: 'Cool SAA1064 8-]' from right to left by 250 ms per step
  int arr[ 20 ] = { 12, 21, 21, 19, -1, 5, 10, 10, 1, 0, 6, 4, -1, 8, 26, 27, -1, -1, -1 ,-1 }; // hex + interal codes
  saa1064.scroll( arr, 20, 250 ); // scroll right to left by 250 ms per step
  
  saa1064.say( 815 );
  delay( 1000 );
  saa1064.clear( );
  delay( 1000 );
  
  saa1064.sayByZero( 815 );
  delay( 1000 );
  saa1064.clear( );
  delay( 1000 );
  
  saa1064.say( 0,8,1,5 );
  delay( 1000 );  
  saa1064.clear( );
  delay( 1000 );
  
  saa1064.sayTime( 8, 5 );
  delay( 1000 );
  
  saa1064.sayTime( 8, 15 );
  delay( 1000 );
  
  saa1064.sayTime( 18, 15 );
  delay( 1000 );
  
  saa1064.sayDate( 24, 01 );
  delay( 1000 );
  
  saa1064.sayDateUS( 01, 24 );
  delay( 1000 );
  
  saa1064.sayYear( 14 );
  delay( 1000 );

  saa1064.sayYear( 2014 );
  delay( 1000 );
  
  saa1064.say( 5 );
  delay( 1000 );
  saa1064.say( 15 );
  delay( 1000 );
  saa1064.say( 815 );
  delay( 1000 );
  saa1064.say( 2815 );
  delay( 1000 );
  
  saa1064.sayByZero( 5 );
  delay( 1000 );
  saa1064.sayByZero( 15 );
  delay( 1000 );
  saa1064.sayByZero( 815 );
  delay( 1000 );
  saa1064.sayByZero( 2815 );
  delay( 1000 );
    
  saa1064.clear( );
  saa1064.say( 1, 0 ); // show 1 on 1st digit
  delay( 1000 );
  saa1064.clear( );
  saa1064.say( 2, 1 ); // show 2 on 2nd digit
  delay( 1000 );
  saa1064.clear( );
  saa1064.say( 3, 2 ); // show 3 on 3rd digit
  delay( 1000 );
  saa1064.clear( );
  saa1064.say( 4, 3 ); // show 4 on 4th digit
  delay( 1000 );    

  // say all store digits
  saa1064.sayArrDigits( );
  delay( 1000 );
  
  // use it as an amplitude in levels from 0 to 7
  for( int i = 0; i < 8; i++ ) {
    saa1064.amplitude( i );
    delay( 125 );
  }
  for( int i = 7; i >= 3; i-- ) {
    saa1064.amplitude( i );
    delay( 125 );
  }
  for( int i = 3; i < 6; i++ ) {
    saa1064.amplitude( i );
    delay( 125 );
  }
  for( int i = 5; i >= 0; i-- ) {
    saa1064.amplitude( i );
    delay( 125 );
  }
  
  saa1064.byteAll( );
  delay( 1000 );
  
  for( int i = 0; i < 10000; i++ ) {
    
   saa1064.say( i );
   delay( 10 );
  
  } // i
  
  saa1064.clear( );
  delay( 1000 );
  
} // loop