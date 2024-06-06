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

#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include "Structs/OSInfo.h"

#ifdef _WIN32
#define strdup _strdup
#endif

FOSVerInfo* FOSVerInfo_Init(char* name, char* version, unsigned int id, char* version_id, char* version_codename, char* pretty_name,
                char* variant_id) {
    FOSVerInfo* OSVerInfo = (FOSVerInfo*)malloc(sizeof(FOSVerInfo));

    if (OSVerInfo == NULL) {
        fprintf(stderr, "Memory allocation failed for FOSVerInfo.\n");
        return NULL;
        //exit(EXIT_FAILURE);
    }

    OSVerInfo->name = strdup(name);
    OSVerInfo->version = strdup(version);
    OSVerInfo->id = id;
    OSVerInfo->version_id = strdup(version_id);
    OSVerInfo->version_codename = strdup(version_codename);
    OSVerInfo->pretty_name = strdup(pretty_name);
    OSVerInfo->variant_id = strdup(variant_id);

    return OSVerInfo;
}

void HL_FOSVerInfo_Free(FOSVerInfo* osVerInfo) {
    if (!osVerInfo) return;

    free(osVerInfo->name);
    free(osVerInfo->version);
    free(osVerInfo->version_id);
    free(osVerInfo->version_codename);
    free(osVerInfo->pretty_name);
    free(osVerInfo->variant_id);
    free(osVerInfo);
}
