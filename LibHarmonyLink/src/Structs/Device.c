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

#include "Structs/Device.h"
#include "Utilities.h"

#include <malloc.h>
#include <stdio.h>

FDevice* Device_Init(EPlatform platform, EDevice device, ESteamDeck steam_deck_model) {
    FDevice* newDevice = (FDevice*)malloc(sizeof(FDevice));
    if (newDevice != NULL) {
        newDevice->platform = platform;
        newDevice->device = device;
        newDevice->steam_deck_model = steam_deck_model;
    }
    return newDevice;
}

void HL_Device_Print(const FDevice *Device) {
    if (Device == NULL) {
        wprintf(L"Device is NULL\n");
        return;
    }

    // Assuming that EPlatform, EDevice, and ESteamDeck have corresponding string representations
    // which should be implemented for a proper print function

    wchar_t* platformStr = convertToWideChar(Platform_ToString(Device->platform));
    wchar_t* deviceStr = convertToWideChar(Device_ToString(Device->device));
    wchar_t* steamDeckStr = convertToWideChar(SteamDeck_ToString(Device->steam_deck_model));

    wprintf(L"Device Information:\n");
    wprintf(L"Platform: %ls\n", platformStr);
    wprintf(L"Device: %ls\n", deviceStr);
    wprintf(L"Steam Deck Model: %ls\n", steamDeckStr);

    free(platformStr);
    free(deviceStr);
    free(steamDeckStr);
}

void HL_Device_Free(FDevice *Device) {
    if (Device != NULL) {
        free(Device);
    }
}
