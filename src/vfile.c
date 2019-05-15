#include "al2o3_platform/platform.h"
#include "al2o3_os/file.h"
#include "al2o3_vfile/vfile.h"
#include "al2o3_vfile/interface.h"
#include "al2o3_vfile/osfile.h"


#define VFILE_FUNC_HEADER  \
struct VFile_Interface_t* interface = (VFile_Interface_t*)handle; \
ASSERT(interface); \
ASSERT(interface->magic == InterfaceMagic);

AL2O3_EXTERN_C void VFile_Close(VFile_Handle handle) {
  VFILE_FUNC_HEADER
  interface->closeFunc(interface);
  free(interface);
}

AL2O3_EXTERN_C void VFile_Flush(VFile_Handle handle) {
  VFILE_FUNC_HEADER
  interface->flushFunc(interface);
}
AL2O3_EXTERN_C size_t VFile_Read(VFile_Handle handle, void *buffer, size_t byteCount) {
  VFILE_FUNC_HEADER
  memset(buffer, 0, byteCount);
  return interface->readFunc(interface, buffer, byteCount);
}
AL2O3_EXTERN_C size_t VFile_Write(VFile_Handle handle, void const *buffer, size_t byteCount) {
  VFILE_FUNC_HEADER
  return interface->writeFunc(interface, buffer, byteCount);
}
AL2O3_EXTERN_C bool VFile_Seek(VFile_Handle handle, int64_t offset, enum VFile_SeekDir origin) {
  VFILE_FUNC_HEADER
  return interface->seekFunc(interface, offset, origin);
}
AL2O3_EXTERN_C int64_t VFile_Tell(VFile_Handle handle) {
  VFILE_FUNC_HEADER
  return interface->tellFunc(interface);
}
AL2O3_EXTERN_C size_t VFile_Size(VFile_Handle handle) {
  VFILE_FUNC_HEADER
  return interface->sizeFunc(interface);
}

AL2O3_EXTERN_C char const *VFile_GetName(VFile_Handle handle) {
  VFILE_FUNC_HEADER

  return interface->nameFunc(interface);
}

AL2O3_EXTERN_C bool VFile_IsEOF(VFile_Handle handle) {
  VFILE_FUNC_HEADER

  return interface->isEofFunc(interface);
}
AL2O3_EXTERN_C uint32_t VFile_GetType(VFile_Handle handle) {
  VFILE_FUNC_HEADER

  return interface->type;
}
AL2O3_EXTERN_C void* VFile_GetTypeSpecificData(VFile_Handle handle) {
  VFILE_FUNC_HEADER

  return (interface + 1);
}

#undef VFILE_FUNC_HEADER
