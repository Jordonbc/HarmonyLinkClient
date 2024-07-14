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

#include "Wine.h"

#include <stdio.h>
#include <stdbool.h>
#ifdef BUILD_WINDOWS
#include <windows.h>
#endif

bool Detect_Wine(void)
{
    bool isWine = false;
    
#ifdef BUILD_WINDOWS
        printf("Detecting wine...\n");
        bool HasFound = GetProcAddress(GetModuleHandleA("ntdll.dll"), "wine_get_version") != NULL;

        if (!HasFound)
            HasFound = GetProcAddress(GetModuleHandleA("ntdll.dll"), "proton_get_version") != NULL;

        printf("wine %s found\n", HasFound ? "has been" : "not");

        isWine = HasFound; // Cache the result
#else
        isWine = false; // In non-Windows builds, always set isWine to false
#endif
    return isWine; // Return the cached result
}