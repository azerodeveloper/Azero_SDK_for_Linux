/**
 * Copyright (c) 2019 SoundAI. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 */

#ifndef SOUNDAI_AZERO_SDK_API_H
#define SOUNDAI_AZERO_SDK_API_H

#ifndef SAI_API
    #if defined(_WIN32) && defined(DLL_EXPORT)
        #define SAI_API __declspec(dllexport)
    #elif defined(_WIN32)
        #define SAI_API __declspec(dllimport)
    #elif defined(__GNUC__) && defined(DLL_EXPORT)
        #define SAI_API __attribute__((visibility("default")))
    #else
        #define SAI_API
    #endif
#endif

#if defined(__cplusplus)
extern "C" 
{
#endif

/**
* Enum type of defined key events.
*/
typedef enum {
	///Volume up key event
	AZERO_KEY_EVT_VOL_UP = 1,
	///Volume down key event
	AZERO_KEY_EVT_VOL_DOWN,
	///Mute mic and speaker key event
	AZERO_KEY_EVT_MUTE_ALL,
	///Mute mic key event
	AZERO_KEY_EVT_MUTE_MIC,
	///Mute speaker key event
	AZERO_KEY_EVT_MUTE_SPEAKER,
	///UnMute mic and speaker key event
	AZERO_KEY_EVT_UNMUTE_ALL,
	///UnMute mic key event
	AZERO_KEY_EVT_UNMUTE_MIC,
	///UnMute speaker key event
	AZERO_KEY_EVT_UNMUTE_SPEAKER,
	///Pause or resume key event
	AZERO_KEY_EVT_TOGGLE_PAUSE,
	///Previous key event
	AZERO_KEY_EVT_PREVIOUS,
	///Next key event
	AZERO_KEY_EVT_NEXT,
	///Start VOIP key event
	AZERO_KEY_EVT_VOIP_START,
	///Stop VOIP key event
	AZERO_KEY_EVT_VOIP_STOP,
	///Config network key event
	AZERO_KEY_EVT_NET_CONFIG,
	///Turn on led key event
	AZERO_KEY_EVT_TOGGLE_LED,
	///Customized key event
	AZERO_KEY_EVT_CUSTOM
}azero_key_event_e;

/**
* Enum type of defined status event for any purpose as led control.
*/

typedef enum {
	///Authentication is ok.
	AZERO_EVT_AUTH_OK,
	///Need authentication.
	AZERO_EVT_AUTH_REQUIRED,
	///Authentication is error.
	AZERO_EVT_AUTH_ERROR,
	///Start to capture audio.  	
	AZERO_EVT_AUDIO_CAPTURE_START,
	///Stop to capture audio.   	
	AZERO_EVT_AUDIO_CAPTURE_STOP,
	///In listening state of a dialog.
	AZERO_EVT_DIALOG_LISTENING,
	///In thinking state of a dialog.  	
	AZERO_EVT_DIALOG_THINKING,
	///In speaking state of a dialog.  	
	AZERO_EVT_DIALOG_SPEAKING,
	///The state that device is expecting audio input in multi-turn dialog.
	AZERO_EVT_DIALOG_EXPECT,
	///In end state of a dialog.  		
	AZERO_EVT_DIALOG_IDLE,
	///In playing state of audio.      	
	AZERO_EVT_AUDIO_PLAYING,
	///In paused state of audio.
	AZERO_EVT_AUDIO_PAUSED,
	///In stop state of audio.
	AZERO_EVT_AUDIO_STOPPED,
	///In end state of audio.		
	AZERO_EVT_AUDIO_FINISHED,
	///Volume is changed.
	AZERO_EVT_VOLUME_CHANGED,
	///Mic is muted.
	AZERO_EVT_MIC_MUTED,
	///Mic is unmuted.
	AZERO_EVT_MIC_UNMUTED,
	///Speaker is muted.
	AZERO_EVT_SPEAKER_MUTED,
	///Speaker is unmuted.
	AZERO_EVT_SPEAKER_UNMUTED,
	///Alerts is set successfully.
	AZERO_EVT_ALERTS_SET_SUCCEEDED,
	///Alerts is set failed.
	AZERO_EVT_ALERTS_SET_FAILED,
	///Alerts is delete successfully.
	AZERO_EVT_ALERTS_DELETE_SUCCEEDED,
	///Alerts is delete failed.
	AZERO_EVT_ALERTS_DELETE_FAILED,
	///Alerts is started.
	AZERO_EVT_ALERTS_STARTED,
	///Alerts is stopped.
	AZERO_EVT_ALERTS_STOPPED,
	///Net config is started.
	AZERO_EVT_NET_CONFIG_STARTED,
	///Net config is stopped.
	AZERO_EVT_NET_CONFIG_STOPPED,
	///Phone Call in idle state
	AZERO_EVT_PHONE_CALL_IDLE,
	///Phone Call in dialling state
	AZERO_EVT_PHONE_CALL_DIALING,
	///Phone Call in outband and ringing state
	AZERO_EVT_PHONE_CALL_OUTBOUND_RINGING,
	///Phone Call in active state, the media is being transmitted between the caller and remote party.
	AZERO_EVT_PHONE_CALL_ACTIVE,
	///The inbound call has been received.
	AZERO_EVT_PHONE_CALL_RECEIVED,
	///Phone Call in inbound ringing state
	AZERO_EVT_PHONE_CALL_INBOUND_RINGING
}azero_status_event_e;

/**
*
* Enum of audio commands, which notify the audio command to application for
* further action.
*/
typedef enum {
	///Audio command play.
	AZERO_AUDIO_CMD_PLAY,
	///Audio command stop.
	AZERO_AUDIO_CMD_STOP,
	///Audio command pause.
	AZERO_AUDIO_CMD_PAUSE,
	///Audio command continue.
	AZERO_AUDIO_CMD_CONTINUE,
	///Audio command switch to another one.
	AZERO_AUDIO_CMD_SWITCH,
	///Audio command to play previous one.
	AZERO_AUDIO_CMD_PREVIOUS,
	///Audio command to play next one.
	AZERO_AUDIO_CMD_NEXT,
	///Audio command to change to single loop play mode.
	AZERO_AUDIO_CMD_SINGLE_LOOP,
	///Audio command to change to list loop play mode.
	AZERO_AUDIO_CMD_LIST_LOOP,
	///Audio command to change to random play mode.
	AZERO_AUDIO_CMD_RANDOM_PLAY,
	///Audio command to stop single loop mode.
	AZERO_AUDIO_CMD_CLOSE_SINGLE_LOOP,
	///Audio command to change to list order play mode.
	AZERO_AUDIO_CMD_LIST_ORDER,
	///Audio command to play the song again.
	AZERO_AUDIO_CMD_SONG_AGAIN,
	///Audio command to forward.
	AZERO_AUDIO_CMD_FORWARD,
	///Audio command to backward.
	AZERO_AUDIO_CMD_BACKWARD
}azero_audio_command_e;

/**
*
* Enum of bluetooth commands.
*/
typedef enum {
	///Close the device bluetooth.
	AZERO_OPERATION_BT_CLOSE,
	///Open the device bluetooth.
	AZERO_OPERATION_BT_OPEN
}azero_operation_bluetooth_e;


/**
*
* Enum of status input into Azero OS.
*/
typedef enum {
	///BT player is playing.
	AZERO_BT_PLAYER_PLAYING,
	///BT player is paused.
	AZERO_BT_PLAYER_PAUSED,
	///BT player is stopped.
	AZERO_BT_PLAYER_STOPPED
}azero_input_status_e;

/**
* The customer and device information input.
*
* @param [in] client_ID The client ID.
* @param [in] product_ID The product ID.
* @param [in] device_SN The device serial number, which is the unique ID of a 
*			  particular device.
*/
SAI_API void azero_set_customer_info(const char *client_ID,
									 const char *product_ID,
									 const char *device_SN);

/**
* Set device and system information.
*
* @param [in] azero_device_info_json The device relevant information in json 
*			  format, an example is listed below:
* @example 
*	{
*	  ///Device info, reserved for future version.
*	  "deviceInfo": "",
*	  ///Application info, a set of application's info, "/r/n" is used to separate
*	  ///infos, each piece info include application name,package name,application
*	  ///life time(ms),application called times,"|" is used to separate them.
*	  "appInfo": "app_name1|pak_name1|1234000|3\r\napp_name2|pak_name2|2234000|5\r\n",
*	  ///MAC address.
*	  "macAddr": "80:12:DC:18:EF:2D",
*	  ///ROM size.
*	  "ROMSize": "256MB",
*	  ///RAM size.
*	  "RAMSize": "128MB",
*	  ///CPU type.
*	  "CPUType": "Amlogic",
*	  ///Operator System version.
*	  "OSVersion": "Linux 4.9.54",
*	  ///Firmware version.
*	  "firmwareVersion": "Azero_R2.0.1.1",
*	  ///Firmware name.
*	  "firmawareName":"SMART_SPEAKER_A113X_REL",
*	  ///VOLTE status, on(1) or off(0)
*	  "VOLTE": "0",
*	  ///Network type.
*	  "netType": "WIFI",
*	  ///Broadband network account.
*	  "netAccount": "A012356789",
*	  ///Telephone number.
*	  "phoneNumber": "13x10005678",
*	  ///Location info, longtitude,latitude,location mode(1:satelite,2:base station,3:WIFI,4:AGPS).
*	  "location": "25.77701556036132,123.52958679200002,1"
*	}
*/
SAI_API void azero_device_sys_info(const char *azero_device_info_json);

/**
* Init the sdk service.
*
* @param [in] cfg_path The path contain the SDK configuration files.
* @return A constant string of version information.
*/
SAI_API int azero_start_service(const char *cfg_path);

/**
* Stop the sdk service and release the corresponding resource.
*/
SAI_API void azero_stop_service(void);

/**
* The callback to get the verification id and code when application bind the device.
*
* @param [in] verification_id The short message verification ID.
* @param [in] verification_code The short message verification code.
*/
SAI_API void azero_register_bind_verification_cb(void(*azero_bind_verification_cb)(
												 const char *verifcation_id,
												 const char *verifcation_code));

/**
* Set SDK in wakeup status then ready to capture audio data for ASR.
*
* @param [in] status  set 1 to wakeup the SDK and 0 to unwakeup it.
* @return 0: successful, -1: failed.
*/
SAI_API int azero_set_wakeup_status(int status);

/**
* Input audio data to Azero SDK, currently only 16k/16bit raw data supported.
*
* @param [in] audio_buf The data buffer bear audio data.
* @param [in] buf_size The audio_buf size.
* @return -1: if failed, the others is successfully. 
*/

SAI_API int azero_audio_data_input(const short int *audio_buf, int buf_size);

/**
* Play audio file by Azero SDK.
*
* @param [in] absolute path of audio file.
* @return -1: if failed, the others is successfully. 
*/

SAI_API int azero_audio_file_play(const char *file_path);

/**
* Send key event to SDK for further action. 
*
* @param [in] key_event The current event input, which will trigger 
* 			  corresponding action in SDK as mute/volume etc.
* @return The result of sending, 0: successful, -1: failed.
*/

SAI_API int azero_send_key_event(azero_key_event_e key_event);

/**
* The callback of status change event,which should be invoked before
* azero_start_sdk_service.
*
* @param [in] status_event The current status event.
*/

SAI_API void azero_register_status_evt_cb(void(*azero_status_evt_cb)(
										 azero_status_event_e status_event));

/**
* The callback to set the system volume.
* 
* @param [in] volume_val The volume should be set, scope is [0~100].
* @return The function pointer of the registered callback.
*/
SAI_API void azero_register_set_volume_cb(int(*azero_set_volume_cb)(
										  int volume_val));

/**
* The callback to get the system volume.
* 
* @return The volume value,which should be in scope of [0~100].
*/
SAI_API void azero_register_get_volume_cb(int(*azero_get_volume_cb)());

/**
* The callback of major audio command for customer controlling.
* Note: which should be invoked before azero_start_sdk_service.
*
* @param [in] audio_command The input audio command.
* 
*/
SAI_API void azero_register_audio_command_cb(void(*azero_audio_command_cb)(
										     azero_audio_command_e audio_command));

/**
* The callback of wakeup and DOA(degree of arrival).
* Note: which should be invoked before azero_start_sdk_service.
*
* @param [in] waken_up The notitifation when waked up,1:waken up, others:no waken up.
* @param [in] waken_doa The DOA of this wakeup,range is [0,360).
*/
SAI_API void azero_register_wakenup_cb(void(*azero_wakenup_cb)(
                                       int waken_up, int waken_doa));

/**
* Start TTS player play for customer input.
*
* @param [in] tts_text The content TXT that customer requeir to play.
*/
SAI_API void azero_play_user_tts(const char * tts_text);

/*The callback of bluetooth open/close processing.
*
* @param [in] bluetooth_action The action towards bluetooth.
*
* @return The result of process, 0: successful, -1: failed.
*/

SAI_API void azero_register_bluetooth_cb(int (*azero_bluetooth_cb)(azero_operation_bluetooth_e bluetooth_action));

/**
* Input status for further action.
*
* @param [in] input_status The input status for further action and control.
* @return The result of process, 0: successful, -1: failed.
*/
SAI_API int azero_input_status_inf(azero_input_status_e input_status );

/**
* reset http service for network switch or reconnect.
*/
SAI_API void azero_reset_http_service(void);

/**
* Get the SDK version info.
*
* @return the SDK version info.
*/
SAI_API const char* azero_get_sdk_version(void);


#if defined(__cplusplus)
}
#endif
#endif //SOUNDAI_AZERO_SDK_API_H
