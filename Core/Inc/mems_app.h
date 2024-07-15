#include "main.h"
#include "NanoEdgeAI.h"

#define NUM_BUFFER    5
#define MOTION_DATA_SIZE (DATA_INPUT_USER * AXIS_NUMBER) // X, Y, Z line

typedef struct{
  float x;
  float y;
  float z;
}MotionAxes_t;

typedef enum{
    EMPTY = 0,
    FULL
}BufferStatus_t;

typedef struct{
  float Buf[NUM_BUFFER][MOTION_DATA_SIZE];
  BufferStatus_t status[NUM_BUFFER];
  //BufferStatus_t status;
  uint32_t bufIndex;
  uint32_t dataIndex;
}BufferManager_t;

uint32_t MotionSensorProcess(MotionAxes_t* value, BufferManager_t* buffer);
uint8_t NanoEdgeAIProcess(BufferManager_t* buffer);


