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

#include <iostream>

#include "FString.h"

void HarmonyLinkLib::Utilities::DebugPrint(const FString& String, bool AddNewline)
{
#ifdef DEBUG_MODE
    std::wcout << String.c_str();
    
    if (AddNewline)
    {
        std::wcout << L"\n";
    }
#endif
}

void HarmonyLinkLib::Utilities::DebugPrint(const char* String, bool AddNewline)
{
#ifdef DEBUG_MODE
    std::wcout << std::wstring(String, String + std::strlen(String));
    
    if (AddNewline) {
        std::wcout << L"\n";
    }
#endif
}

void HarmonyLinkLib::Utilities::DebugPrint(const wchar_t* String, bool AddNewline)
{
#ifdef DEBUG_MODE
    std::wcout << String;
    
    if (AddNewline) {
        std::wcout << L"\n";
    }
#endif
}
