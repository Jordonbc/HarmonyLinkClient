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
    ESteamDeck_NONE, // Device is not a steam deck
    ESteamDeck_UNKNOWN, // Device is a steam deck but model cannot be determined
    ESteamDeck_LCD,
    ESteamDeck_OLED,
} ESteamDeck;

HARMONYLINK_API const char* SteamDeck_ToString(ESteamDeck steam_deck_model) {
    switch (steam_deck_model) {
        case ESteamDeck_NONE: return "NONE";
        case ESteamDeck_LCD: return "STEAMDECK_LCD";
        case ESteamDeck_OLED: return "STEAMDECK_OLED";
            // Add other cases as needed
        default: return "UNKNOWN";
    }
}

#ifdef __cplusplus
}
}
#endif
