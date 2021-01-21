#ifndef EVMS2_H
#define EVMS2_H
#include "main.h"

#define BRAKES_LIGHT_VALUE 200
void EVMS2_init(void);
void loop(void);
uint16_t read_brakes_angle_sensor(void);
void Error_action(void);


uint8_t isError(void); // returns one if one of feedbacks doesn't equal the true value

void Error_Action(void);




#endif