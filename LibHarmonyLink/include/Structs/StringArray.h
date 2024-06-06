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

// include/Structs/StringArray.h

#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "Core.h"

#define DEFAULT_INITIAL_FLAGS_SIZE 4

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

typedef struct StringArray {
    char **data;       // Array of strings (flags)
    size_t FlagsCount; // Number of flags
    size_t AllocatedSize; // Number of allocated slots
} StringArray;

// Initialize FlagsInfo
void StringArray_Init(StringArray *flagsInfo, size_t overrideInitialSize);

// Print FlagsInfo
HARMONYLINK_API void HL_StringArray_Print(const StringArray *flagsInfo);

// Free FlagsInfo
HARMONYLINK_API void HL_StringArray_Free(StringArray *flagsInfo);

// Check if a flag exists in FlagsInfo
HARMONYLINK_API bool HL_StringArray_Contains(const StringArray *flagsInfo, const char *flag);

// Add a flag to FlagsInfo
void StringArray_AddFlag(StringArray *flagsInfo, const char *flag);

// Remove a flag from FlagsInfo by value
void StringArray_Remove(StringArray *flagsInfo, const char *flag);

// Resize FlagsInfo array
void StringArray_Resize(StringArray *flagsInfo, size_t newSize);

#ifdef __cplusplus
}
}
#endif
