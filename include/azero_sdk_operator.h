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

#if defined(__cplusplus)
}
#endif
#endif //SOUNDAI_AZERO_SDK_OPERATOR_API_H
