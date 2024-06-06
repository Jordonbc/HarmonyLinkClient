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

// include/Structs/CPUInfo.h

#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "Core.h"
#include "Structs/StringArray.h"

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

typedef struct FCPUInfo {
    char* VendorID;
    char* Model_Name;
    unsigned int Physical_Cores;
    unsigned int Logical_Cores;
    StringArray flagsInfo;
} FCPUInfo;

// Initialize FCPUInfo
FCPUInfo* FCPUInfo_Init(const char *vendorID, const char *modelName, unsigned int physicalCores, unsigned int logicalCores,
              size_t flagsCount);

// Print FlagsInfo
HARMONYLINK_API void HL_FlagsInfo_Print(const FCPUInfo *cpuInfo);

// Print FCPUInfo
HARMONYLINK_API void HL_FCPUInfo_Print(const FCPUInfo *cpuInfo);

// Free FCPUInfo
HARMONYLINK_API void HL_FCPUInfo_Free(FCPUInfo *cpuInfo);

// Check if a flag exists in FlagsInfo
HARMONYLINK_API bool HL_FlagsInfo_Contains(const FCPUInfo *cpuInfo, const char *flag);

#ifdef __cplusplus
}
}
#endif
