# Azero OS API Reference
[TOC]
### 开启、结束Azero OS服务及设置

```c
/*
 * 启动 Azero OS 服务
 * cfg_path: 相关配置文件的绝对路径，例如/data/Azero_config 
 */
SAI_API void azero_start_service(const char *cfg_path);

/* 停止 Azero OS 服务并释放相关资源 */
SAI_API void azero_stop_service(void);

/*
 * 设置用户和设备相关信息
 * client_ID:用户ID
 * product_ID: 产品ID
 * device_SN:唯一设备号
 */
SAI_API void azero_set_customer_info(const char *client_ID,
				const char *product_ID,
				const char *device_SN);

/*
 * 设备系统相关信息上报
 * 参见头文件azero_sdk_api.h中示例json进行值对上报
 */
SAI_API void azero_device_sys_info(const char *azero_device_info_json);

/* 绑定设备时的ID和验证码（暂未生效）*/
SAI_API void azero_register_bind_verification_cb(void(*azero_bind_verification_cb)(
						const char *verifcation_id,
						const char *verifcation_code));

/* 获取的当前Azero OS 版本 */
SAI_API const char* azero_get_os_version(void);
```
### 按键事件

##### 按键事件枚举

```c
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
```
##### 事件发送接口

```c
/* 向AZERO OS发送 相应的KEY事件 */ 
SAI_API int azero_send_key_event(azero_key_event_e key_event);
```
### 系统状态事件

##### 系统交互状态回调函数枚举
``` c
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
	///Phone Call in active state, the media is being transmitted 
	///between the caller and remote party.
	AZERO_EVT_PHONE_CALL_ACTIVE,
	///The inbound call has been received.
	AZERO_EVT_PHONE_CALL_RECEIVED,
	///Phone Call in inbound ringing state
	AZERO_EVT_PHONE_CALL_INBOUND_RINGING
}azero_status_event_e;
```

##### 系统交互状态回调注册接口
```c
/* 注册状态回调 */
SAI_API void azero_register_status_evt_cb(void(*azero_status_evt_cb)(
                                       azero_status_event_e status_event));
```

### 音量调节
```c
/* 设置系统音量回调 */
SAI_API void azero_register_set_volume_cb(int(*azero_set_volume_cb)(
					int volume_val));

/* 读取系统音量回调 */
SAI_API void azero_register_get_volume_cb(int(*azero_get_volume_cb)());
```
### 播放控制

##### 播放控制语音命令枚举
``` c
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
```

##### 播放控制接口
```c
/* 语音命令回调,通过接口获取当前语音命令控制三方播放器 */
SAI_API void azero_register_audio_command_cb(void(*azero_audio_command_cb)(
					azero_audio_command_e audio_command));

/* 播放外部音频文件 */
SAI_API int azero_audio_file_play(const char *file_path);

/* 播放指定的TTS内容 */
SAI_API void azero_play_user_tts(const char * tts_text);
```


### 唤醒操作

````c
/*设置系统唤醒状态*/
SAI_API int azero_set_wakeup_status(int status);

/*Azero OS 唤醒通知和估计的声源定位角度信息 */
SAI_API void azero_register_wakenup_cb(void(*azero_wakenup_cb)(
                                       int waken_up, int waken_doa));
````

### 语音识别

```c
/*原始多通道数据输入接口*/
SAI_API int azero_audio_data_input(const short int *audio_buf, int buf_size);

/* 单路识别数据输入接口 */
SAI_API int azero_audio_data_input_mono(const short int *audio_buf, int buf_size);
```

### 蓝牙控制
##### 蓝牙状态枚举
``` c
typedef enum {
	///Close the device bluetooth.
	AZERO_OPERATION_BT_CLOSE,
	///Open the device bluetooth.
	AZERO_OPERATION_BT_OPEN
}azero_operation_bluetooth_e;
```
##### 蓝牙控制接口
```c
/* 蓝牙状态回调函数注册 */
SAI_API void azero_register_bluetooth_cb(int (*azero_bluetooth_cb)(
				azero_operation_bluetooth_e bluetooth_action));

/* 设置当前播放状态 */
SAI_API int azero_input_status_inf(azero_input_status_e input_status);
```

### 网络设置
``` c
/* 重置http服务连接 */
SAI_API void azero_reset_http_service(void);
```