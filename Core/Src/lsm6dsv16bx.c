#include "lsm6dsv16bx.h"

#define XYZ_BUFFER_SIZE 64

extern I2C_HandleTypeDef hi2c1;
extern SAI_HandleTypeDef hsai_BlockA1;
extern FlagStatus TdmRxCompleted;

static uint32_t lsm6dsv_RegWrite(uint16_t reg, uint8_t* pData, uint16_t length);
static uint32_t lsm6dsv_RegRead(uint16_t reg, uint8_t* pData, uint16_t length);
static uint32_t lsm6dsv_DataRead(uint8_t* pData, uint16_t length);

void lsm6dsv_Init(void)
{
  uint8_t param[2] = {0x0, };

  param[0] = 0x20;
  lsm6dsv_RegWrite(LSM6DS_CTRL1, param, 1);
  HAL_Delay(10);
  
  param[0] = 0xA3;
  lsm6dsv_RegWrite(LSM6DS_TDM_CFG0, param, 1);
  HAL_Delay(10);
  
  param[0] = 0xE0;
  lsm6dsv_RegWrite(LSM6DS_TDM_CFG1, param, 1);
  HAL_Delay(10);
  
  param[0] = 0x00;
  lsm6dsv_RegWrite(LSM6DS_TDM_CFG2, param, 1);
  HAL_Delay(10);
}

uint32_t lsm6dsv_AccelerationRawGet(int16_t* value)
{
  uint8_t buff[6] = {0x0, };
  uint32_t ret;

  ret = lsm6dsv_DataRead(buff, 3);

  value[0] = (int16_t)buff[1];
  value[0] = (value[0] * 256) + (int16_t)buff[0];
  value[1] = (int16_t)buff[3];
  value[1] = (value[1] * 256) + (int16_t)buff[2];
  value[2] = (int16_t)buff[5];
  value[2] = (value[2] * 256) + (int16_t)buff[4];

  return ret;
}

static uint32_t lsm6dsv_RegWrite(uint16_t reg, uint8_t* pData, uint16_t length)
{
  if (HAL_I2C_Mem_Write(&hi2c1, (LSM6DS_ADDR << 1), reg, I2C_MEMADD_SIZE_8BIT, pData, length, 1000) != HAL_OK){
    return MEMS_ERROR_BUS_FAILURE;
  }
  
  return MEMS_ERROR_NONE;
}

static uint32_t lsm6dsv_RegRead(uint16_t reg, uint8_t* pData, uint16_t length)
{
  if (HAL_I2C_Mem_Read(&hi2c1, (LSM6DS_ADDR << 1), reg, I2C_MEMADD_SIZE_8BIT, pData, length, 1000) != HAL_OK){
    return MEMS_ERROR_BUS_FAILURE;
  }
  
  return MEMS_ERROR_NONE;
}

static uint32_t lsm6dsv_DataRead(uint8_t* pData, uint16_t length)
{
  if (HAL_SAI_Receive(&hsai_BlockA1, pData, length, 100) != HAL_OK){
    return MEMS_ERROR_BUS_FAILURE;
  }

  return MEMS_ERROR_NONE;
}

