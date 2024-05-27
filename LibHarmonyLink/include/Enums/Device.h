// Copyright (c) 2024 Jordon Brooks
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "Core.h"

// Undefine the LINUX macro to avoid conflicts with the enum definition.
#undef LINUX

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

typedef enum {
    EDevice_UNKNOWN,
    EDevice_DESKTOP,
    EDevice_LAPTOP,
    EDevice_HANDHELD,

    EDevice_STEAM_DECK,
    // EDevice_ROG_ALLY
    // EDevice_AYONEO_SLIDE
    // etc...
} EDevice;

HARMONYLINK_API const char* Device_ToString(EDevice device) {
    switch (device) {
        case EDevice_DESKTOP: return "DESKTOP";
        case EDevice_LAPTOP: return "LAPTOP";
        case EDevice_HANDHELD: return "HANDHELD";
        case EDevice_STEAM_DECK: return "STEAM_DECK";
        default: return "UNKNOWN";
    }
}

#ifdef __cplusplus
}
}
#endif
