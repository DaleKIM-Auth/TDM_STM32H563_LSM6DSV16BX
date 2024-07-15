#include "mems_app.h"
#include "lsm6dsv16bx.h"
#include "string.h"

BufferManager_t MotionBuffer = {.bufIndex = 0, .dataIndex = 0};

uint32_t MotionSensorProcess(MotionAxes_t* value, BufferManager_t* buffer)
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
	  buffer->status[buffer->bufIndex] = FULL;
    if(buffer->bufIndex >= NUM_BUFFER - 1){
    	buffer->bufIndex = 0;
    } else {
    	buffer->bufIndex++;
    }
  }
  
  return ret;
}

uint8_t oneclass_result = 0;
uint32_t current = 0;

//void NanoEdgeAIProcess(uint32_t* inData, uint32_t* outData, uint32_t size)
uint8_t NanoEdgeAIProcess(BufferManager_t* buffer)
{
  if(buffer->status[current] != EMPTY){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    neai_oneclass(buffer->Buf[current], &oneclass_result);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    buffer->status[current] = EMPTY;
    current++;
    printf("res : %d\n", oneclass_result);
  }
  if(current >= NUM_BUFFER){
    current = 0;
  }

  return oneclass_result;
}
