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

// Use a preprocessor definition to switch between export and import declarations
#ifdef BUILD_WINDOWS
    #ifdef HARMONYLINKLIB_STATIC
        #define HARMONYLINKLIB_API
    #else
        #ifdef HARMONYLINKLIB_SHARED
            #define HARMONYLINKLIB_API __declspec(dllexport)
        #else
            #define HARMONYLINKLIB_API __declspec(dllimport)
        #endif
    #endif
#else
    #ifdef HARMONYLINKLIB_SHARED
        #ifdef __clang__
            #define HARMONYLINKLIB_API __attribute__((visibility("default")))
        #else
            #define HARMONYLINKLIB_API
        #endif
    #else
        #define HARMONYLINKLIB_API
    #endif
#endif
