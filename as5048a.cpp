/**
  ******************************************************************************
  * @file     :as5048a.cpp
  * @author   :Jihkadre
  * @brief    :AS5048A(SPI) module driver.
  * @version  :1.1
  *
  ******************************************************************************
  */

#include <as5048a.h>

/**
 * Constructor
 */
AS5048A::AS5048A(SPI_HandleTypeDef *_hspi, GPIO_TypeDef* _ps, uint16_t _cs, uint32_t _timeout){
	cs = _cs;
	ps = _ps;
	hspi = _hspi;
	timeout = _timeout;
}

//************************************************************//
#define SPI_START_COM HAL_GPIO_WritePin(ps, cs, GPIO_PIN_RESET);
#define SPI_STOP_COM HAL_GPIO_WritePin(ps, cs, GPIO_PIN_SET);
//************************************************************//

/*
 *  @brief Close the SPI connection
 */
void AS5048A::close(){
	HAL_SPI_DeInit(hspi);
}

/**
 *  @brief Open the SPI connection
 */
void AS5048A::open(){
	HAL_SPI_Init(hspi);
}

/**
 *  @brief Clear the AS5048A errors
 */
void AS5048A::clear_Errors(void){
	read(REQ_CLEAR_ERROR_FLAG);
}

/**
 *  @brief Request angle data
 */
uint16_t AS5048A::getAngle(void){
	return read(REQ_ANGLE);
}

/**
 *  @brief Calculate angle in degree
 */
float AS5048A::calculateAngle(uint16_t angle){
	return float(angle * (360.0f/16384.0f));
}

/**
 * @brief Read register from sensor
 */
uint16_t AS5048A::read(uint16_t command){

	command |= 0b0100000000000000; // Parity=0 // R-W = R //{0x4000}
	command |= ((uint16_t)calculateParityBit(command)<<15); //Calculate and set parity bit

	SPI_START_COM // Chip Select LOW
	HAL_SPI_TransmitReceive(hspi,(uint8_t *)&command,(uint8_t *)&bytes_R,1,timeout);
	SPI_STOP_COM // Chip Select HIGH

	return bytes_R & 0x3FFF;

}

/*
 * @brief Calculate Parity Bit
 */
uint16_t AS5048A::calculateParityBit(uint16_t command){

	uint8_t x = 0;
	uint8_t i;

	for (i = 0; i < 16; i++)
	{
		if (command & 0b0001)
		{
			x++;
		}
		command >>= 1;
	}
	return x & 0b0001;
}

/*
 * @brief Error Handler
 */
void AS5048A::Error_Handler(void)
{
  while (1){}
}
