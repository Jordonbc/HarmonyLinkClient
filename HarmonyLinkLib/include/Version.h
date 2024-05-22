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

#pragma once

#include <stdbool.h>
#include "Core.h"

HARMONYLINKLIB_API char* get_version_string(void);
HARMONYLINKLIB_API char* get_version_build_timestamp(void);
HARMONYLINKLIB_API char* get_git_branch(void);
HARMONYLINKLIB_API char* get_git_commit_timestamp(void);
HARMONYLINKLIB_API bool get_is_debug(void);
