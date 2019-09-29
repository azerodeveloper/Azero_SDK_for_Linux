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

#include "../include/azero_sdk_api.h"

// C++ Standard Library
#include <csignal>  // std::signal and SIG_ERR macro
#include <fstream>  // std::ifstream and std::ifstream::in
#include <iostream> // std::cerr and std::cout
#include <memory>   // std::unique_ptr

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <inttypes.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/prctl.h>

#include <algorithm>
#include <sstream>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "sai_micbasex_interface.h"

using namespace std;

#define PRE_MODULE "AzeroOS_LOG"
bool basex_loop_run_ = true;
void* sai_plugin_basex_handle_;


static const std::string get_accurate_date() {
  struct timeval tv;
    struct tm *     time_ptr;
  std::memset(&tv, 0, sizeof(timeval));
  gettimeofday(&tv, NULL);
  time_ptr = std::localtime(&tv.tv_sec);
  char accT[128];
  std::sprintf(accT, "%d-%02d-%02d %02d:%02d:%02d.%.04ld\n",
          time_ptr->tm_year + 1900,
          time_ptr->tm_mon + 1,
          time_ptr->tm_mday,
          time_ptr->tm_hour,
          time_ptr->tm_min,
          time_ptr->tm_sec,
          (long)tv.tv_usec);
  std::string ret(accT);
  ret.erase(std::remove(ret.begin(), ret.end(), '\r'), ret.end());
  ret.erase(std::remove(ret.begin(), ret.end(), '\n'), ret.end());
  return ret;
}

static void debug_log_with_tag(const std::string& tag, std::string format, ...) {
  const char *fmt = format.c_str();
  va_list args1;
  va_start(args1, format);
  va_list args2;
  va_copy(args2, args1);
  char buf[1+vsnprintf(NULL, 0, fmt, args1)];
  va_end(args1);
  vsnprintf(buf, sizeof buf, fmt, args2);
  va_end(args2);
  printf("[****[%s]****]: [%s] #%s#  msg=%s\n", PRE_MODULE, get_accurate_date().c_str(), tag.c_str(), buf);
}

int demo_set_volume_cb(int volume_val){
    printf("demo azero set volume %d",volume_val);
    return 0;
}

int demo_get_volume_cb(){
    printf("demo azero_start_service get volume");
    return 99;
}

void demo_wakenup_cb(int waken_up, int waken_doa){
    printf("demo waken up :%d, waken_doa : %d \n",waken_up, waken_doa);
}


 void* load_plugin_basex() {
	void *handle;

    int mic_num = 2;
    int board_num = 8;
    int frame = 16*16;
    const char *hw = "hw:0,0"; 
    char chmap[16] = "0,1,3,4,2,5,6,7";
    handle = SaiMicBaseX_Init(board_num, mic_num, frame, hw);

    SaiMicBaseX_SetBit(handle,16);
    SaiMicBaseX_SetSampleRate(handle,16000);
    SaiMicBaseX_SetMicShiftBits(handle,16);
    SaiMicBaseX_SetRefShiftBits(handle,16);
    SaiMicBaseX_SetPeroidSize(handle,1024);
    SaiMicBaseX_SetBufferSize(handle,262144);

    const char *delim = ",";
    const char *token = strtok(chmap, delim);
    if (token)
    {
        int ch_map[20];
        int c = 0;
        do
        {
            ch_map[c++] = atoi(token);
        } while ((token = strtok(NULL, delim)));
        SaiMicBaseXSetChannelMap(handle,ch_map,board_num);

        if(SaiMicBaseX_Start(handle) == 0) {
			printf("[sample]start basex success ");
        } else {
            std::cout << " ======== [sample]start basex failed " << std::endl;
            }
    }
    std::cout << " ======== Basex : Finish basex init " << std::endl;

    return handle;
}

