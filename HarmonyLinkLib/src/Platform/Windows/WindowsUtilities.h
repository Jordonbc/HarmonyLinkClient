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

#include "Platform/IPlatformUtilities.h"

namespace HarmonyLinkLib
{
    class WindowsUtilities : public IPlatformUtilities
    {
    public:
        std::shared_ptr<FBattery> get_battery_status() override;

        std::shared_ptr<FCPUInfo> get_cpu_info() override;
    
        std::shared_ptr<FOSVerInfo> get_os_version() override;

        bool get_is_external_monitor_connected() override;

        bool get_keyboard_detected() override;

        bool get_mouse_detected() override;

        bool get_external_controller_detected() override;

        bool get_is_steam_deck_native_resolution() override;
    };
}
