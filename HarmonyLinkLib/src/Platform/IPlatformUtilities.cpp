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

#include "IPlatformUtilities.h"

#include <fmt/core.h>
#include <set>
#include "Utilities.h"

#include "WineUtilities.h"
#if BUILD_WINDOWS
#include "Windows/WindowsUtilities.h"
#elif BUILD_LINUX
#include "Unix/Linux/LinuxUtilities.h"
#elif BUILD_MAC
#include "Unix/Mac/MacUtilities.h"
#elif BUILD_UNIX
#include "Unix/Mac/MacUtilities.h"
#endif

namespace HarmonyLinkLib
{
    static std::shared_ptr<IPlatformUtilities> INSTANCE = nullptr;

    std::shared_ptr<IPlatformUtilities>& IPlatformUtilities::GetInstance()
    {
        if (!INSTANCE)
        {
    #if BUILD_WINDOWS
            INSTANCE = std::make_shared<WindowsUtilities>();
    #elif BUILD_LINUX
            INSTANCE = std::make_shared<LinuxUtilities>();
    #elif BUILD_MAC
            INSTANCE = std::make_shared<MacUtilities>();
    #elif BUILD_UNIX
            INSTANCE = std::make_shared<UnixUtilities>();
    // ... other platform checks
    #else
            std::wcout << "Platform is not supported.\n"
    #endif
        }
        
        return INSTANCE;
    }

    bool IPlatformUtilities::is_running_under_wine()
    {
        return WineUtilities::is_wine_present();
    }

    bool IPlatformUtilities::is_linux()
    {
    #ifdef BUILD_LINUX
        return true;
    #else
        return is_running_under_wine();
    #endif
    }

    bool IPlatformUtilities::is_steam_deck()
    {
        const std::shared_ptr<FDevice> device = get_device();

        return device && device->device == EDevice::STEAM_DECK;
    }

    bool IPlatformUtilities::is_docked()
    {
        static constexpr uint8_t CHARGING_SCORE = 3;
        static constexpr uint8_t EXTERNAL_MONITOR_SCORE = 4;
        static constexpr uint8_t STEAM_DECK_RESOLUTION_SCORE = 3;
        static constexpr uint8_t KEYBOARD_DETECTION_SCORE = 1;
        static constexpr uint8_t MOUSE_DETECTION_SCORE = 2;
        static constexpr uint8_t CONTROLLER_DETECTION_SCORE = 3;
        static constexpr uint8_t FINAL_TARGET_DETECTION_SCORE = 9;

        
        const std::shared_ptr<FDevice> device = get_device();

        if (!device)
        {
            std::wcout << "Error: failed to get device.\n";
            return false;
        }
        
        if (device->device != EDevice::STEAM_DECK)
        {
            std::wcout << "Error: Dock detection is currently only supported on Steam Decks.\n";
            return false;
        }

        uint8_t score = 0;

        Utilities::DebugPrint("Detected: ", false);

        if (is_charging())
        {
            Utilities::DebugPrint("Charging, ", false);
            score += CHARGING_SCORE;
        }

        if (get_is_external_monitor_connected())
        {
            Utilities::DebugPrint("External monitor, ", false);
            score += EXTERNAL_MONITOR_SCORE;
        }

        if (get_is_steam_deck_native_resolution())
        {
            Utilities::DebugPrint("Non-native resolution, ", false);
            score += STEAM_DECK_RESOLUTION_SCORE;
        }

        if (get_keyboard_detected())
        {
            Utilities::DebugPrint("keyboard ", false);
            score += KEYBOARD_DETECTION_SCORE;
        }

        if (get_mouse_detected())
        {
            Utilities::DebugPrint("mouse, ", false);
            score += MOUSE_DETECTION_SCORE;
        }

        if (get_external_controller_detected())
        {
            Utilities::DebugPrint("external controller, ", false);
            score += CONTROLLER_DETECTION_SCORE;
        }

        Utilities::DebugPrint(fmt::format("Score: {}/{}", score, FINAL_TARGET_DETECTION_SCORE).c_str());
        
        return score >= FINAL_TARGET_DETECTION_SCORE;
    }

    std::shared_ptr<FDevice> IPlatformUtilities::get_device()
    {
        FDevice new_device;
        
        if (is_linux())
        {
            new_device.platform = EPlatform::LINUX;
        }
        else
        {
            new_device.platform = EPlatform::WINDOWS;
        }

        const std::shared_ptr<FBattery> battery_status = get_battery_status();

        if (battery_status && !battery_status->has_battery)
        {
            new_device.device = EDevice::DESKTOP;
        }
        else
        {
            new_device.device = EDevice::LAPTOP;
        }

        if (is_steam_deck_detected(new_device)) {
            new_device.device = EDevice::STEAM_DECK;
        }
        return std::make_shared<FDevice>(new_device);
    }

    // Helper function to check if the device is a Steam Deck
    bool IPlatformUtilities::is_steam_deck_detected(const FDevice& device) {

        // Check if the device is already identified as a Steam Deck
        if (device.device == EDevice::STEAM_DECK) {
            return true;
        }

        // Check for Steam Deck by OS version
        if (const std::shared_ptr<FOSVerInfo> version = get_os_version()) {
            if (version->variant_id == "steamdeck" && version->name == "SteamOS") {
                return true;
            }
        } else {
            wprintf(L"OS version information not available.\n");
        }

        // Set of known Steam Deck CPU model names
        const std::set<std::string> steam_deck_models = {
            "amd custom apu 0405" // LCD Steam Deck
            "amd custom apu 0932", // OLED Steam Deck
        };

        // Check for Steam Deck by CPU model name
        if (const std::shared_ptr<FCPUInfo> cpu_info = get_cpu_info()) {
            const FString cpu_model_lower = FString::to_lower(cpu_info->Model_Name);
            for (const auto& model : steam_deck_models) {
                if (cpu_model_lower == FString::to_lower(model.c_str())) {
                    wprintf(L"Steam Deck detected by CPU model name.\n");
                    return true;
                }
            }
        } else {
            wprintf(L"CPU information not available.\n");
        }

        wprintf(L"Device is not a Steam Deck.\n");
        
        return false;
    }

    bool IPlatformUtilities::is_connected_to_ac()
    {
        const std::shared_ptr<FBattery> battery = get_battery_status();
        return battery && battery->is_connected_to_ac;
    }

    bool IPlatformUtilities::is_charging()
    {
        const std::shared_ptr<FBattery> battery = get_battery_status();
        return battery && battery->has_battery && battery->is_connected_to_ac;
    }
}
