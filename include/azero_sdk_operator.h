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

#ifndef SOUNDAI_AZERO_SDK_OPERATOR_API_H
#define SOUNDAI_AZERO_SDK_OPERATOR_API_H

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
* The operator device information input.
*
* @param [in] device_imei The IMEI of the device if exist.
* @param [in] device_cxei The CMEI of CMCC or CUEI of CUC.
*/
SAI_API void azero_set_operator_device_info(const char *device_imei,
					                        const char *device_cxei);

/**
* Set the andcall app key and app sercret.
*
* @param [in] andcall_app_key The application key issued for andcall 
* 	      authentication by CMCC.
* @param [in] andcall_app_secret The application secret issued for andcall
*	      authentication by CMCC.
* @param [in] andlink_id The device ID created after andlink configured network.
*/
SAI_API void azero_set_CMCC_andcall_app_key(const char *andcall_app_key, 
                                            const char *andcall_app_secret,
                                            const char* andlink_id);

/**
* Set channel number and encryption key for wocall and TMP registration.
*
* @param [in] cuc_channel_no The channel number issued for WO call and TMP 
* 	      registration and encryption by CUC.
* @param [in] cuc_encrypt_key The encryption key issued for handshaking between
*	      device and server by CUC.
*/
SAI_API void azero_set_CUC_channel_key(const char *cuc_channel_no,
                                       const char *cuc_encrypt_key);

/**
* Enable migu, must enable it before azero_start_service.
* @param [in] VoWIFI absolute path (/usr/lib/libmigu.so).
*/
SAI_API void azero_enable_migu_music(const char *path);

/**
* Enable andlink, must enable it before azero_start_service.
*/
SAI_API void azero_enable_andlink(void);

/**
 * The following two APIs ,i.e. azero_enable_andcall and azero_enable_wocall, are used to enable Andcall of CMCC 
 * and Wocall of CUC explicitly. 
 * 
 * User could enable either phone type explicitly by invoking corresponding API before azero_start_service. If  
 * both invoked, only the latter one will take effect while the first one will be ignored.
 * 
 * Additionally, user could also enable one phone type inexplicitly by just place the required libraries in 
 * /usr/lib or /lib, without invoking either of the two below APIs. Then SDK will search for possible phone call 
 * libraries in /usr/lib and /lib, in order of first Andcall and then Wocall. Phone type will be determined based 
 * on search results.
 * 
 * libvoipengine.so : official AndCall library, must be v1.6.0 or above, user shoud ask CMCC for this lib.
 * libandcall_wrapper.so : secondary encapsulation of Andcall SDK ,user shoud ask SoundAI for this lib.
 * libmtccommon_voice.so : official WoCall library, user shoud ask CUC for this lib.
 * /

/**
* Enable Andcall, if want to enable Andcall explicitly, must enable it before azero_start_service, 
* or the enable will be ignored and SDK will search library automatically as described above.
* @param [in] andcall_lib_path Andcall Lib absolute path etc(/usr/lib/libvoipengine.so).
* @param [in] andcall_wrapper_path Andcall Lib wrapper absolute path etc(/usr/lib/libandcall_wrapper.so).
*/
SAI_API void azero_enable_andcall(const char *andcall_lib_path, const char *andcall_wrapper_path);

/**
* Enable Wocall, if want to enable Wocall explicitly, must enable it before azero_start_service,
* or the enable will be ignored and SDK will search library automatically as described above.
* @param [in] VoWIFI absolute path (/usr/lib/libmtccommon_voice.so).
*/
SAI_API void azero_enable_wocall(const char *path);

#if defined(__cplusplus)
}
#endif
#endif //SOUNDAI_AZERO_SDK_OPERATOR_API_H
