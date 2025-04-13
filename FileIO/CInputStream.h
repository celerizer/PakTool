#ifndef FILEIO_CINPUTSTREAM_H
#define FILEIO_CINPUTSTREAM_H

#include "FileIO.h"

class CInputStream
{
public:
  CInputStream();
  virtual ~CInputStream();

  virtual bool IsValid(void);

  virtual long PeekLong(void);

  virtual short PeekShort(void);

  virtual void ReadBytes(void *data, unsigned size);

  virtual uint32_t ReadLong(void);

  virtual uint64_t ReadLongLong(void);

  virtual short ReadShort(void);

  virtual std::string ReadString(void);

  virtual void Seek(long offset, int origin);

  virtual void SeekToBoundary(long offset);

  virtual unsigned long long Tell(void);
};

class CFileInStream : public CInputStream
{
public:
  CFileInStream(std::string path, unsigned endianness);
  ~CFileInStream() override;
  bool IsValid(void) override;
  long PeekLong(void) override;
  short PeekShort(void) override;
  void ReadBytes(void *data, unsigned size) override;
  uint32_t ReadLong(void) override;
  uint64_t ReadLongLong(void) override;
  short ReadShort(void) override;
  std::string ReadString(void) override;
  void Seek(long offset, int origin) override;
  void SeekToBoundary(long offset) override;
  unsigned long long Tell(void) override;

private:
  unsigned m_Endianness;
  FILE *m_File = nullptr;
};

class CMemoryInStream : public CInputStream
{
public:
  CMemoryInStream(void *data, unsigned long long size, unsigned endianness)
  {
    m_Data = reinterpret_cast<unsigned char*>(data);
    m_Endianness = endianness;
    m_Size = size;
  }
  ~CMemoryInStream() override;
  bool IsValid(void) override;
  long PeekLong(void) override;
  short PeekShort(void) override;
  void ReadBytes(void *data, unsigned size) override;
  uint32_t ReadLong(void) override;
  uint64_t ReadLongLong(void) override;
  short ReadShort(void) override;
  std::string ReadString(void) override;
  void Seek(long offset, int origin) override;
  void SeekToBoundary(long offset) override;
  unsigned long long Tell(void) override;

private:
  unsigned char *m_Data = nullptr;
  unsigned m_Endianness;
  unsigned long long m_Position = 0;
  unsigned long long m_Size = 0;
};

#endif
