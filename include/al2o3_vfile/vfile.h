#pragma once
#ifndef AL2O3_VFILE_VFILE_H
#define AL2O3_VFILE_VFILE_H

#include "al2o3_platform/platform.h"
#include "al2o3_os/file.h"

typedef struct VFile_Interface_t *VFile_Handle;

enum VFile_SeekDir {
  VFile_SD_Begin = 0,
  VFile_SD_Current,
  VFile_SD_End,
};

enum {
  VFile_Type_Invalid = 0,
  VFile_Type_OsFile = 1,
  VFile_Type_Memory = 2
};

AL2O3_EXTERN_C VFile_Handle VFile_FromFile(char const *filename, enum Os_FileMode mode);
AL2O3_EXTERN_C VFile_Handle VFile_FromMemory(void const *memory, size_t size, bool takeOwnership);
AL2O3_EXTERN_C VFile_Handle VFile_ToBuffer(size_t initialSize);

AL2O3_EXTERN_C void VFile_Close(VFile_Handle handle);
AL2O3_EXTERN_C void VFile_Flush(VFile_Handle handle);
AL2O3_EXTERN_C size_t VFile_Read(VFile_Handle handle, void *buffer, size_t byteCount);
AL2O3_EXTERN_C size_t VFile_Write(VFile_Handle handle, void const *buffer, size_t byteCount);
AL2O3_EXTERN_C bool VFile_Seek(VFile_Handle handle, int64_t offset, enum VFile_SeekDir origin);
AL2O3_EXTERN_C int64_t VFile_Tell(VFile_Handle handle);
AL2O3_EXTERN_C size_t VFile_Size(VFile_Handle handle);
AL2O3_EXTERN_C char const *VFile_GetName(VFile_Handle handle);
AL2O3_EXTERN_C bool VFile_IsEOF(VFile_Handle handle);
AL2O3_EXTERN_C uint32_t VFile_GetType(VFile_Handle handle);
AL2O3_EXTERN_C void* VFile_GetTypeSpecificData(VFile_Handle handle);

#endif //WYRD_VFILE_VFILE_H
