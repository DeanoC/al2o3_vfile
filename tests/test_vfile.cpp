#include "al2o3_platform/platform.h"
#include "al2o3_platform/utf8.h"
#include "al2o3_catch2/catch2.hpp"
#include "al2o3_vfile/vfile.h"
#include "al2o3_vfile/vfile.hpp"


TEST_CASE("Open and close (C)", "[VFile OsFile]") {
  {
  Os_FileHandle fh = Os_FileOpen("test_data/al2o3_vfile/test.txt", Os_FM_Write);
  REQUIRE(fh != NULL);
  static char expectedBytes[] = "Testing 1, 2, 3";
  size_t bytesWritten = Os_FileWrite(fh, expectedBytes, utf8size(expectedBytes));
  bool closeOk = Os_FileClose(fh);
  REQUIRE(closeOk);
  }

  VFile_Handle vfh = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Read);
  REQUIRE(vfh);
  REQUIRE(stricmp(VFile_GetName(vfh), "test_data/al2o3_vfile/test.txt") == 0);
  VFile_Close(vfh);
}

TEST_CASE("Read Testing 1, 2, 3 text file OsFile (C)", "[VFile]") {
  VFile_Handle vfh = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Read);
  REQUIRE(vfh);

  static char expectedBytes[] = "Testing 1, 2, 3";
  char buffer[1024];
  size_t bytesRead = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead == utf8size(expectedBytes));
  REQUIRE(utf8cmp(expectedBytes, buffer) == 0);

  VFile_Close(vfh);
}

TEST_CASE("Write Testing 1, 2, 3 text file OsFile (C)", "[VFile]") {
  VFile_Handle vfh = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Write);
  REQUIRE(vfh);
  static char expectedBytes[] = "Testing 1, 2, 3";

  size_t bytesWritten = VFile_Write(vfh, expectedBytes, strlen(expectedBytes));
  REQUIRE(bytesWritten == strlen(expectedBytes));

  // there not really an easy way of testing flush so we test it doesn't crash
  VFile_Flush(vfh);
  VFile_Close(vfh);

  // verify write
  VFile_Handle vfhr = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Read);
  REQUIRE(vfhr);
  char buffer[1024];
  size_t bytesRead = VFile_Read(vfhr, buffer, 1024);
  REQUIRE(bytesRead == utf8size(expectedBytes));
  REQUIRE(utf8cmp(expectedBytes, buffer) == 0);

  VFile_Close(vfhr);
}

