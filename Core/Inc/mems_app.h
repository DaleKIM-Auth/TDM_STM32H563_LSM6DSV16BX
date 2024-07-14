#include "main.h"

#define NB_BUFFER    5
#define MOTION_DATA_SIZE (1024 * 3) // X, Y, Z line

typedef struct{
  float x;
  float y;
  float z;
}MotionAxes_t;

typedef struct{
  float Buf[NB_BUFFER][MOTION_DATA_SIZE];
  uint32_t len;
}MotionBuffer_t;

uint32_t MotionSensorProcess(MotionAxes_t* value);


