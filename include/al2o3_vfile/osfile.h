#pragma once
#ifndef AL2O3_VFILE_OSFILE_H
#define AL2O3_VFILE_OSFILE_H

#include "al2o3_platform/platform.h"
#include "al2o3_os/file.h"

typedef struct VFile_OsFile_t {
  Os_FileHandle fileHandle;
} VFile_OsFile_t;

#endif //WYRD_VFILE_OSFILE_H
