#ifndef _RFI_H_
#define _RFI_H_

#include <stdio.h>

/*

RFI - Raw Flux Image

- Jasper Renow-Clarke 06/03/2018

File header
===========
3 bytes .. "RFI"
JSON file metadata .. {date:"02/03/2018",time:"17:00:00",tracks:80,sides:2,rate:12500000}
* date/time relate to capture and are in "localtime" and is in dd/mm/YYYY format, time is in HH:MM:SS format and is 24hr

Track header
============
JSON track metadata .. {track:0,side:0,rate:12500000,rpm:300,enc:"rle",len:48560}
* rate in samples/sec
* rpm is optional as it may not be known
* enc can be "raw", "rle", or possibly gz
* len refers to encoded data, to allow skipping tracks when seeking
* when more than one side is used, tracks are interlaced, e.g. track 0 side 0, track 0 side 1, track 1 side 0 e.t.c

Track data
==========
RLE encoding
* expects low level first, so if it's not low, then 0x00 first
* runs more than 0xff are (e.g. 0x101) are encoded as [ 0xff 0x00 0x02 ]
* runs are samples between level changes
* multiple rotations should be stored incase of jacket slip or CAV fluctuations

*/

extern void rfi_writeheader(FILE *rfifile, const int tracks, const int sides, const long rate, const unsigned char writeable);
extern void rfi_writetack(FILE *rfifile, const int track, const int side, const float rpm, const char *encoding, const unsigned char *rawtrackdata, const unsigned long rawdatalength);

#endif
