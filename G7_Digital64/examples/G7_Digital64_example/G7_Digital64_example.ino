/*==================================================================
	G7_Digital64 example
==================================================================*/

#include <Wire.h>
#include "G7_Digital64.h"


// 基板上のADDR_SELを1にした場合は
// G7_Digital64 dio(1)とする。
G7_Digital64 dio;

void setup() {
	Serial.begin(9600);

	//I2Cを使用する
	Wire.begin();

	//G7_Digital64の初期化
	dio.init();

	// 入出力を設定する
	
	// ポートで指定
	// setConfig(IC番号, ポート番号, 入出力の指定)
	// 入出力の指定は入力:1,出力:0で8ビットで指定
	dio.setConfig(DIO_A, 0, 0x00); //全て出力
	dio.setConfig(DIO_A, 1, 0x00);
	dio.setConfig(DIO_D, 0, 0xFF);
	dio.setConfig(DIO_D, 1, B10101010);
	// Arduino風にピン毎に指定
	// pinMode(IC番号,ポート番号, ピン番号, (OUTPUT/INPUT))
	dio.pinMode(DIO_B,0, 0,OUTPUT);
	dio.pinMode(DIO_B,0, 1,OUTPUT);
	dio.pinMode(DIO_B,1, 0,INPUT);
	dio.pinMode(DIO_B,1, 1,INPUT);

	// Arduino風にピン毎に指定その2
	// pinMode(IC番号, ピン番号, (OUTPUT/INPUT))
	// この場合、ピン番号は0～15
	dio.pinMode(DIO_C,8,INPUT);
	dio.pinMode(DIO_C,9,INPUT);
	dio.pinMode(DIO_C,10,OUTPUT);
	dio.pinMode(DIO_C,11,OUTPUT);
}

void loop() {

	// 出力に指定されているピンに出力
	// portWrite(IC番号, ポート番号, 出力の指定)
	dio.portWrite(DIO_A, 0, B01010101);
	dio.portWrite(DIO_D, 0, 0xFF); //出力に指定されていないピンは反映されない


	// Arduino風出力
	// digitalWrite(IC番号, ポート番号, ピン番号, (HIGH / LOW))
	dio.digitalWrite(DIO_B, 0, 0, HIGH);
	dio.digitalWrite(DIO_B, 0, 1, LOW);

	// Arduino風出力 その2
	// digitalWrite(IC番号, ピン番号, (HIGH / LOW))
	dio.digitalWrite(DIO_C, 10, HIGH);
	dio.digitalWrite(DIO_C, 11, LOW);

	delay(500);

	// 点滅させる
	dio.portWrite(DIO_A, 0, B10101010);
	dio.digitalWrite(DIO_B, 0, 0, LOW);
	dio.digitalWrite(DIO_B, 0, 1, HIGH);
	dio.digitalWrite(DIO_C, 10, LOW);
	dio.digitalWrite(DIO_C, 11, HIGH);

	// 入力に指定されているピンの状態を得る
	// 入力に指定されていないピンは無意味な値が入っています
	byte inputD = dio.portRead(DIO_D, 0);
	Serial.print("INPUT D :");
	Serial.println(inputD, BIN);

	// DIO_D0の状態をそのままDIO_Aに出力
	dio.portWrite(DIO_A, 1, inputD);

	// Arduino風入力
	// digitalRead(IC番号, ポート番号, ピン番号)
	byte inputB_1_0 = dio.digitalRead(DIO_B, 1, 0);
	byte inputB_1_1 = dio.digitalRead(DIO_B, 1, 1);
	Serial.print("input B[1-0] :");
	Serial.print(inputB_1_0);
	Serial.print("  input B[1-1] :");
	Serial.println(inputB_1_1);

	// Arduino風出力 その2
	// digitalRead(IC番号, ピン番号)
	byte inputC_8 = dio.digitalRead(DIO_C, 8);
	byte inputC_9 = dio.digitalRead(DIO_C, 9);
	Serial.print("input C[8] :");
	Serial.print(inputC_8);
	Serial.print("  input C[9] :");
	Serial.println(inputC_9);
	Serial.println("*******************************************");
	delay(500);
}