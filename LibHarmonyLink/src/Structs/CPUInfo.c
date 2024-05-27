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
#include "Utilities.h"

#include <stdlib.h>
#include <string.h>

FCPUInfo* FCPUInfo_Init(const char *vendorID, const char *modelName, unsigned int physicalCores,
                     unsigned int logicalCores, size_t flagsCount) {
    FCPUInfo *cpuInfo = (FCPUInfo*)malloc(sizeof(FCPUInfo));

    if (cpuInfo == NULL) {
        fprintf(stderr, "Memory allocation failed for FCPUInfo.\n");
        exit(EXIT_FAILURE);
    }
#if defined(BUILD_WINDOWS)
    cpuInfo->VendorID = _strdup(vendorID);
    cpuInfo->Model_Name = _strdup(modelName);
#else
    cpuInfo->VendorID = strdup(vendorID);
    cpuInfo->Model_Name = strdup(modelName);
#endif

    cpuInfo->Physical_Cores = physicalCores;
    cpuInfo->Logical_Cores = logicalCores;
    StringArray_Init(&cpuInfo->flagsInfo, flagsCount);

    return cpuInfo;
}

void HL_FlagsInfo_Print(const FCPUInfo* cpuInfo) {
    if (!cpuInfo)
    {
        fprintf(stderr, "cpuInfo is nullptr!\n");
        return;
    }

    HL_StringArray_Print(&cpuInfo->flagsInfo);
}

void HL_FCPUInfo_Print(const FCPUInfo *cpuInfo) {
    wchar_t* wVendorID = convertToWideChar(cpuInfo->VendorID);
    wchar_t* wModelName = convertToWideChar(cpuInfo->Model_Name);

    wprintf(L"VendorID: %ls\n", wVendorID);
    wprintf(L"Model Name: %ls\n", wModelName);
    wprintf(L"Physical Cores: %u\n", cpuInfo->Physical_Cores);
    wprintf(L"Logical Cores: %u\n", cpuInfo->Logical_Cores);
    wprintf(L"Flags:\n");
    HL_StringArray_Print(&cpuInfo->flagsInfo);

    free(wVendorID);
    free(wModelName);
}

bool HL_FlagsInfo_Contains(const FCPUInfo* cpuInfo, const char* flag) {
    if (!cpuInfo)
    {
        fprintf(stderr, "cpuInfo is nullptr!\n");
        return false;
    }

    return HL_StringArray_Contains(&cpuInfo->flagsInfo, flag);
}

void HL_FCPUInfo_Free(FCPUInfo *cpuInfo) {
    free(cpuInfo->VendorID);
    free(cpuInfo->Model_Name);
    HL_StringArray_Free(&cpuInfo->flagsInfo);
}
