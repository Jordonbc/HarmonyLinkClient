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

#include "HarmonyLinkLib.h"

#include <iostream>
#include "Platform/IPlatformUtilities.h"
#include "Version.h"

namespace HarmonyLinkLib
{
    std::shared_ptr<IPlatformUtilities> PlatformUtilities = nullptr;

    bool HL_Init()
    {
        std::wcout << "HarmonyLink V" << version::ToString().c_str() << " Copyright (C) 2023 Jordon Brooks\n";
        PlatformUtilities = IPlatformUtilities::GetInstance();

        return PlatformUtilities != nullptr;
    }

    bool get_is_wine()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return false;
        }

        return PlatformUtilities->is_running_under_wine();
    }

    bool get_is_linux()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return false;
        }

        return PlatformUtilities->is_linux();
    }

    bool get_is_docked()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return false;
        }

        return PlatformUtilities->is_docked();
    }

    FCPUInfo* get_cpu_info()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return nullptr;
        }

        const std::shared_ptr<FCPUInfo> cpu_info = PlatformUtilities->get_cpu_info();
        if (!cpu_info)
        {
            return nullptr;
        }

        FCPUInfo* new_cpu_info = new FCPUInfo(*cpu_info);
        return new_cpu_info;
    }

    FDevice* get_device_info()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return nullptr;
        }

        const std::shared_ptr<FDevice> device = PlatformUtilities->get_device();
        if (!device)
        {
            return nullptr;
        }

        FDevice* new_device = new FDevice(*device);
        return new_device;
    }

    FOSVerInfo* get_os_version()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return nullptr;
        }

        const std::shared_ptr<FOSVerInfo> os_version_info = PlatformUtilities->get_os_version();
        if (!os_version_info)
        {
            return nullptr;
        }

        FOSVerInfo* new_os_info = new FOSVerInfo(*os_version_info);
        return new_os_info;
    }

    FBattery* get_battery_status()
    {
        if (!PlatformUtilities)
        {
            std::wcout << "Failed to get platform utilities!\n";
            return nullptr;
        }

        const std::shared_ptr<FBattery> new_battery = PlatformUtilities->get_battery_status();
        if (!new_battery)
        {
            return nullptr;
        }

        FBattery* battery = new FBattery(*new_battery);
        return battery;
    }
}
