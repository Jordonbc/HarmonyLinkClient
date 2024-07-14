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

#ifdef __cplusplus
namespace LibHarmonyLink {
extern "C" {
#endif

/**
 * @brief Initializes the HarmonyLink library.
 *
 * This function initializes the HarmonyLink library by printing the version,
 * detecting if the application is running under Wine or on Linux.
 *
 * @return Returns true on successful initialization.
 */
HARMONYLINK_API bool HL_Init(void);
/**
 * @brief Checks if the HarmonyLink library is running under Wine.
 *
 * This function returns the result of Get_IsWine.
 *
 * @return Returns true if the HarmonyLink library is running under Wine, false otherwise.
 */
HARMONYLINK_API bool HL_Is_Wine(void);

/**
 * @brief Checks if the HarmonyLink library is running on Linux.
 *
 * This function returns the result of Get_IsLinux.
 *
 * @return Returns true if the HarmonyLink library is running on Linux, false otherwise.
 */
HARMONYLINK_API bool HL_Is_Linux(void);

/**
 * @brief Handles the detection of Linux.
 *
 * This function detects if the application is running on Linux and caches the result.
 * If the application is not running on Linux, it checks if it is running under Wine.
 */
void Handle_Detect_Linux(void);

/**
 * @brief Handles the detection of Wine.
 *
 * This function detects if the application is running under Wine and caches the result.
 */
void Handle_Detect_Wine(void);

/**
 * @brief Checks if the application is running under Wine.
 *
 * This function returns the cached result of the Wine detection. If the result
 * is not cached, it will call Handle_Detect_Wine to detect and cache the result.
 *
 * @return Returns true if the application is running under Wine, false otherwise.
 */
bool Get_IsWine(void);

/**
 * @brief Checks if the application is running on Linux.
 *
 * This function returns the cached result of the Linux detection. If the result
 * is not cached, it will call Handle_Detect_Linux to detect and cache the result.
 *
 * @return Returns true if the application is running on Linux, false otherwise.
 */
bool Get_IsLinux(void);

#ifdef __cplusplus
}
}
#endif
