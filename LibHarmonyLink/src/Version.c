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

#include "Version.h"

#include <Version.generated.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

char* HL_version_get_string(void)
{
    return HARMONYLINK_VERSION;
}

char* HL_version_build_timestamp(void)
{
    return __TIMESTAMP__;
}

char* HL_git_branch(void)
{
    return GIT_BRANCH_NAME;
}

char* HL_git_commit_timestamp(void)
{
    return GIT_COMMIT_TIMESTAMP;
}

bool HL_is_debug(void)
{
#ifdef DEBUG_MODE
    return true;
#else
    return false;
#endif
}

void HL_version_print(void) {
    wprintf(L"HarmonyLink V%hs Copyright (C) 2023 Jordon Brooks\n", HL_version_get_string());
    wprintf(L"Build Timestamp: %hs\n", HL_version_build_timestamp());
    wprintf(L"Git Branch: %hs\n", HL_git_branch());
    wprintf(L"Git Commit Timestamp: %hs\n", HL_git_commit_timestamp());
    wprintf(L"Build type: %ls\n", HL_is_debug() ? L"True" : L"False");
}
