/*
 * bit.h
 *
 *  Created on: 2018/10/09
 *      Author: yazhou
 */

#ifndef LIBRARY_API_BIT_H_
#define LIBRARY_API_BIT_H_

#define REG_SET_BIT(reg, bit) do { (reg |= (1 << (bit))); } while (0)
#define REG_CLR_BIT(reg, bit) do { (reg &= ~(1 << (bit))); } while (0)
#define REG_Reverse_BIT(reg, bit)  do { (reg ^= (1 << (bit))); } while (0)
#define REG_GET_BIT(reg, bit) ((reg) & (1<<(bit)))
#endif /* LIBRARY_API_BIT_H_ */
