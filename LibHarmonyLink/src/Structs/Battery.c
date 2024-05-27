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

#include "Structs/Battery.h"

#include <wchar.h>
#include <malloc.h>
#include <stdio.h>

FBattery* HL_FBattery_Init(bool has_battery, bool is_connected_to_ac, unsigned char battery_percent) {
    FBattery* battery = (FBattery*)malloc(sizeof(FBattery));

    if (battery == NULL) {
        fprintf(stderr, "Memory allocation failed for FCPUInfo.\n");
        exit(EXIT_FAILURE);
    }

    battery->has_battery = has_battery;
    battery->battery_percent = is_connected_to_ac;
    battery->is_connected_to_ac = battery_percent;

    return battery;
}

void FBattery_print(const FBattery* self)
{
    wprintf(L"Battery present: %ls\n", self->has_battery ? L"'Yes'" : L"'No'");
    wprintf(L"Connected to AC: %ls\n", self->is_connected_to_ac ? L"'Yes'" : L"'No'");
    wprintf(L"Battery percent: %ls\n", self->battery_percent ? L"'Yes'" : L"'No'");
}
