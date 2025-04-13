#ifndef FILEIO_COUTPUTSTREAM_H
#define FILEIO_COUTPUTSTREAM_H

#include "FileIO.h"

class COutputStream
{
public:
  void *Data(void);

  void *DataAtPosition(void);

  bool IsValid(void);

  void Seek(long offset, int origin);

  unsigned long long Size(void);

  unsigned long long Tell(void) { return m_Pos; }

  void WriteByte(unsigned char byte);

  void WriteBytes(void *data, unsigned size);

  void WriteLong(long data);

  void WriteLongLong(long long data);

  void WriteToBoundary(unsigned boundary, unsigned value);

private:
  unsigned long long m_Pos = 0;
};

class CFileOutStream : public COutputStream
{
public:
  CFileOutStream(std::string path, unsigned endianness);
};

class CMemoryOutStream : public COutputStream
{
public:
  CMemoryOutStream(void *data, unsigned size, unsigned endianness);
};

class CTextOutStream : public COutputStream
{
public:
  CTextOutStream(void *data, unsigned size, unsigned endianness);
};

class CVectorOutStream : public COutputStream
{
public:
  CVectorOutStream(unsigned size, unsigned endianness);
};

#endif
