/*
 ============================================================================
 Name        : crc8.h
 Date		 : 09.11.2010
 Version     :
 Author      : Vanin Alexey
 Copyright   : Electro Drives Control System
 Description : Header for CRC8 check
 ============================================================================
 */

#ifndef CRC8_H_
#define CRC8_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//	Check crc8 function
int crc8(char * buf, int cnt);
//	For NTP frame
uint8_t crc8_sr (	uint8_t crc, 		/* initialization value */
					uint8_t xor_out, 	/* finalization value */
					uint8_t polinom, 	/* polinom */
					const char *data, 	/* data buffer */
					int len /* size of buffer */
					);

#define CRC_XOR			0x8C	//	CRC XOR base
#define CRC_START		0x00	//	CRC XOR start

uint16_t CRC16( const uint8_t *pucFrame, int usLen);
uint16_t SUM16( const uint8_t *src, int cnt);

#ifdef __cplusplus
}
#endif

#endif /* CRC8_H_ */
