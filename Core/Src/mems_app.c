#include "mems_app.h"
#include "lsm6dsv16bx.h"

MotionSensorBuffer_t MotionBuffer;

uint32_t MotionSensorProcess(MotionAxes_t* value)
{
  uint32_t ret;
  int16_t rawData[3];
  
  ret = lsm6dsv_AccelerationRawGet(rawData);

  value.x = (rawData[2] * 0.122);
  value.y = (rawData[1] * 0.122);
  value.z = (rawData[0] * 0.122);
 
  return ret;
}

void NanoEdgeAIProcess(uint32_t* inData, uint32_t* outData)
{

}
