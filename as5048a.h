/**
  ******************************************************************************
  * @file    :as5048a.h
  * @author  :Jihladre
  * @brief   :Header for as5048.c file.
  *           This file contains the common defines of the application.
  * @version :1.0
  *
  ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
//#include "stm32f4xx_hal.h"

class AS5048A{

	uint16_t cs;
	GPIO_TypeDef* ps;
	SPI_HandleTypeDef* hspi;
	uint32_t timeout;
	uint16_t bytes_R;

	public:

	AS5048A(SPI_HandleTypeDef *_hspi, GPIO_TypeDef* _ps, uint16_t _cs, uint32_t _timeout);

	void close();
	void open();
	void clear_Errors(void);
	uint16_t getAngle(void);
	float calculateAngle(uint16_t angle);
	uint16_t read(uint16_t command);
	uint16_t read_dir_angle(void);

	private:

	uint16_t calculateParityBit(uint16_t command);
	void Error_Handler(void);
	
};


/*****************************************************************************/
const uint16_t REQ_NOP = 0x0000;
const uint16_t REQ_CLEAR_ERROR_FLAG = 0x0001;
const uint16_t REQ_MAGNITUDE = 0x3FFE;
const uint16_t REQ_ANGLE = 0x3FFF;
/*****************************************************************************/


#ifdef __cplusplus
}
#endif
