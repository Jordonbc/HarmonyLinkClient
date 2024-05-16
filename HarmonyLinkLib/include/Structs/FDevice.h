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

#include <HarmonyLinkStruct.h>

#include "Enums/EDevice.h"
#include "Enums/EPlatform.h"
#include "Enums/ESteamDeck.h"

namespace HarmonyLinkLib
{
    // Struct to represent a specific device with both platform and device type
    struct FDevice : HarmonyLinkStruct
    {
        EPlatform platform = EPlatform::UNKNOWN;
        EDevice device = EDevice::UNKNOWN;
        ESteamDeck steam_deck_model = ESteamDeck::NONE;
    };
}
