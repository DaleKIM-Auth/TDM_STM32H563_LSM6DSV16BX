#include "mems_app.h"
#include "lsm6dsv16bx.h"
#include "string.h"
#include "Axis.h"
#include "i2s.h"

BufferManager_t MotionBuffer = {.bufIndex = 0, .dataIndex = 0};

void BoardInit(void)
{
  /* Interface initialization */
#ifdef USE_TDM_WITH_SAI
  MX_SAI1_Init();
#else
  MX_I2S1_Init();
#endif

  /* Accelerometer initialization */
  lsm6dsv_Init();
}

#ifdef USE_TDM_WITH_SAI
uint32_t AccelerometerProcess(MotionAxes_t* value, BufferManager_t* buffer)
{
  uint32_t ret;
  int16_t rawData[3];
  
  ret = lsm6dsv_AccelerationRawGet(rawData);

  value->x = (rawData[2] * 0.061);
  value->y = (rawData[1] * 0.061);
  value->z = (rawData[0] * 0.061);
  
  buffer->Buf[buffer->bufIndex][buffer->dataIndex] = value->x;
  buffer->Buf[buffer->bufIndex][buffer->dataIndex + 1] = value->y;
  buffer->Buf[buffer->bufIndex][buffer->dataIndex + 2] = value->z;

  buffer->dataIndex += 3;

  if(buffer->dataIndex >= MOTION_DATA_SIZE - 1){
	  buffer->dataIndex = 0;
	  //buffer->status[buffer->bufIndex] = FULL;
    if(buffer->bufIndex >= NUM_BUFFER - 1){
      buffer->status = FULL;
    	buffer->bufIndex = 0;
    } else {
    	buffer->bufIndex++;
    }
  }
  
  return ret;
}
#else
uint32_t AccelerometerProcess(MotionAxes_t* value, BufferManager_t* buffer)
{
  uint32_t ret;
  int16_t rawData[3];

  ret = lsm6dsv_AccelerationRawGet(rawData);

  value->x = (rawData[2] * 0.061);
  value->y = (rawData[1] * 0.061);
  value->z = (rawData[0] * 0.061);

  buffer->Buf[buffer->dataIndex] = value->x;
  buffer->Buf[buffer->dataIndex + 1] = value->y;
  buffer->Buf[buffer->dataIndex + 2] = value->z;

  buffer->dataIndex += 3;

  if(buffer->dataIndex >= MOTION_DATA_SIZE - 1){
	  buffer->dataIndex = 0;
	  buffer->status = FULL;
  }

  return ret;
}
#endif

uint8_t oneclass_result = 0;
uint32_t current = 0;

#ifdef USE_TDM_WITH_SAI
uint8_t NanoEdgeAIProcess(BufferManager_t* buffer)
{
  uint8_t res[5] = {0x0, };

  if(buffer->status == FULL){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    for(int i = 0; i < NUM_BUFFER; i++){
      neai_oneclass(buffer->Buf[i], &oneclass_result);
      res[i] = oneclass_result;
    }
    buffer->status = EMPTY;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    printf("result: \t");
    for(int i = 0; i < 5; i++){
      printf("res[%d]: %d\t", i, res[i]);
    }
    printf("\n");
  }
  return oneclass_result;
}
#else
uint8_t NanoEdgeAIProcess(BufferManager_t* buffer)
{
  uint8_t res = 0;

  if(buffer->status == FULL){
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    neai_oneclass(buffer->Buf, &oneclass_result);
    res = oneclass_result;
    buffer->status = EMPTY;
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

    printf("res: %d\t", res);
    printf("\n");
  }
  return oneclass_result;
}
#endif
