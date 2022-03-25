/*
	Made with ImgConv v1.1
	layout: col-major
	format: str
	zigzag: False
*/

#pragma once
#include <avr/pgmspace.h>

const unsigned int logo_width = 9, logo_height = 8, logo_depth = 3;
#define LOGO_ZIGZAG 0
#define LOGO_COLMAJOR 1

static const unsigned char logo[217] PROGMEM = "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x8c\xff\x0\x0\x0\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0\x8c\xff\x0";