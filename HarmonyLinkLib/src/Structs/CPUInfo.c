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

#include "Structs/CPUInfo.h"

#include <stdlib.h>
#include <string.h>

void FlagsInfo_Init(FlagsInfo *flagsInfo, size_t count) {
    flagsInfo->FlagsCount = count;
    flagsInfo->data = (char**)malloc(count * sizeof(char*));
    for (size_t i = 0; i < count; ++i) {
        flagsInfo->data[i] = NULL;
    }
}

void FCPUInfo_Init(FCPUInfo *cpuInfo, const char *vendorID, const char *modelName, unsigned int physicalCores,
                     unsigned int logicalCores, size_t flagsCount) {
    cpuInfo->VendorID = strdup(vendorID);
    cpuInfo->Model_Name = strdup(modelName);
    cpuInfo->Physical_Cores = physicalCores;
    cpuInfo->Logical_Cores = logicalCores;
    FlagsInfo_Init(&cpuInfo->flagsInfo, flagsCount);
}

void FlagsInfo_AddFlag(FlagsInfo *flagsInfo, size_t index, const char *flag) {
    if (index < flagsInfo->FlagsCount) {
        flagsInfo->data[index] = strdup(flag);
    }
}

void HL_FlagsInfo_Print(const FlagsInfo *flagsInfo) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] != NULL) {
            wprintf(L"  %s\n", flagsInfo->data[i]);
        }
    }
}

void HL_FCPUInfo_Print(const FCPUInfo *cpuInfo) {
    wprintf(L"VendorID: %s\n", cpuInfo->VendorID);
    wprintf(L"Model Name: %s\n", cpuInfo->Model_Name);
    wprintf(L"Physical Cores: %u\n", cpuInfo->Physical_Cores);
    wprintf(L"Logical Cores: %u\n", cpuInfo->Logical_Cores);
    wprintf(L"Flags:\n");
    HL_FlagsInfo_Print(&cpuInfo->flagsInfo);
}

void HL_FlagsInfo_Free(FlagsInfo *flagsInfo) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        free(flagsInfo->data[i]);
    }
    free(flagsInfo->data);
}

void FlagsInfo_Remove(FlagsInfo *flagsInfo, const char *flag) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] && strcmp(flagsInfo->data[i], flag) == 0) {
            free(flagsInfo->data[i]);
            for (size_t j = i; j < flagsInfo->FlagsCount - 1; ++j) {
                flagsInfo->data[j] = flagsInfo->data[j + 1];
            }
            flagsInfo->data[flagsInfo->FlagsCount - 1] = NULL;
            flagsInfo->FlagsCount--;

            // Use a temporary pointer to ensure realloc success
            char** temp = realloc(flagsInfo->data, flagsInfo->FlagsCount * sizeof(char*));
            if (temp != NULL) {
                flagsInfo->data = temp;
            } else if (flagsInfo->FlagsCount > 0) {
                // realloc failed and we're not deallocating to zero, handle error
                fprintf(stderr, "Realloc failed. Memory not reallocated.\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
}

bool HL_FlagsInfo_Contains(const FlagsInfo *flagsInfo, const char *flag) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] && strcmp(flagsInfo->data[i], flag) == 0) {
            return true;
        }
    }
    return false;
}

void HL_FCPUInfo_Free(FCPUInfo *cpuInfo) {
    free(cpuInfo->VendorID);
    free(cpuInfo->Model_Name);
    HL_FlagsInfo_Free(&cpuInfo->flagsInfo);
}
