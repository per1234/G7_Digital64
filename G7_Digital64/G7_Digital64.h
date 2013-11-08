/*!
 * @file G7_Digital64.h
 * @author Takuya Urakawa (galileo-7.com)
 * @license MIT Licence
 * 
 * @brief This is library for Galileo-7 I2C 64Digital-IOs "OOMORI" Shield.
 * 
 * 
 * @section HISTORY
 * v1.0 - First release
*/

 /*!
  * @mainpage
  * 
  * ガリレオセブンにて販売中のI2C 64Digital-IOs "大盛り" ShieldのArduino用ライブラリです。<br>
  * I2Cで通信し、それぞれ個別に入出力の指定ができるデジタルIOを64ピン追加します。<br>
  * <br>
  * 詳しくは以下クラスのリファレンスを参照して下さい。
  * - G7_Digital64
 */

#ifndef G7_DIGITAL64_H
#define G7_DIGITAL64_H

#include "Arduino.h"

/*===========================================================================*/
//! IC番号
//! IC番号の代りに使用する定数

#define DIO_A (0)
#define DIO_B (1)
#define DIO_C (2)
#define DIO_D (3)

/*===========================================================================*/

//!	4つのI2C IO Expander ICをコントロールして64本のデジタルIOを追加します
//! @note このシールドを2枚使用したいときは基板上のADDR_SELで選択するアドレスをそれぞれ変えること
//! @note IC番号には DIO_A / DIO_B / DIO_C / DIO_D が使用できます。
class G7_Digital64 {
	public:

		//! コンストラクタ
		//! @param _addr 基板上のADDR_SELで選択したアドレス(0か1)
		G7_Digital64(uint8_t _addr = 0);


		//! 全てのIOを初期化する
		/**
		 *  全てのピンを入力にし、OUTPUTレジスタに0xFFを書き込む
		 *	@attention OUTPUTレジスタには0xFFが書き込まれるのでそのままピンを出力にするとHIGHが出力される
		 */
		void init(void);

		//! CONFIGレジスタに書き込む
		//! 1ポート分のピンの設定を入力か出力に設定する
		/**   
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _data 設定するデータ
		 * @attention 出力に設定した場合、OUTPUTレジスタに指定されている値が即時に反映される
		 */
		void setConfig(uint8_t _ic, uint8_t _port, uint8_t _data);

		//! CONFIGレジスタに書き込む
		//! 全てのピンの設定を入力か出力に設定する
		/**   
		 * @param _ic IC番号
		 * @param _data 設定するデータ [0.1][0.2]...[0.7][1.0]...[1.7]の16ビットで指定
		 * @attention 出力に設定した場合、OUTPUTレジスタに指定されている値が即時に反映される
		 */
		void setConfigAll(uint8_t _ic, uint16_t _data);

		//! INPUT POLARITYレジスタに書き込む
		//! 入力ピンの極性を変更する
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _data 設定するデータ
		 */
		void setPolarity(uint8_t _ic, uint8_t _port, uint8_t _data);

		//! OUTPUTレジスタに直接書き込む
		//! ポート毎に出力を設定する
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _data 設定するデータ
		 */
		void portWrite(uint8_t _ic, uint8_t _port, uint8_t _data);

		//! OUTPUTレジスタに書き込む
		//! 全てのピンの出力を書き込む
		/**   
		 * @param _ic IC番号
		 * @param _data 設定するデータ [0.1][0.2]...[0.7][1.0]...[1.7]の16ビットで指定
		 */
		void portWriteAll(uint8_t _ic, uint16_t _data);

		//! INPUTレジスタを直接読み込む
		//! ポート毎に入力を取得する
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @return 入力の状態 [port.7][port.6]...[port.1][port.0]の8ビット
		 */
		uint8_t portRead(uint8_t _ic, uint8_t _port);

		//! INPUTレジスタを直接読み込む
		//! 入力に指定された全てのピンを読み込む
		/**   
		 * @param _ic IC番号
		 * @return 入力の状態 [0.1][0.2]...[0.7][1.0]...[1.7]の16ビット
		 */
		uint16_t portReadAll(uint8_t _ic);

		//! ピンの設定を入力か出力に設定する
		//! 
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _pin ピン番号(0-8)
		 * @param _value OUTPUT/INPUTの指定
		 */
		void pinMode(uint8_t _ic, uint8_t _port, uint8_t _pin, uint8_t _value);

		//! ピンの設定を入力か出力に設定する
		//! ポートを指定しない
		/**
		 * @param _ic IC番号
		 * @param _pin ピン番号(0-16)
		 * @param _value OUTPUT/INPUTの指定
		 */
	    void pinMode(uint8_t _ic, uint8_t _pin, uint8_t _value);

	    //! HIGH/LOWを指定したピンから出力する
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _pin ピン番号(0-8)
		 * @param _value HIGH/LOWの指定
		 */
		void digitalWrite(uint8_t _ic, uint8_t _port, uint8_t _pin, uint8_t _value);

		//! HIGH/LOWを指定したピンから出力する
		//! _portを指定しない
		/**
		 * @param _ic IC番号
		 * @param _pin ピン番号(0-16)
		 * @param _value HIGH/LOWの指定
		 */
		void digitalWrite(uint8_t _ic, uint8_t _pin, uint8_t _value);

		//! 指定したピンの状態(HIGH/LOW)を取得する
		/**
		 * @param _ic IC番号
		 * @param _port ポート番号(0か1)
		 * @param _pin ピン番号(0-8)
		 * @param _value HIGH/LOWの指定
		 * @return ピンの状態
		 */
		uint8_t digitalRead(uint8_t _ic, uint8_t _port, uint8_t _pin);

		//! 指定したピンの状態(HIGH/LOW)を取得する
		//! _portを指定しない
		/**
		 * @param _ic IC番号
		 * @param _pin ピン番号(0-16)
		 * @return ピンの状態
		 */
		uint8_t digitalRead(uint8_t _ic, uint8_t _pin);


	private:
		uint8_t addr;
		static const uint8_t i2cAddress[2][4];
		uint8_t output[4][2];
		uint8_t config[4][2];

		//! コマンドとデータをi2cで送信する
		inline void i2cSend(uint8_t _addr, uint8_t _cmd, uint8_t _data);

		//! コマンドとデータ2バイトをi2cで送信する
		inline void i2cSend2Bytes(uint8_t _addr, uint8_t _cmd, uint16_t _data);

		//! i2cからデータを2バイト読み込む
		//! @return 成功したら受信した値、失敗した場合はNULL
		inline uint16_t i2cRead2Bytes(uint8_t _addr, uint8_t _cmd);

		//! 0-16のピン番号からポート番号とピン番号(0-8)を計算する
		//! @return ret[0]はポート番号(0-1)、ret[1]はピン番号(0-8)
		inline uint8_t* calcPin(uint8_t _pin);
};

#endif