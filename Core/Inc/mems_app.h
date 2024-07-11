#include "main.h"

#define bufferMaxSize 256

typedef struct{
  float x;
  float y;
  float z;
}MotionSensorAxes_t;

typedef struct{
  float Buf[bufferMaxSize];
  uint32_t len;
}MotionSensorBuffer_t;



uint32_t MotionSensorProcess(void);


