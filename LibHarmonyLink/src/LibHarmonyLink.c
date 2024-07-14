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

#include <stdbool.h>
#include "LibHarmonyLink.h"

#include "Version.h"
#include "Wine.h"

static bool bIsWine = false;
static bool bCachedIsWine = false;

static bool bIsLinux = false;
static bool bCachedIsLinux = false;

bool HL_Init(void)
{
    HL_version_print();
    Handle_Detect_Wine();
    Handle_Detect_Linux();
    return 1;
}

void Handle_Detect_Wine(void)
{
#ifdef BUILD_WINDOWS
    bIsWine = Detect_Wine();
#else
    bIsWine = false;
#endif

bCachedIsWine = true;
}

bool Get_IsWine(void)
{
    if (!bCachedIsWine)
    {
        Handle_Detect_Wine();
    }

    return bIsWine;
}

bool Get_IsLinux(void)
{
    if (!bCachedIsLinux)
    {
        Handle_Detect_Linux();
    }

    return bIsLinux;
}

void Handle_Detect_Linux(void)
{
#ifdef BUILD_LINUX
    bIsLinux = true;
#else
    bIsLinux = Get_IsWine();
#endif

bCachedIsLinux = true;
}

bool HL_Is_Wine(void)
{
    return Get_IsWine();
}
bool HL_Is_Linux(void)
{
    return Get_IsLinux();
}
