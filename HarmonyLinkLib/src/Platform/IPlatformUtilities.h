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

#include "Enums/ESteamDeck.h"
#include "Structs/FBattery.h"
#include "Structs/FCPUInfo.h"
#include "Structs/FDevice.h"
#include "Structs/FOSVerInfo.h"

namespace HarmonyLinkLib
{
    class IPlatformUtilities {
    public:
        static std::shared_ptr<IPlatformUtilities>& GetInstance();

        IPlatformUtilities() = default;
        IPlatformUtilities(const IPlatformUtilities& other) = default;
        IPlatformUtilities(IPlatformUtilities&& other) = default;
        IPlatformUtilities& operator=(const IPlatformUtilities& other) = default;
        IPlatformUtilities& operator=(IPlatformUtilities&& other) = default;
        virtual ~IPlatformUtilities() = default;
    
        // General OS-level functions
        virtual bool is_running_under_wine();
        virtual bool is_linux();
        virtual bool is_steam_deck();
        virtual bool is_docked();
    
        virtual std::shared_ptr<FDevice> get_device();
        virtual std::shared_ptr<FCPUInfo> get_cpu_info() = 0;
        virtual std::shared_ptr<FBattery> get_battery_status() = 0;
        virtual std::shared_ptr<FOSVerInfo> get_os_version() = 0;
        virtual bool get_is_external_monitor_connected() = 0;
        virtual bool get_keyboard_detected() = 0;
        virtual bool get_mouse_detected() = 0;
        virtual bool get_external_controller_detected() = 0;
        virtual bool get_is_steam_deck_native_resolution() = 0;
        //virtual bool get_is_ethernet_connected() = 0;
        //virtual bool get_is_external_input_detected() = 0;

        ESteamDeck detect_steam_deck(const FDevice& device);
        bool is_connected_to_ac();
        bool is_charging();

        // Add more virtual functions for other OS interactions here
    };
}
