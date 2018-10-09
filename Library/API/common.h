/*
 * common.h
 *
 *  Created on: 2018/10/09
 *      Author: yazhou
 */

#ifndef LIBRARY_API_SERVICE_COMMON_H_
#define LIBRARY_API_SERVICE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//operate bit
#define REG_SET_BIT(reg, bit) do { (reg |= (1 << (bit))); } while (0)
#define REG_CLR_BIT(reg, bit) do { (reg &= ~(1 << (bit))); } while (0)
#define REG_Reverse_BIT(reg, bit)  do { (reg ^= (1 << (bit))); } while (0)
#define REG_GET_BIT(reg, bit) ((reg) & (1<<(bit)))

//swap value
 #define SWAP(a, b) \
(((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

//swap byte
#define BSWAP_8(x)  ((x) & 0xff)
#define BSWAP_16(x) ((BSWAP_8(x) << 8) | BSWAP_8((x) >> 8))
#define BSWAP_32(x) ((BSWAP_16(x) << 16) | BSWAP_16((x) >> 16))
#define BSWAP_64(x) ((BSWAP_32(x) << 32) | BSWAP_32((x) >> 32))

void memoryDump(char *buf,int len);
uint32_t runTimesCounter();

#endif /* LIBRARY_API_SERVICE_COMMON_H_ */
