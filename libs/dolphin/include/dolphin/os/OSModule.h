#ifndef DOLPHIN_OSMODULE_H
#define DOLPHIN_OSMODULE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// typedef struct OSModuleInfo_s OSModuleInfo;

// typedef struct OSModuleQueue_s {
//   OSModuleInfo* head;
//   OSModuleInfo* tail;
// } OSModuleQueue;

// typedef struct OSModuleLink_s {
//   OSModuleInfo* next;
//   OSModuleInfo* prev;
// } OSModuleLink;

// typedef struct OSModuleInfo_s {
//   u32 id;
//   OSModuleLink link;
//   u32 numSections;
//   u32 sectionInfoOfs;
//   u32 nameOfs;
//   u32 nameSize;
//   u32 version;
// } OSModuleInfo;

// typedef struct OSModuleHeader_s {
//   OSModuleInfo info;
//   u32 bssSize;
//   u32 relOfs;
//   u32 impOfs;
//   u32 impSize;

//   u8 prologSection;
//   u8 epilogSection;
//   u8 unresolvedSection;
//   u8 bssSection;

//   u32 prolog;
//   u32 epilog;
//   u32 unresolved;
//   /* OS_MODULE_VERSION >= 2 */

//   u32 align;
//   u32 bssAlign;
// } OSModuleHeader;

// typedef struct OSSectionInfo_s {
//   u32 offset;
//   u32 size;
// } OSSectionInfo;

// #define OSGetSectionInfo(module) \
//   ((OSSectionInfo*) (((OSModuleInfo*) (module))->sectionInfoOfs))

// #define OS_SECTIONINFO_EXEC 1
// #define OS_SECTIONINFO_OFFSET(offset)   ((offset) & ~OS_SECTIONINFO_EXEC)

// void OSSetStringTable (const void* strTable);
// BOOL OSLink(OSModuleInfo* module, void* bss);
// BOOL OSUnlink(OSModuleInfo* module);

#ifdef __cplusplus
}
#endif

#endif
