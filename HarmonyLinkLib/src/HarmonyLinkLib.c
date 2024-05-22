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

#include "HarmonyLinkLib.h"

#include <wchar.h>
#include "Version.h"

bool HarmonyLink_Init(void)
{
    wprintf(L"HarmonyLink V%hs Copyright (C) 2023 Jordon Brooks\n", get_version_string());
    wprintf(L"Build Timestamp: %hs\n", get_version_build_timestamp());
    wprintf(L"Git Branch: %hs\n", get_git_branch());
    wprintf(L"Git Commit Timestamp: %hs\n", get_git_commit_timestamp());
    wprintf(L"Build type: %ls\n", get_is_debug() ? L"True" : L"False");
    return 1;
}