void* AzeroOS_handler(void* args) {
    prctl(PR_SET_NAME, "AzeroOS_thread");
    int start_azero = azero_start_service("/data/sai_config");
    if (start_azero != 0){
        debug_log_with_tag("AzeroOS_handler", "start failed! ");
        std::cout << "azero_start_service start failed" << std::endl;
    }
    return NULL;
}

void* basex_read_handler(void* args) {
    prctl(PR_SET_NAME, "basex_read");
	int write_bytes;
    while(basex_loop_run_) {
        int16_t *raw_data = nullptr;
        int32_t len = SaiMicBaseX_ReadData(sai_plugin_basex_handle_, &raw_data);

        if(raw_data && len > 0) {

            write_bytes = azero_audio_data_input(reinterpret_cast<const short int*>(raw_data), (int)len);
			if (write_bytes < 0)
				std::cout << " ======== Basex : write data to Azero failed: " << std::endl;

        } else {
            std::cout << " ======== Basex : Failed reading basex data: " << std::endl;
        }
    }
    std::cout << " ======== Basex : Out of basex reading routine "  << std::endl;
    return NULL;
}

int demo_bluetooth_cb(azero_operation_bluetooth_e bluetooth_action)
{
    if(AZERO_OPERATION_BT_OPEN == bluetooth_action){
        debug_log_with_tag("AzeroOS_handler", "bluetooth open! ");
    }else{
        debug_log_with_tag("AzeroOS_handler", "bluetooth close! ");
    }
    return 0;
}
void demo_audio_command_cb(azero_audio_command_e audio_command)
{
    debug_log_with_tag("AzeroOS_handler:","audio command!");
    printf("audio command: %d \n",audio_command);
}

int main(int argc, const char *argv[]) {
    int ret=0;
    pthread_t pt_AzeroOSid;
    pthread_t pt_BasexReadid;

    std::string TAG = "Main app";
    debug_log_with_tag(TAG, "Azero OS started");
    std::cout << "Azero OS version:" << azero_get_sdk_version() << std::endl;

    //set volume callback
    debug_log_with_tag(TAG, "set volume call back!");
    azero_register_set_volume_cb(demo_set_volume_cb);
    //get volume callback
    debug_log_with_tag(TAG, "get volume call back!");
    azero_register_get_volume_cb(demo_get_volume_cb);
    
    debug_log_with_tag(TAG, "wake up call back!");
    azero_register_wakenup_cb(demo_wakenup_cb);

    azero_register_bluetooth_cb(demo_bluetooth_cb);

    azero_register_audio_command_cb(demo_audio_command_cb);

    // creat AzeroOS thread
    ret=pthread_create(&pt_AzeroOSid,NULL,AzeroOS_handler,NULL);
    if(ret)
    {
        printf("create AzeroOS pthread failed\n");
        return 0;
    }
    else
    {
        printf("***Start AzeroOS Thread\n");
    }

    // init & creat basex thread
    sai_plugin_basex_handle_ = load_plugin_basex();
    ret=pthread_create(&pt_BasexReadid,NULL,basex_read_handler,NULL);
    if(ret)
    {
        printf("create basex pthread failed\n");
        return 0;
    }
    else
    {
        printf("***Start basex Thread success\n");
    }
    static int ret_key = -1;
    while (1) {
        //handle the regular event.
        printf("***I am alive and wait for work\n");
        sleep(5);
        //key event test
        if (ret_key < 0 || ret_key++ > 20){
            ret_key = azero_input_status_inf(AZERO_BT_PLAYER_PLAYING);
            if (ret_key > 20) { ret_key = -1;}
            debug_log_with_tag("AzeroOS_handler", "send AZERO_BT_PLAYER_PLAYING! ");
        }
        if (ret_key == -1){
            ret_key = azero_input_status_inf(AZERO_BT_PLAYER_STOPPED);
            debug_log_with_tag("AzeroOS_handler", "send AZERO_BT_PLAYER_STOPPED! ");
        }
    }

    azero_stop_service();    
    return 0;
}
