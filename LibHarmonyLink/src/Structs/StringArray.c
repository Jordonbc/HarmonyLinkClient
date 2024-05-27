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

#include "Structs/StringArray.h"
#include "Utilities.h"

#include <stdlib.h>
#include <string.h>

// Initialize FlagsInfo with optional initial size
void StringArray_Init(StringArray *flagsInfo, size_t overrideInitialSize) {
    size_t initialSize = DEFAULT_INITIAL_FLAGS_SIZE;

    if (overrideInitialSize > 0) {
        initialSize = overrideInitialSize;
    }

    flagsInfo->FlagsCount = 0;
    flagsInfo->AllocatedSize = initialSize;
    flagsInfo->data = (char**)malloc(initialSize * sizeof(char*));
    for (size_t i = 0; i < initialSize; ++i) {
        flagsInfo->data[i] = NULL;
    }
}

void StringArray_AddFlag(StringArray *flagsInfo, const char *flag) {
    // Check if we need to resize the array
    if (flagsInfo->FlagsCount >= flagsInfo->AllocatedSize) {
        StringArray_Resize(flagsInfo, flagsInfo->AllocatedSize * 2);
    }
#if defined(BUILD_WINDOWS)
    flagsInfo->data[flagsInfo->FlagsCount] = _strdup(flag);
#else
    flagsInfo->data[flagsInfo->FlagsCount] = strdup(flag);
#endif
    flagsInfo->FlagsCount++;
}

void HL_StringArray_Print(const StringArray *flagsInfo) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] != NULL) {
            wchar_t* wstr = convertToWideChar(flagsInfo->data[i]);
            wprintf(L"  %ls\n", wstr);
            free(wstr);
        }
    }
}

void HL_StringArray_Free(StringArray *flagsInfo) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        free(flagsInfo->data[i]);
    }
    free(flagsInfo->data);
}

void StringArray_Remove(StringArray *flagsInfo, const char *flag) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] && strcmp(flagsInfo->data[i], flag) == 0) {
            free(flagsInfo->data[i]);
            for (size_t j = i; j < flagsInfo->FlagsCount - 1; ++j) {
                flagsInfo->data[j] = flagsInfo->data[j + 1];
            }
            flagsInfo->data[flagsInfo->FlagsCount - 1] = NULL;
            flagsInfo->FlagsCount--;
            break;
        }
    }
}

bool HL_StringArray_Contains(const StringArray *flagsInfo, const char *flag) {
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] && strcmp(flagsInfo->data[i], flag) == 0) {
            return true;
        }
    }
    return false;
}

// Resize FlagsInfo array
void StringArray_Resize(StringArray* flagsInfo, size_t newSize) {
    // Count the number of non-null pointers
    size_t nonNullCount = 0;
    for (size_t i = 0; i < flagsInfo->FlagsCount; ++i) {
        if (flagsInfo->data[i] != NULL) {
            nonNullCount++;
        }
    }

    // Check if the new size is smaller than the number of non-null pointers
    if (newSize < nonNullCount) {
        fprintf(stderr, "Resize failed. New size is smaller than the number of non-null pointers.\n");
        return;
    }

    char** temp = realloc(flagsInfo->data, newSize * sizeof(char*));
    if (temp != NULL) {
        flagsInfo->data = temp;
        if (newSize > flagsInfo->AllocatedSize) {
            // Initialize new elements to NULL
            for (size_t i = flagsInfo->AllocatedSize; i < newSize; ++i) {
                flagsInfo->data[i] = NULL;
            }
        }
        flagsInfo->AllocatedSize = newSize;
    } else {
        // Handle realloc failure
        fprintf(stderr, "Realloc failed. Memory not reallocated.\n");
        exit(EXIT_FAILURE);
    }
}
