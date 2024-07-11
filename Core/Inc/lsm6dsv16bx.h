/*
 * lsm6dsv16bx.h
 *
 *  Created on: Jul 10, 2024
 *      Author: DALE-DESKTOP
 */
#include "main.h"

#ifndef INC_LSM6DSV16BX_H_
#define INC_LSM6DSV16BX_H_

#define LSM6DS_ADDR 0x6B

/* LSM6DSV16BX register */
#define LSM6DS_CTRL1       0x10
#define LSM6DS_TDM_CFG0    0x6C
#define LSM6DS_TDM_CFG1    0x6D
#define LSM6DS_TDM_CFG2    0x6E

/* LSM6DSV16BX operating status */
#define  MEMS_ERROR_NONE         0x00
#define  MEMS_ERROR_BUS_FAILURE  0x01

void lsm6dsv_Init(void);
uint32_t lsm6dsv_AccelerationRawGet(int16_t* value);
#endif /* INC_LSM6DSV16BX_H_ */
