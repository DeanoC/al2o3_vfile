#pragma once
#ifndef AL2O3_VFILE_MEMFILE_H
#define AL2O3_VFILE_MEMFILE_H

#include "al2o3_platform/platform.h"

typedef struct VFile_MemFile_t {
  void *memory;
  size_t size;
  bool takeOwnership;
  size_t offset;
} VFile_MemFile_t;

#endif //WYRD_VFILE_MEMFILE_H
