#pragma once
#ifndef AL2O3_VFILE_UTILS_H
#define AL2O3_VFILE_UTILS_H

#include "al2o3_platform/platform.h"
#include "al2o3_vfile/vfile.h"
#include "al2o3_cmath/vector.h"

AL2O3_EXTERN_C uint8_t VFile_ReadByte(VFile_Handle handle);
AL2O3_EXTERN_C char VFile_ReadChar(VFile_Handle handle);

AL2O3_EXTERN_C int8_t VFile_ReadInt8(VFile_Handle handle);
AL2O3_EXTERN_C int16_t VFile_ReadInt16(VFile_Handle handle);
AL2O3_EXTERN_C int32_t VFile_ReadInt32(VFile_Handle handle);
AL2O3_EXTERN_C int64_t VFile_ReadInt64(VFile_Handle handle);
AL2O3_EXTERN_C uint8_t VFile_ReadUInt8(VFile_Handle handle);
AL2O3_EXTERN_C uint16_t VFile_ReadUInt16(VFile_Handle handle);
AL2O3_EXTERN_C uint32_t VFile_ReadUInt32(VFile_Handle handle);
AL2O3_EXTERN_C uint64_t VFile_ReadUInt64(VFile_Handle handle);

AL2O3_EXTERN_C bool VFile_ReadBool(VFile_Handle handle);
AL2O3_EXTERN_C float VFile_ReadFloat(VFile_Handle handle);
AL2O3_EXTERN_C double VFile_ReadDouble(VFile_Handle handle);
AL2O3_EXTERN_C Math_vec2F_t VFile_ReadVector2(VFile_Handle handle);
AL2O3_EXTERN_C Math_vec3F_t VFile_ReadVector3(VFile_Handle handle);
AL2O3_EXTERN_C Math_vec3F_t VFile_ReadPackedVector3(VFile_Handle handle, float maxAbsCoord);
AL2O3_EXTERN_C Math_vec4F_t VFile_ReadVector4(VFile_Handle handle);

AL2O3_EXTERN_C size_t VFile_ReadString(VFile_Handle handle, char *buffer, size_t maxSize);
AL2O3_EXTERN_C void VFile_ReadFileID(VFile_Handle handle, char buffer[4]);
AL2O3_EXTERN_C size_t VFile_ReadLine(VFile_Handle handle, char *buffer, size_t maxSize);

#endif //WYRD_VFILE_UTILS_H