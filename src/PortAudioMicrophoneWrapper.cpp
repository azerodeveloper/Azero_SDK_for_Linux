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

#include <cstring>
#include <string>
#include <portaudio.h>
#include <iostream>

#include "PortAudioMicrophoneWrapper.h"

namespace demo {

static const int NUM_INPUT_CHANNELS = 1;
static const int NUM_OUTPUT_CHANNELS = 0;
static const double SAMPLE_RATE = 16000;
static const unsigned long PREFERRED_SAMPLES_PER_CALLBACK = 256;

/// String to identify log entries originating from this file.
static const std::string TAG("PortAudioMicrophoneWrapper:");

std::shared_ptr<PortAudioMicrophoneWrapper> PortAudioMicrophoneWrapper::create(callback_type cb) {
    std::shared_ptr<PortAudioMicrophoneWrapper> portAudioMicrophoneWrapper(new PortAudioMicrophoneWrapper(cb));
    if (!portAudioMicrophoneWrapper->initialize()) {
        std::cout << TAG << "Failed to initialize PortAudioMicrophoneWrapper" << std::endl;
        return nullptr;
    }
    return portAudioMicrophoneWrapper;
}

PortAudioMicrophoneWrapper::PortAudioMicrophoneWrapper(callback_type cb) :
        m_paStream{nullptr} ,
        m_cb(cb) {
}

PortAudioMicrophoneWrapper::~PortAudioMicrophoneWrapper() {
    Pa_StopStream(m_paStream);
    Pa_CloseStream(m_paStream);
    Pa_Terminate();
}

bool PortAudioMicrophoneWrapper::initialize() {
    PaError err;
    err = Pa_Initialize();
    if (err != paNoError) {
	    std::cout << TAG << "Failed to initialize PortAudio" << " errorCode" << err << std::endl;
        return false;
    }

    err = Pa_OpenDefaultStream(
                &m_paStream,
                NUM_INPUT_CHANNELS,
                NUM_OUTPUT_CHANNELS,
                paInt16,
                SAMPLE_RATE,
                PREFERRED_SAMPLES_PER_CALLBACK,
                PortAudioCallback,
                this);

    if (err != paNoError) {
        std::cout << TAG << "Failed to open PortAudio default stream"
                << " errorCode" << err << std::endl;
        return false;
    }
    return true;
}

bool PortAudioMicrophoneWrapper::startStreamingMicrophoneData() {
    std::lock_guard<std::mutex> lock{m_mutex};
    PaError err = Pa_StartStream(m_paStream);
    if (err != paNoError) {
	std::cout << TAG << "Failed to start PortAudio stream" << std::endl;
        return false;
    }
    return true;
}

bool PortAudioMicrophoneWrapper::stopStreamingMicrophoneData() {
    std::lock_guard<std::mutex> lock{m_mutex};
    PaError err = Pa_StopStream(m_paStream);
    if (err != paNoError) {
	std::cout << TAG << "Failed to stop PortAudio stream" << std::endl;
        return false;
    }
    return true;
}

int PortAudioMicrophoneWrapper::PortAudioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long numSamples,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    PortAudioMicrophoneWrapper* wrapper = static_cast<PortAudioMicrophoneWrapper*>(userData);
    ssize_t returnCode = wrapper->m_cb(inputBuffer, numSamples);
    if (returnCode <= 0) {
	    std::cout << TAG << "Failed to write to stream." << std::endl;
        return paAbort;
    }
    return paContinue;
}

}  // namespace demo
