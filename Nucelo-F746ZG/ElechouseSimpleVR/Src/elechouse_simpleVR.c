/*
 * elechouse_simpleVR.c
 *
 *  Created on: 24 may. 2018
 *      Author: mfnunez
 */


#include "elechouse_simpleVR.h"
#include "usart.h"


uint8_t buffer_out[100];
uint8_t buffer_in [100];



void elechouse_send_message (uint8_t * message, uint8_t len)
{
	HAL_UART_Transmit(Ring_Buffer_UART_VR.huart, message, len, 0xFF);
}


void elechouse_read_message (uint8_t * message, uint32_t * len)
{
	*len = UART_Ring_Buffer_RD(&Ring_Buffer_UART_VR, message);
}









_Bool elechouse_restore_system_settings ()
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x02;
	buffer_out[2] = ELECHOUSE__CMD_CODE__RESTORE_SYSTEM_SETTINGS;
	buffer_out[3] = ELECHOUSE__END;
	uint32_t len = 4;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_restore_system_settings respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__RESTORE_SYSTEM_SETTINGS &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_enable_recognition ()
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x02;
	buffer_out[2] = ELECHOUSE__CMD_CODE__ENABLE_RECOGNITION;
	buffer_out[3] = ELECHOUSE__END;
	uint32_t len = 4;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_enable_recognition respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__ENABLE_RECOGNITION &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_disable_recognition ()
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x02;
	buffer_out[2] = ELECHOUSE__CMD_CODE__DISABLE_RECOGNITION;
	buffer_out[3] = ELECHOUSE__END;
	uint32_t len = 4;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_disable_recognition respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__DISABLE_RECOGNITION &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_group_select (uint8_t group)
{
	// Se comprueba la entrada
	if (group > ELECHOUSE__MAX_GROUPS || group == 0)	return 1;

	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x03;
	buffer_out[2] = ELECHOUSE__CMD_CODE__GROUP_SELECT;
	buffer_out[3] = group;
	buffer_out[4] = ELECHOUSE__END;
	uint32_t len = 5;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_group_select respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__GROUP_SELECT &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_enable_or_disable_startup_info (_Bool enable_disable)
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x03;
	buffer_out[2] = ELECHOUSE__CMD_CODE__ENABLE_DISABLE_STARTUP_INFORMATION;
	buffer_out[3] = (uint8_t) enable_disable;
	buffer_out[4] = ELECHOUSE__END;
	uint32_t len = 5;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_enable_or_disable_startup_info respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__ENABLE_DISABLE_STARTUP_INFORMATION &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_set_threshold_value (uint8_t threshold)
{
	// Se comprueba el nivel
	if (threshold < 0x45)	threshold = 0x45;
	if (threshold > 0x65)	threshold = 0x65;

	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x03;
	buffer_out[2] = ELECHOUSE__CMD_CODE__SET_THRESHOLD_VALUE;
	buffer_out[3] = threshold;
	buffer_out[4] = ELECHOUSE__END;
	uint32_t len = 5;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_set_threshold_value respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__SET_THRESHOLD_VALUE &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[4]==ELECHOUSE__END &&
			len==5)
		return 0;
	else
		return 1;
}


_Bool elechouse_check_system_state (uint8_t * recognition_state, uint8_t * current_group, uint8_t * threshold)
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x02;
	buffer_out[2] = ELECHOUSE__CMD_CODE__CHECK_SYSTEM_STATE;
	buffer_out[3] = ELECHOUSE__END;
	uint32_t len = 4;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_check_system_state respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x06 && buffer_in[2]==ELECHOUSE__CMD_CODE__CHECK_SYSTEM_STATE &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[7]==ELECHOUSE__END &&
			len==8)
	{
		if (buffer_in[4] != 0)	*recognition_state = ELECHOUSE__RECOGNITION_STATE__ENABLE;
		else					*recognition_state = ELECHOUSE__RECOGNITION_STATE__DISABLE;

		*current_group = buffer_in[5];

		*threshold = buffer_in[6];

		return 0;
	}
	else
		return 1;
}


_Bool elechouse_check_version (uint16_t * SW_version, uint8_t * SW_patch, uint16_t * HW_version)
{
	// Se crea el mensaje
	buffer_out[0] = ELECHOUSE__HEAD;
	buffer_out[1] = 0x02;
	buffer_out[2] = ELECHOUSE__CMD_CODE__CHECK_VERSION_INFO;
	buffer_out[3] = ELECHOUSE__END;
	uint32_t len = 4;

	// Se manda
	elechouse_send_message(buffer_out, (uint8_t) len);

	// Se espera a la respuesta
	HAL_Delay(500);

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_check_version respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x08 && buffer_in[2]==ELECHOUSE__CMD_CODE__CHECK_VERSION_INFO &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[9]==ELECHOUSE__END &&
			len==10)
	{
		*SW_version = (buffer_in[4]<<8) | buffer_in[5];

		*SW_patch = buffer_in[6];

		*HW_version = (buffer_in[7]<<8) | buffer_in[8];

		return 0;
	}
	else
		return 1;
}


_Bool elechouse_voice_recognized (uint16_t * index, uint8_t * current_group, uint8_t * score_of_recognition)
{
	uint32_t len;

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_voice_recognized respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x07 && buffer_in[2]==ELECHOUSE__CMD_CODE__VOICE_RECOGNIZED &&
			buffer_in[3]==ELECHOUSE__CMD_CODE__ERROR__NO_ERROR && buffer_in[8]==ELECHOUSE__END &&
			len==9)
	{
		*index = (buffer_in[4]<<8) | buffer_in[5];

		*current_group = buffer_in[6];

		*score_of_recognition = buffer_in[7];

		return 0;
	}
	else
		return 1;
}


_Bool elechouse_error (uint16_t * error_code)
{
	uint32_t len;

	// Se lee el mensaje
	elechouse_read_message(buffer_in, &len);
	/*traza("\n\r elechouse_voice_recognized respuesta: ");
	for (uint8_t i=0; i<len; i++)
	{
		traza(" 0x%X", buffer_in[i]);
	}
	traza(" len = %i", len);*/

	// Se comprueba la respuesta
	if (buffer_in[0]==ELECHOUSE__HEAD && buffer_in[1]==0x03 && buffer_in[2]==ELECHOUSE__CMD_CODE__ERROR__ERROR &&
			buffer_in[4]==ELECHOUSE__END &&
			len==5)
	{
		*error_code = buffer_in[3];

		return 0;
	}
	else
		return 1;
}
