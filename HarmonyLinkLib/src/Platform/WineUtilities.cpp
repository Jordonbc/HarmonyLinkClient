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

#include "WineUtilities.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <ghc/filesystem.hpp>

#ifdef BUILD_WINDOWS
#include <windows.h>
#endif

namespace fs = ghc::filesystem;

namespace HarmonyLinkLib
{
    bool force_detect_wine = false;
    
    std::shared_ptr<HarmonyLinkLib::FBattery> HarmonyLinkLib::WineUtilities::get_battery_status()
    {
        std::string append;
        if (is_wine_present())
        {
            append = "Z:";
        }

        FBattery result = {};
        for (int i = 0; i <= 9; ++i) {
            if (std::string bat_path = append + "/sys/class/power_supply/BAT" + std::to_string(i); fs::exists(bat_path)) {
                result.has_battery = true;

                std::ifstream status_file(bat_path + "/status");
                std::string status;
                if (status_file.is_open() && std::getline(status_file, status)) {
                    if (status == "Charging" || status == "AC") {
                        result.is_connected_to_ac = true;
                    }
                }

                std::ifstream capacity_file(bat_path + "/capacity");
                if (capacity_file.is_open() && std::getline(capacity_file, status)) {
                    result.battery_percent = static_cast<uint8_t>(std::stoi(status));
                    break;  // assuming you only need data from the first battery found
                }
            }
        }

        return std::make_shared<FBattery>(result);
    }

    std::shared_ptr<FCPUInfo> WineUtilities::get_cpu_info()
    {
        std::wcout << "Getting cpu info\n";
        
        std::string append;
        if (is_wine_present())
        {
            append = "Z:";
        }

        FCPUInfo cpu_info;
        
        std::ifstream file(append + "/proc/cpuinfo");
        std::unordered_map<HarmonyLinkLib::FString, HarmonyLinkLib::FString> hashmap;

        if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream line_stream(line);
                std::string key, value;
                if (std::getline(line_stream, key, ':')) {
                    key.erase(key.find_last_not_of(" \t") + 1); // Trim trailing whitespace from key
                    if (std::getline(line_stream, value)) {
                        value.erase(0, value.find_first_not_of(" \t")); // Trim leading whitespace from value

                        // Aggregate flags
                        if (key == "flags") {
                            std::istringstream flag_stream(value);
                            std::string flag;
                            while (flag_stream >> flag) {
                                flag.erase(flag.find_last_not_of(" \t") + 1); // Trim trailing whitespace from flag
                                cpu_info.Flags.insert(HarmonyLinkLib::FString(flag));
                                //printf("Flag detected: %s\n", flag.c_str());
                            }
                        } else {
                            hashmap[key] = value;
                        }
                    }
                }
            }
            file.close();
        }

        // Now you can access the values using the keys:
        cpu_info.VendorID = hashmap["vendor_id"];
        cpu_info.Model_Name = hashmap["model name"];

        try {
            cpu_info.Physical_Cores = std::stoi(hashmap["cpu cores"].c_str());
        } catch (const std::invalid_argument& ia) {
            std::wcerr << "Invalid argument: " << ia.what() << '\n';
        } catch (const std::out_of_range& oor) {
            std::wcerr << "Out of Range error: " << oor.what() << '\n';
        }
        
        cpu_info.Logical_Cores = (cpu_info.Flags.find("ht") != cpu_info.Flags.end()) ? cpu_info.Physical_Cores * 2 : cpu_info.Physical_Cores;

        return std::make_shared<FCPUInfo>(cpu_info);
    }

    std::shared_ptr<FOSVerInfo> WineUtilities::get_linux_info()
    {
        std::string append;
        if (is_wine_present())
        {
            append = "Z:";
        }

        FOSVerInfo os_info;
        
        std::ifstream file(append + "/etc/os-release");
        std::unordered_map<HarmonyLinkLib::FString, HarmonyLinkLib::FString> hashmap;

        if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream lineStream(line);
                std::string key, value;
                if (std::getline(lineStream, key, '=')) {
                    if (std::getline(lineStream, value)) {
                        // Remove leading and trailing whitespace
                        size_t firstNonSpace = value.find_first_not_of(" \t");
                        size_t lastNonSpace = value.find_last_not_of(" \t");
                        if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
                            value = value.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
                        } else {
                            value.clear(); // If value is all whitespace, make it empty
                        }

                        // Check for double quotes and remove them
                        if (!value.empty() && value.front() == '"' && value.back() == '"') {
                            value = value.substr(1, value.length() - 2);
                        }

                        hashmap[key] = value;
                    }
                }
            }
            file.close();
        }

        // Now you can access the values using the keys:
        os_info.name = hashmap["NAME"];
        os_info.id = hashmap["ID"];
        os_info.version_id = hashmap["VERSION_ID"];
        os_info.version_codename = hashmap["VERSION_CODENAME"];
        os_info.pretty_name = hashmap["PRETTY_NAME"];

        try {
            os_info.version = std::stoi(hashmap["VERSION"].c_str());
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
            // Handle the error, perhaps by setting a default value or leaving the field unchanged
        } catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
            // Handle the error, perhaps by setting a default value or leaving the field unchanged
        }

        return std::make_shared<FOSVerInfo>(os_info);
    }

    bool WineUtilities::is_wine_present()
    {
        static bool isWineCached = false; // Static variable to store the cached result
        static bool isWine = false;       // Static variable to indicate if the caching has been done

        if (!isWineCached)
        {
            // Only detect wine if force_detect_wine is true or if we haven't cached the result yet
#ifdef BUILD_WINDOWS
            std::wcout << "Detecting wine...\n";
            bool HasFound = GetProcAddress(GetModuleHandle("ntdll.dll"), "wine_get_version") != nullptr;

            if (!HasFound)
                HasFound = GetProcAddress(GetModuleHandle("ntdll.dll"), "proton_get_version") != nullptr;

            wprintf(L"wine %s found\n", HasFound ? L"has been" : L"not");

            isWine = HasFound; // Cache the result
#else
            isWine = false; // In non-Windows builds, always set isWine to false
#endif
            isWineCached = true; // Indicate that the result is now cached
        }

        return isWine; // Return the cached result
    }

    bool WineUtilities::force_detect_wine_presence()
    {
        force_detect_wine = true;
        return is_wine_present();
    }
}