TEST_CASE("Seek & Tell Testing 1, 2, 3 text file OsFile (C)", "[VFile]") {
  VFile_Handle vfh = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Read);
  REQUIRE(vfh);

  static char expectedBytes[] = "Testing 1, 2, 3";
  char buffer[1024];
  size_t totalLen = utf8size(expectedBytes);

  bool seek0 = VFile_Seek(vfh, 4, VFile_SD_Begin);
  REQUIRE(seek0);
  REQUIRE(VFile_Tell(vfh) == 4);
  size_t bytesRead0 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead0 == utf8size(&expectedBytes[4]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  VFile_Seek(vfh, 4, VFile_SD_Begin);
  bool seek1 = VFile_Seek(vfh, 4, VFile_SD_Current);
  REQUIRE(seek1);
  REQUIRE(VFile_Tell(vfh) == 8);
  size_t bytesRead1 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead1 == utf8size(&expectedBytes[8]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  bool seek2 = VFile_Seek(vfh, -4, VFile_SD_End);
  REQUIRE(seek2);
  REQUIRE(VFile_Tell(vfh) == totalLen - 4);
  size_t bytesRead2 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead2 == utf8size(&expectedBytes[totalLen - 4]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  VFile_Close(vfh);
}

TEST_CASE("Size OsFile (C)", "[VFile]") {
  VFile_Handle vfh = VFile_FromFile("test_data/al2o3_vfile/test.txt", Os_FM_Read);
  REQUIRE(vfh);

  size_t size = VFile_Size(vfh);
  REQUIRE(size == 15);

  VFile_Close(vfh);
}

TEST_CASE("Open and close MemFile (C)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile_Handle vfh = VFile_FromMemory(testData, sizeof(testData), false);
  REQUIRE(vfh);
  REQUIRE(utf8icmp(VFile_GetName(vfh), "*NO_NAME*") == 0);
  VFile_Close(vfh);
}

TEST_CASE("Read Testing 1, 2, 3 text file MemFile (C)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile_Handle vfh = VFile_FromMemory(testData, sizeof(testData) - 1, false);
  REQUIRE(vfh);

  static char expectedBytes[] = "Testing 1, 2, 3";
  char buffer[1024];
  size_t bytesRead = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead == utf8size(expectedBytes));
  REQUIRE(utf8cmp(expectedBytes, buffer) == 0);

  VFile_Close(vfh);
}

TEST_CASE("Write Testing 1, 2, 3 text file MemFile (C)", "[VFile]") {
  static char testData[1024];
  VFile_Handle vfh = VFile_FromMemory(testData, sizeof(testData), false);
  REQUIRE(vfh);

  static char expectedBytes[] = "Testing 1, 2, 3";
  size_t bytesWritten = VFile_Write(vfh, expectedBytes, utf8size(expectedBytes));
  REQUIRE(bytesWritten == utf8size(expectedBytes));

  // there not really an easy way of testing flush so we test it doesn't crash
  VFile_Flush(vfh);
  VFile_Close(vfh);

  // verify write
  VFile_Handle vfhr = VFile_FromMemory(testData, bytesWritten, false);
  REQUIRE(vfhr);
  char buffer[1024];
  size_t bytesRead = VFile_Read(vfhr, buffer, 1024);
  REQUIRE(bytesRead == utf8size(expectedBytes));
  REQUIRE(utf8cmp(expectedBytes, buffer) == 0);

  VFile_Close(vfhr);
}

TEST_CASE("Seek & Tell Testing 1, 2, 3 text file MemFile (C)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile_Handle vfh = VFile_FromMemory(testData, sizeof(testData) - 1, false);
  REQUIRE(vfh);

  static char expectedBytes[] = "Testing 1, 2, 3";
  char buffer[1024];
  size_t totalLen = utf8size(expectedBytes);

  bool seek0 = VFile_Seek(vfh, 4, VFile_SD_Begin);
  REQUIRE(seek0);
  REQUIRE(VFile_Tell(vfh) == 4);
  size_t bytesRead0 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead0 == utf8size(&expectedBytes[4]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  VFile_Seek(vfh, 4, VFile_SD_Begin);
  bool seek1 = VFile_Seek(vfh, 4, VFile_SD_Current);
  REQUIRE(seek1);
  REQUIRE(VFile_Tell(vfh) == 8);
  size_t bytesRead1 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead1 == utf8size(&expectedBytes[8]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  bool seek2 = VFile_Seek(vfh, -4, VFile_SD_End);
  REQUIRE(seek2);
  REQUIRE(VFile_Tell(vfh) == totalLen - 4);
  size_t bytesRead2 = VFile_Read(vfh, buffer, 1024);
  REQUIRE(bytesRead2 == utf8size(&expectedBytes[totalLen - 4]));
  REQUIRE(VFile_Tell(vfh) == utf8size(expectedBytes));

  VFile_Close(vfh);
}

TEST_CASE("Size MemFile (C)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile_Handle vfh = VFile_FromMemory(testData, sizeof(testData) - 1, false);
  REQUIRE(vfh);

  size_t size = VFile_Size(vfh);
  REQUIRE(size == 15);

  VFile_Close(vfh);
}

TEST_CASE("Open and close MemFile (CPP)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile::File *vfh = VFile::File::FromMemory(testData, sizeof(testData), false);
  REQUIRE(vfh);
  REQUIRE(stricmp(vfh->GetName(), "*NO_NAME*") == 0);
  vfh->Close();

}

TEST_CASE("Scoped Open and close MemFile (CPP)", "[VFile]") {

  static char testData[] = "Testing 1, 2, 3";

  VFile::ScopedFile vfh = VFile::File::FromMemory(testData, sizeof(testData), false);
  REQUIRE(vfh);
  REQUIRE(stricmp(vfh->GetName(), "*NO_NAME*") == 0);
}