#include <Arduino.h>

class WireHelper
{
public:
	static void write(byte, byte, byte);
	static byte read(byte, byte);
	static int read(byte, byte, int, byte*);
	static uint16_t read16(byte, byte);
	static int16_t readS16(byte, byte);
private:
	static bool hasBegun;
	static void maybeBegin();
	static byte genericRead();
	static void genericWrite(byte);
};
