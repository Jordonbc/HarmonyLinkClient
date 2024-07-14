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

#include <wchar.h>
#include "LibHarmonyLink.h"

int main(void)
{
    wprintf(L"Hello from C!\n");
    
    if (!HL_Init())
    {
        wprintf(L"Error: Failed to initialise HarmonyLink!\n");
        return 1;
    }

    wprintf(L"Successfully Initialised HarmonyLink!\n");

    const wchar_t* IsLinux = HL_Is_Linux() ? L"True" : L"False";
    wprintf(L"Is Linux: %ls\n", IsLinux);

    const wchar_t* IsWine = HL_Is_Wine() ? L"True" : L"False";
    wprintf(L"Is Wine: %ls\n", IsWine);
    
    return 0;
}
