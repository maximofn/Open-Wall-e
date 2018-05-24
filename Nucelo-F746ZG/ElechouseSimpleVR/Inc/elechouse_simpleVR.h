/*
 * elechouse_simpleVR.h
 *
 *  Created on: 24 may. 2018
 *      Author: mfnunez
 */

#ifndef ELECHOUSE_SIMPLEVR_H_
#define ELECHOUSE_SIMPLEVR_H_

#include "stm32f7xx_hal.h"



#define ELECHOUSE__HEAD											0xAA
#define ELECHOUSE__END											0x0A

#define ELECHOUSE__CMD_CODE__RESTORE_SYSTEM_SETTINGS			0x00
#define ELECHOUSE__CMD_CODE__ENABLE_RECOGNITION					0x01
#define ELECHOUSE__CMD_CODE__DISABLE_RECOGNITION				0x02
#define ELECHOUSE__CMD_CODE__GROUP_SELECT						0x03
#define ELECHOUSE__CMD_CODE__ENABLE_DISABLE_STARTUP_INFORMATION	0x04
#define ELECHOUSE__CMD_CODE__SET_THRESHOLD_VALUE				0x05
#define ELECHOUSE__CMD_CODE__CHECK_SYSTEM_STATE					0x10
#define ELECHOUSE__CMD_CODE__CHECK_VERSION_INFO					0x11
#define ELECHOUSE__CMD_CODE__PROMPT_ID0A						0x0A
#define ELECHOUSE__CMD_CODE__VOICE_RECOGNIZED					0x0D
#define ELECHOUSE__CMD_CODE__ERROR__NO_ERROR					0x00
#define ELECHOUSE__CMD_CODE__ERROR__ERROR						0xFF


#define ELECHOUSE__MAX_GROUPS	64


#define ELECHOUSE__ENABLE_DISABLE_STARTUP_INFO__ENABLE	1
#define ELECHOUSE__ENABLE_DISABLE_STARTUP_INFO__DISABLE	0

#define ELECHOUSE__RECOGNITION_STATE__ENABLE	1
#define ELECHOUSE__RECOGNITION_STATE__DISABLE	0




void elechouse_send_message (uint8_t * message, uint8_t len);
void elechouse_read_message (uint8_t * message, uint32_t * len);









_Bool elechouse_restore_system_settings ();
_Bool elechouse_enable_recognition ();
_Bool elechouse_disable_recognition ();
_Bool elechouse_group_select (uint8_t group);
_Bool elechouse_enable_or_disable_startup_info (_Bool enable_disable);
_Bool elechouse_set_threshold_value (uint8_t threshold);
_Bool elechouse_check_system_state ();
_Bool elechouse_check_system_state (uint8_t * recognition_state, uint8_t * current_group, uint8_t * threshold);
_Bool elechouse_check_version (uint16_t * SW_version, uint8_t * SW_patch, uint16_t * HW_version);
_Bool elechouse_voice_recognized (uint16_t * index, uint8_t * current_group, uint8_t * score_of_recognition);
_Bool elechouse_error (uint16_t * error_code);



#endif /* ELECHOUSE_SIMPLEVR_H_ */
