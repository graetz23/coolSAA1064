## The coolSAA1064 arduino library

### Introduction ###

The coolSAA1064 arduino library handles the 7 segement Philips / NXP SAA1064 driver.

![coolSAA1064 sent in by some user](coolSAA1064.jpg)

The Philips / NXP SAA1064 drives up to four 7 segment displays via an _i2c_ communication. The 7 segments have to have a common _anode_, otherswise you have to use _a lot_ transistors. Anyway the huge advantage of the SAA1064 is, that it deals with up to 18 V of VCC, still driving a 5 V (max. 5.9 V) level on i2c wires. That allows for driving _large_ 7 segments, that are internally built by four to six LED diodes, and need an break through voltage of about 8 V to 12 V. Top of the line, the SAA1064 can control the current of the segments, and makes diming possible.

### Why

In 2013 / 2014, I experimented with arduino, the real time clock module _DS1307_, and some need for _output_. It looked somehow like this:

![coolSAA1064 sent in by some user](coolSAA1064_breadboard.jpg)

The SAA1064 _was still available_ and satisfied my need for output, but unfortunately there was no library for _an easy way of_ using the SAA1064 available. So I (re-)structured, utilized, and object-oriented my SAA1064 code towards this arduino library implementation.

### Revival

And in 2020 there's again the need for _output_. A friend of mine renovate some _foosball_ (colored Germany vs. Brazil) and built in some _photoelectric barrier_ to detect goals; he asked how to display a seven to one best. I told, I got these SAA1ß64 ICs and some library ready to go ..

![coolSAA1064 sent in by some user](coolSAA1064_PCB_layout.png)

However, ebay _donated_ me several orange 7 segment displays with an _alpha size_ of 2.3 inch (5.842 cm); that's a 7 seg of 6.97 cm x 4.78 cm. That arised the problem how to wire 4 x 9 and 16 resistors, a DIL 24 IC, .. :-|

![coolSAA1064 sent in by some user](coolSAA1064_PCB_top.png)

Anyway, I designed a PCB for the _fossball_, and having still in mind to build that _living room clock_ and that _thermometer display for my home brewery_, and ..

![coolSAA1064 sent in by some user](coolSAA1064_PCB_bottom.png)

### Live

_That's something to be there soon .._

### Examples

**Minimal code:**

```C++
SAA1064 saa1064; // generate an object
saa1064.scollCooLSAA1064( ); // shows functionality
```

### Library Features

The most usable features of the library:

  - select IC's internal test mode switching on all segments,
  - select mode for two or four digits,
  - select the intensity of the segments by dark, normal, bright,
  - select the intensity of the segments by an integer 1 .. 7,
  - display a number by 0 to 9999 as integer; blank not used,
  - display a number by 0000 to 9999 as integer; not blanking,
  - display hex values 0000 to FFFF as integer 0 .. 15,
  - display letters by an interal code 16 .. following,
  - display a digit as integer on a selected segment as update,
  - display a digit as byte on a selected segment as update,
  - display a digit on a selected segment as register update,
  - display four digits seperately as integer or blank by -1,
  - display four digits seperately as bytes,
  - display one of a predefined word; CooL, Foo, bAr, ...,
  - display a predefined smiley; 8-],
  - display the time directly,
  - display the date and the date in US and year,
  - scroll any integer or internal codes by milliseconds per step,
  - scroll time by 'hour-minute-second' from right to left,
  - scroll date by 'day-month-year' from right to left,
  - display an amplitude from right to left by an integer of 0 .. 7,
  - display all possible letters that are stored internal,
  - display all byte coding over all segments; takes time!

### Implementation

All necessary I2C communications are realized by only three methods:

  - \_set( .. ); // set the configuration of SAA1064; once implemented,
  - \_say( .. ); // tell bytes for displaying to SAA1064; two times implemented.

All other methods for communicating are using these two methods.

### Remarks

everything was coded using:

  - [**SAA1064 IC**](https://www.nxp.com/docs/en/application-note/AN264.pdf) from NXP,
  - [**arduino**](https://www.arduino.cc/) project,
  - [**arduino IDE**](https://www.arduino.cc/en/main/software) for _serial debugging_,
  - [**arduino Makefile**](https://github.com/sudar/Arduino-Makefile) for automated building,
  - [**atom**](https://atom.io/) editor,
  - [**Gnome**](https://www.gnome.org/) as window manager,
  - and [**debian**](https://www.debian.org/) GNU/Linux.

have fun :-)

## Change Log

**20200413**
 - In honors to the _discontinued_ SAA1064, rewritten readme, added pictures, ..

**20140215**
 - first stable implementation available.
