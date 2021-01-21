#include "EVMS2.h"

// code for pump and fan to be added after discussion

uint16_t val[2]; // val[0] is brakes angle, val[1] is brakes pressure
void EVMS2_init(void)
{  
    HAL_ADC_Start_DMA(&hadc1,val,2);
}
uint16_t read_brakes_angle_sensor(void)
{
    uint16_t brakes_read=0;
	for(int i=0;i<10;i++)
	{
		brakes_read+=val[0];
	}
	return (brakes_read/10);
}

uint8_t isError(void)
{
    if(HAL_GPIO_ReadPin(BMS_FB_GPIO_Port,BMS_FB_Pin)==1)
    {
        return 1; // error of bms so shutdown must be opened
    }
    if(HAL_GPIO_ReadPin(IMD_RELAY_FB_GPIO_Port,IMD_RELAY_FB_Pin)!= HAL_GPIO_ReadPin(IMD_FB_GPIO_Port,IMD_FB_Pin))
    {
        return 1;  // the imd value doesnt affect its relay so sdc must be opened
    }
    if(HAL_GPIO_ReadPin(BSPD_RELAY_FB_GPIO_Port,BSPD_RELAY_FB_Pin)!= HAL_GPIO_ReadPin(BSPD_FB_GPIO_Port,BSPD_FB_Pin))
    {
        return 1;// bspd value doesnt affect its relay so sdc must be opened
    }

    return 0; // no errors 

}
void loop(void)
{
    if(read_brakes_angle_sensor()>=BRAKES_LIGHT_VALUE) // illuminate the brakes light if brake is pressed
    {
        HAL_GPIO_WritePin(BRAKE_LIGHT_RELAY_GPIO_Port,BRAKE_LIGHT_RELAY_Pin,1);
    }
    else
    {
        HAL_GPIO_WritePin(BRAKE_LIGHT_RELAY_GPIO_Port,BRAKE_LIGHT_RELAY_Pin,0);
    }
    if(isError()==1)
    {
        Error_Action();
    }
}


void Error_Action(void)
{
    //open the shutdown circuit and terminate
    HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,0);
    while(1);
}


