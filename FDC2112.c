/*
 * FDC2112.c
 *
 *  Created on: Oct 12, 2021
 *      Author: olegp
 */
#include "FDC2112.h"
uint32_t FDCsensor1;
uint32_t FDCsensor2;

void FDC2112_Init(I2C_HandleTypeDef *hi2c, uint8_t i2c_addr, defInitConfigStructFDC *init_struct)
{
	init_struct->i2c_fdc = hi2c;
	init_struct->addr = i2c_addr;
	FDC2112_Set_Configuration(init_struct);
}
uint32_t FDC2112_Get_Value_Chanel_A(defInitConfigStructFDC *init_struct)
{
	uint32_t sensor1 = 0x00;

	uint8_t TXbuffer[1] = {0,};
	uint8_t RXbuffer[8] = {0,};

	TXbuffer[0] = 0x00; //ADDRES_DATA0_REG;
	HAL_I2C_Master_Transmit(init_struct->i2c_fdc, init_struct->addr, (uint8_t*)TXbuffer, 1, 1000);
	HAL_I2C_Master_Receive (init_struct->i2c_fdc, init_struct->addr, (uint8_t*)&RXbuffer[0], 2, 1000);

	TXbuffer[0] = 0x01; //ADDRES_DATA0_REG;
	HAL_I2C_Master_Transmit(init_struct->i2c_fdc, init_struct->addr, (uint8_t*)TXbuffer, 1, 1000);
	HAL_I2C_Master_Receive (init_struct->i2c_fdc, init_struct->addr, (uint8_t*)&RXbuffer[2], 2, 1000);

	sensor1 = 0x00;

	sensor1 |= RXbuffer[0]<<8;
	sensor1 |= RXbuffer[1]<<0;

	return sensor1;
}
uint32_t FDC2112_Get_Value_Chanel_B(defInitConfigStructFDC *init_struct)
{
	uint32_t sensor2 = 0x00;

	uint8_t TXbuffer[1] = {0,};
	uint8_t RXbuffer[8] = {0,};

	TXbuffer[0] = 0x02; //ADDRES_DATA0_REG;
	HAL_I2C_Master_Transmit(init_struct->i2c_fdc, init_struct->addr, (uint8_t*)TXbuffer, 1, 1000);
	HAL_I2C_Master_Receive (init_struct->i2c_fdc, init_struct->addr, (uint8_t*)&RXbuffer[4], 2, 1000);

	TXbuffer[0] = 0x03; //ADDRES_DATA0_REG;
	HAL_I2C_Master_Transmit(init_struct->i2c_fdc, init_struct->addr, (uint8_t*)TXbuffer, 1, 1000);
	HAL_I2C_Master_Receive (init_struct->i2c_fdc, init_struct->addr, (uint8_t*)&RXbuffer[6], 2, 1000);

	sensor2 = 0x00;

	sensor2 |= RXbuffer[0]<<8;
	sensor2 |= RXbuffer[1]<<0;

	return sensor2;
}
void FDC2112_Set_Configuration(defInitConfigStructFDC *init_struct)
{
	FDC2112_Set_Reg(init_struct, FDC2214_DRIVE_CH0, 0xf800);
	FDC2112_Set_Reg(init_struct, 0x1C, 0x600);
	FDC2112_Set_Reg(init_struct, FDC2214_RCOUNT_CH0,0x00FF);
	HAL_Delay(1);
}
void FDC2112_Set_Reg(defInitConfigStructFDC *init_struct, uint8_t read_REG_addr, uint16_t data)
{
	uint8_t TXbuffer[10] = {0,};
	TXbuffer[0] = read_REG_addr;
	TXbuffer[1] = (uint8_t)(data>>8);
	TXbuffer[2] = (uint8_t)data;
	HAL_I2C_Master_Transmit(init_struct->i2c_fdc, init_struct->addr, (uint8_t*) &TXbuffer, 3, 1000);
}
void FDC2112_Eneble_Convertion(defInitConfigStructFDC *init_struct)
{

	FDC2112_Set_Reg(init_struct, FDC2214_CONFIG,    0x1);
}
void FDC2112_Disable_Convertion(defInitConfigStructFDC *init_struct)
{

	FDC2112_Set_Reg(init_struct, FDC2214_CONFIG,    0x2001);
}
EnumReadBitLDC FDC2112_Read_Bit(defInitConfigStructFDC *init_struct, uint8_t read_REG_addr, uint8_t bit_num)
{

}




