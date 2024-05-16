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

#include "UnixUtilities.h"

namespace HarmonyLinkLib
{
    bool UnixUtilities::is_running_under_wine()
    {
        std::wcout << "This feature is not supported on unix systems yet.\n";
        return false;
    }

    std::shared_ptr<FCPUInfo> UnixUtilities::get_cpu_info()
    {
        std::wcout << "This feature is not supported on unix systems yet.\n";
        return nullptr;
    }

    std::shared_ptr<FBattery> UnixUtilities::get_battery_status()
    {
        std::wcout << "This feature is not supported on unix systems yet.\n";
        return nullptr;
    }

    std::shared_ptr<FOSVerInfo> UnixUtilities::get_os_version()
    {
        std::wcout << "This feature is not supported on unix systems yet.\n";
        return nullptr;
    }

    bool UnixUtilities::get_is_external_monitor_connected()
    {
        std::wcout << "This feature is not supported on unix-based systems yet.\n";
        return false;
    }

    bool UnixUtilities::get_keyboard_detected()
    {
        std::wcout << "This feature is not supported on unix-based systems yet.\n";
        return false;
    }

    bool UnixUtilities::get_mouse_detected()
    {
        std::wcout << "This feature is not supported on unix-based systems yet.\n";
        return false;
    }

    bool UnixUtilities::get_external_controller_detected()
    {
        std::wcout << "This feature is not supported on unix-based systems yet.\n";
        return false;
    }

    bool UnixUtilities::get_is_steam_deck_native_resolution()
    {
        std::wcout << "This feature is not supported on unix-based systems yet.\n";
        return false;
    }
}