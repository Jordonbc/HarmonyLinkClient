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

#include "Utilities.h"
#include <stdlib.h>

wchar_t* convertToWideChar(const char* str) {
    size_t len = 0;
    mbstowcs_s(&len, NULL, 0, str, 0); // Get the length of the wide string (including null terminator)
    wchar_t* wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
    if (wstr == NULL) {
        return NULL; // Handle memory allocation failure
    }
    mbstowcs_s(&len, wstr, len, str, len - 1);
    return wstr;
}