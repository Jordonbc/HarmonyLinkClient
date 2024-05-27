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

typedef struct {
    char** data;       // Array of strings (flags)
    size_t FlagsCount; // Number of flags
} FlagsInfo;

typedef struct {
    char* VendorID;
    char* Model_Name;
    unsigned int Physical_Cores;
    unsigned int Logical_Cores;
    FlagsInfo flagsInfo;
} FCPUInfo;

// Initialize FlagsInfo
void FlagsInfo_Init(FlagsInfo* flagsInfo, size_t count);

// Initialize FCPUInfo
void FCPUInfo_Init(FCPUInfo* cpuInfo, const char* vendorID, const char* modelName, unsigned int physicalCores, unsigned int logicalCores, size_t flagsCount);

// Print FlagsInfo
HARMONYLINKLIB_API void HL_FlagsInfo_Print(const FlagsInfo* flagsInfo);

// Print FCPUInfo
HARMONYLINKLIB_API void HL_FCPUInfo_Print(const FCPUInfo* cpuInfo);

// Free FlagsInfo
HARMONYLINKLIB_API void HL_FlagsInfo_Free(FlagsInfo* flagsInfo);

// Free FCPUInfo
HARMONYLINKLIB_API void FCPUInfo_Free(FCPUInfo* cpuInfo);

// Check if a flag exists in FlagsInfo
HARMONYLINKLIB_API bool HL_FlagsInfo_Contains(const FlagsInfo* flagsInfo, const char* flag);

// Add a flag to FlagsInfo
void FlagsInfo_AddFlag(FlagsInfo* flagsInfo, size_t index, const char* flag);

// Remove a flag from FlagsInfo by value
void FlagsInfo_Remove(FlagsInfo* flagsInfo, const char* flag);
