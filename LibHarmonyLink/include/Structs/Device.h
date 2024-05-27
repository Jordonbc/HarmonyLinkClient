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
#include "Enums/Platform.h"
#include "Enums/Device.h"
#include "Enums/SteamDeck.h"

#define DEFAULT_INITIAL_FLAGS_SIZE 4

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

typedef struct {
    EPlatform platform;
    EDevice device;
    ESteamDeck steam_deck_model;
} FDevice;

// Initialize FlagsInfo
FDevice* Device_Init(EPlatform platform, EDevice device, ESteamDeck steam_deck_model);

// Print FlagsInfo
HARMONYLINK_API void HL_Device_Print(const FDevice* Device);

// Free FlagsInfo
HARMONYLINK_API void HL_Device_Free(FDevice* Device);

#ifdef __cplusplus
}
}
#endif
