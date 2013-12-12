#include <Arduino.h>
#include <Wire.h>
#include "WireHelper.h"


/**************************************************************************/
/*!
    @brief  wrapper for initializaion of the Wire library.  This method must
    be called at every entry point to the WireHelper library.
*/
/**************************************************************************/
bool WireHelper::hasBegun;
void WireHelper::maybeBegin()
{
  if(!hasBegun)
  {
    Wire.begin();
    hasBegun = true;
  }
}

/**************************************************************************/
/*!
    @brief  calls write or send, depending on version, abstracting
    the writing process.
*/
/**************************************************************************/
void WireHelper::genericWrite(byte value)
{
  #if ARDUINO >= 100
  Wire.write((uint8_t)value);
  #else
  Wire.send(value);
  #endif
}

/**************************************************************************/
/*!
    @brief  calls read or receive, depending on version, abstracting
    the reading process.
*/
/**************************************************************************/
byte WireHelper::genericRead(void)
{
  #if ARDUINO >= 100
  return Wire.read();
  #else
  return Wire.receive();
  #endif	
}

/**************************************************************************/
/*!
    @brief  write a single byte
*/
/**************************************************************************/
void WireHelper::write(byte deviceAddress, byte reg, byte value)
{
	maybeBegin();
	Wire.beginTransmission(deviceAddress);
	genericWrite(reg);
	genericWrite(value);
	Wire.endTransmission();
}

/**************************************************************************/
/*!
    @brief  read a single byte
*/
/**************************************************************************/
byte WireHelper::read(byte deviceAddress, byte reg)
{
	byte buffer[1];
	read(deviceAddress, reg, 1, buffer);
	return buffer[0];
}

/**************************************************************************/
/*!
    @brief  read an arbitrary number of bytes into the buffer
*/
/**************************************************************************/
int WireHelper::read(byte deviceAddress, byte reg, int nbytes, byte *buffer)
{
	maybeBegin();
	Wire.beginTransmission(deviceAddress);
	genericWrite(reg);
	Wire.endTransmission();

	Wire.requestFrom((int)deviceAddress, nbytes);

	int i;
	while(Wire.available() && i < nbytes)
	{
		buffer[i++] = genericRead();
	}

	return i;
}

/**************************************************************************/
/*!
    @brief  reads big endian unsigned int.  For little endian, use read(nbytes=2)
    and construct the integer yourself (backwards from below).
*/
/**************************************************************************/
uint16_t WireHelper::read16(byte deviceAddress, byte reg)
{
	byte buffer[2];
	read(deviceAddress, reg, 2, buffer);
	return (genericRead() << 8) | genericRead();
}

/**************************************************************************/
/*!
    @brief  reads big endian signed int.  For little endian, use read(nbytes=2)
    and construct the integer yourself.
*/
/**************************************************************************/
int16_t WireHelper::readS16(byte deviceAddress, byte reg)
{
	return (int16_t)read16(deviceAddress, reg);
}
