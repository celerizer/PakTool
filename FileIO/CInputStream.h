#ifndef FILEIO_CINPUTSTREAM_H
#define FILEIO_CINPUTSTREAM_H

#include "FileIO.h"

class CInputStream
{
public:
  CInputStream(void *data, uint32_t size, unsigned endianness);

  bool IsValid(void);

  long PeekLong(void);

  short PeekShort(void);

  void ReadBytes(void *data, unsigned size);

  uint32_t ReadLong(void);

  uint64_t ReadLongLong(void);

  short ReadShort(void);

  std::string ReadString(void);

  void Seek(long offset, int origin);

  void SeekToBoundary(long offset);

  unsigned long long Tell(void) { return m_Pos; }

private:
  unsigned long long m_Pos = 0;
};

class CMemoryInStream : public CInputStream
{
public:
  CMemoryInStream(void *data, uint32_t size, unsigned endianness);
};

#endif
