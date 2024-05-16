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

#include "WindowsUtilities.h"

#include <sstream>
#include <Windows.h>

#include <XInput.h>
#pragma comment(lib, "XInput.lib")

#include "Platform/WineUtilities.h"
#include <algorithm>

namespace HarmonyLinkLib
{
    std::shared_ptr<FBattery> WindowsUtilities::get_battery_status()
    {
        if (is_linux())
        {
           return WineUtilities::get_battery_status();
        }
        FBattery result;
        
        SYSTEM_POWER_STATUS status;
        if (GetSystemPowerStatus(&status)) {
            result.has_battery = status.BatteryFlag != 128; // 128 indicates no battery
            result.is_connected_to_ac = status.ACLineStatus == 1;
            result.battery_percent = result.has_battery ? status.BatteryLifePercent : 0;
        } else {
            std::wcout << "Failed to get power statistics.\n";
        }

        return std::make_shared<FBattery>(result);
    }

    std::shared_ptr<FCPUInfo> WindowsUtilities::get_cpu_info()
    {
        if (is_linux())
        {
            return WineUtilities::get_cpu_info();
        }
        
        return {};
    }

    std::shared_ptr<FOSVerInfo> WindowsUtilities::get_os_version()
    {
        if (is_linux())
        {
            return WineUtilities::get_linux_info();
        }
        
        OSVERSIONINFOEX os_version_info;
        ZeroMemory(&os_version_info, sizeof(OSVERSIONINFOEX));
        os_version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

        if (!GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&os_version_info))) {
            // Handle error if needed
            return nullptr;
        }

        FOSVerInfo os_version;

        HKEY h_key;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), 0, KEY_READ, &h_key) == ERROR_SUCCESS)
        {
            DWORD dw_size;
            DWORD dw_type;
            char sz_product_name[256];
            dw_size = sizeof(sz_product_name);
            if (RegQueryValueEx(h_key, TEXT("ProductName"), nullptr, &dw_type, reinterpret_cast<LPBYTE>(sz_product_name), &dw_size) == ERROR_SUCCESS)
            {
                os_version.pretty_name = sz_product_name;
            }
            RegCloseKey(h_key);
        }

        std::stringstream version;
        version << os_version_info.dwMajorVersion << "." << os_version_info.dwMinorVersion;
        os_version.version_id = version.str();

        os_version.name = "Windows";
        os_version.version = os_version_info.dwBuildNumber; // Build number as the version

        return std::make_shared<FOSVerInfo>(os_version);
    }

    bool WindowsUtilities::get_is_external_monitor_connected()
    {
        // SM_CMONITORS returns the count of all display monitors.
        const int monitorCount = GetSystemMetrics(SM_CMONITORS);

        // More than one monitor implies an external monitor is connected.
        return monitorCount > 1;
    }

    bool WindowsUtilities::get_keyboard_detected()
    {
        UINT n_devices;
        std::vector<RAWINPUTDEVICELIST> devices;
        
        GetRawInputDeviceList(devices.data(), &n_devices, sizeof(RAWINPUTDEVICELIST));

        if (n_devices == 0)
        {
            return false;
        }

        return std::any_of(devices.begin(), devices.end(), [](const RAWINPUTDEVICELIST& device)
        {
            return device.dwType == RIM_TYPEKEYBOARD;
        });
    }

    bool WindowsUtilities::get_mouse_detected()
    {
        UINT n_devices;
        std::vector<RAWINPUTDEVICELIST> devices;
        
        GetRawInputDeviceList(devices.data(), &n_devices, sizeof(RAWINPUTDEVICELIST));

        if (n_devices == 0)
        {
            return false;
        }

        return std::any_of(devices.begin(), devices.end(), [](const RAWINPUTDEVICELIST& device)
        {
            return device.dwType == RIM_TYPEMOUSE;
        });
    }

    bool WindowsUtilities::get_external_controller_detected()
    {
        static_assert(XUSER_MAX_COUNT <= UINT8_MAX, "XUSER_MAX_COUNT exceeds uint8_t size");
        
        uint8_t connectedGamepads = 0;

        for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));

            if (XInputGetState(i, &state) == ERROR_SUCCESS) {
                connectedGamepads++;
            }
        }

        return connectedGamepads > 1;
    }

    bool WindowsUtilities::get_is_steam_deck_native_resolution()
    {
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);

        // Get the current display settings for the primary monitor
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode)) {
            // Check if the resolution is higher than 800p (1280x800)
            if (devMode.dmPelsWidth > 1280 || devMode.dmPelsHeight > 800) {
                return true;
            }
        }
        return false;
    }
}
