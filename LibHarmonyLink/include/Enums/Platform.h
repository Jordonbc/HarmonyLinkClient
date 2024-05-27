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

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

typedef enum {
    EPlatform_UNKNOWN,
    EPlatform_WINDOWS,
    EPlatform_LINUX,
    EPlatform_MAC,
    EPlatform_UNIX,
} EPlatform;

// Helper functions to convert enums to strings (must be implemented somewhere in your code)
HARMONYLINK_API const char* Platform_ToString(EPlatform platform) {
    switch (platform) {
        case EPlatform_WINDOWS: return "WINDOWS";
        case EPlatform_LINUX: return "LINUX";
        case EPlatform_MAC: return "MAC";
        case EPlatform_UNIX: return "UNIX";
        default: return "UNKNOWN";
    }
}

#ifdef __cplusplus
}
}
#endif
