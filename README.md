WireHelper
==========

Helper Library for I2C communications using Aruino's Wire library.

The WireHelper library abstracts the low level operations of Arduino's Library into simple, intuitive methods.  For instance, reading one byte from a register (0x0F) for the L3G4200D with Wire.h looks like this:

```
Wire.begin();
Wire.beginTransmission(105); // the L3G4200D's I2C Address
Wire.write(0x0F); // the Device ID register
Wire.endTransmission(); 

Wire.requestFrom(105, 1);
return Wire.read();
````

That same operation using WireHelper.h is much shorter:

```
WireHelper::read(105, 0x0f);
```

As of version 0.1, WireHelper provides methods for writing bytes and for reading a byte, byte[], uint16_t, and int16_t.  Other datatypes can be implemented by first reading the byte[] array, then performing the proper bitshifting, etc.  Submit issue requests if you have other commonly used data types you would like to see supported.
