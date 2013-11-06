/**
 * @file G7_Digital64.cpp
 * @author Takuya Urakawa (galileo-7.com)
 * @license MIT Licence
 * 
 * @brief This is a library for Galileo-7 I2C 64Digital-IOs "OOMORI" Shield.
 * 	      Control 64 digital IO via I2C.
 * 
 * @section HISTORY
 * v1.0 - First release
*/

#include <G7_Digital64.h>
#include "Arduino.h"
#include <Wire.h>

//PORT0 Command 
#define PCA9655_REG_INPUT    (0)
#define PCA9655_REG_OUTPUT   (2)
#define PCA9655_REG_POLARITY (4)
#define PCA9655_REG_CONFIG  (6)

const uint8_t G7_Digital64::i2cAddress[2][4] = {{0x20,0x24,0x22,0x26},{0x21,0x25,0x23,0x27}};

// constructor
G7_Digital64::G7_Digital64(uint8_t _addr){
	addr = _addr;
	for(uint8_t i=0;i<4;i++){
		for(uint8_t j=0;j<2;j++){
			config[i][j] = 0xFF;
			output[i][j] = 0xFF;
		}
	}
}

// private methods

inline void G7_Digital64::i2cSend(uint8_t _addr, uint8_t _cmd, uint8_t _data){
	Wire.beginTransmission(i2cAddress[addr][_addr]);
	Wire.write(_cmd);
	Wire.write(_data);
	Wire.endTransmission();
}

inline int16_t G7_Digital64::i2cRead(uint8_t _addr, uint8_t _cmd){
	int16_t ret = -1;
	Wire.beginTransmission(i2cAddress[addr][_addr]);
	Wire.write(_cmd);
	Wire.requestFrom(i2cAddress[addr][_addr], (uint8_t)1);
	if(Wire.available()){
		ret = Wire.read();
	}
	return ret;
}

inline uint8_t* G7_Digital64::calcPin(uint8_t _pin){
	uint8_t ret[2];
	ret[0] = _pin >> 3;
	ret[1] = _pin - (ret[0] << 3);
	return ret;
}


// public methods

void G7_Digital64::init(void){
	for(uint8_t ic=0;ic<4;ic++){
		for(uint8_t port=0;port<2;port++){
			setConfig(ic, port, 0xFF);
			setPolarity(ic, port, 0x00);
			portWrite(ic, port, 0xFF);
		}
	}
}

void G7_Digital64::setConfig(uint8_t _ic, uint8_t _port, uint8_t _data){
	config[_ic][_port] = _data;
	i2cSend(_ic, PCA9655_REG_CONFIG + _port, _data);
}

void G7_Digital64::setPolarity(uint8_t _ic, uint8_t _port, uint8_t _data){
	i2cSend(_ic, PCA9655_REG_POLARITY + _port, _data);
}

void G7_Digital64::portWrite(uint8_t _ic, uint8_t _port, uint8_t _data){
	output[_ic][_port] = _data;
	i2cSend(_ic, PCA9655_REG_OUTPUT + _port, _data);
}

uint16_t G7_Digital64::portRead(uint8_t _ic, uint8_t _port){
	return i2cRead(_ic, PCA9655_REG_INPUT + _port);
}

void G7_Digital64::pinMode(uint8_t _ic, uint8_t _port, uint8_t _pin, uint8_t _value){
	uint8_t tempConfig = config[_ic][_port] & ~((uint8_t)0x01 << _pin);
	tempConfig |= ((_value == 0?1:0) << _pin);
	setConfig(_ic, _port, tempConfig);
}

void G7_Digital64::pinMode(uint8_t _ic, uint8_t _pin, uint8_t _value){
	uint8_t* port = calcPin(_pin);
	pinMode(_ic, port[0], port[1], _value);
}

void G7_Digital64::digitalWrite(uint8_t _ic, uint8_t _port, uint8_t _pin, uint8_t _value){
	uint8_t tempOutput = output[_ic][_port] & ~(0x01 << _pin);
	tempOutput |= (_value << _pin);
	portWrite(_ic, _port, tempOutput);
}

void G7_Digital64::digitalWrite(uint8_t _ic, uint8_t _pin, uint8_t _value){
	uint8_t* port = calcPin(_pin);
	digitalWrite(_ic, port[0], port[1], _value);
}

uint8_t G7_Digital64::digitalRead(uint8_t _ic, uint8_t _port, uint8_t _pin){
	uint16_t tempInput = portRead(_ic, _port);
	if(tempInput == -1) return NULL;
	return (tempInput && (0x01 << _pin));
}

uint8_t G7_Digital64::digitalRead(uint8_t _ic, uint8_t _pin){
	uint8_t* port = calcPin(_pin);
	return digitalRead(_ic, port[0], port[1]);
}