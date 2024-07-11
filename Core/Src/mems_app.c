#include "mems_app.h"
#include "lsm6dsv16bx.h"

uint32_t counter = 0;
MotionSensorAxes_t AccValue;

uint32_t MotionSensorProcess(void)
{
  uint32_t ret;
  int16_t rawData[3];
  
  ret = lsm6dsv_AccelerationRawGet(rawData);

  AccValue.x = (rawData[2] * 0.122);
  AccValue.y = (rawData[1] * 0.122);
  AccValue.z = (rawData[0] * 0.122);

  return ret;
}
