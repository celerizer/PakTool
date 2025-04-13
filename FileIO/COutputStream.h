#ifndef FILEIO_COUTPUTSTREAM_H
#define FILEIO_COUTPUTSTREAM_H

#include "FileIO.h"

class COutputStream
{
public:
  virtual ~COutputStream() {}
  virtual void *Data(void);
  virtual void *DataAtPosition(void);
  virtual bool IsValid(void);
  virtual void Seek(long offset, int origin);
  virtual unsigned long long Size(void);
  virtual unsigned long long Tell(void);
  virtual void WriteByte(unsigned char byte);
  virtual void WriteBytes(void *data, unsigned size);
  virtual void WriteLong(long data);
  virtual void WriteLongLong(long long data);
  virtual void WriteToBoundary(unsigned boundary, unsigned value);
};

class CFileOutStream : public COutputStream
{
public:
  CFileOutStream(std::string path, unsigned endianness);
  ~CFileOutStream() override;
  void *Data(void) override;
  void *DataAtPosition(void) override;
  bool IsValid(void) override;
  void Seek(long offset, int origin) override;
  unsigned long long Size(void) override;
  unsigned long long Tell(void) override;
  void WriteByte(unsigned char byte) override;
  void WriteBytes(void *data, unsigned size) override;
  void WriteLong(long data) override;
  void WriteLongLong(long long data) override;
  void WriteToBoundary(unsigned boundary, unsigned value) override;

private:
  FILE* m_File;
  unsigned m_Endianness;
};

class CMemoryOutStream : public COutputStream
{
public:
  CMemoryOutStream(void* data, unsigned size, unsigned endianness);
  ~CMemoryOutStream() override = default;

  void* Data(void) override;
  void* DataAtPosition(void) override;
  bool IsValid(void) override;
  void Seek(long offset, int origin) override;
  unsigned long long Size(void) override;
  unsigned long long Tell(void) override;
  void WriteByte(unsigned char byte) override;
  void WriteBytes(void* data, unsigned size) override;
  void WriteLong(long data) override;
  void WriteLongLong(long long data) override;
  void WriteToBoundary(unsigned boundary, unsigned value) override;

private:
  unsigned char* m_Data = nullptr;
  unsigned long long m_Position = 0;
  unsigned long long m_Size = 0;
  unsigned m_Endianness = 0;
};

class CTextOutStream : public COutputStream
{
public:
  CTextOutStream(void* data, unsigned size, unsigned endianness);
  ~CTextOutStream() override = default;

  void* Data(void) override;
  void* DataAtPosition(void) override;
  bool IsValid(void) override;
  void Seek(long offset, int origin) override;
  unsigned long long Size(void) override;
  unsigned long long Tell(void) override;
  void WriteByte(unsigned char byte) override;
  void WriteBytes(void* data, unsigned size) override;
  void WriteLong(long data) override;
  void WriteLongLong(long long data) override;
  void WriteToBoundary(unsigned boundary, unsigned value) override;

private:
  char* m_Data = nullptr;
  unsigned long long m_Position = 0;
  unsigned long long m_Size = 0;
  unsigned m_Endianness = 0;
};

class CVectorOutStream : public COutputStream
{
public:
  CVectorOutStream(unsigned size, unsigned endianness);
  ~CVectorOutStream() override = default;

  void* Data(void) override;
  void* DataAtPosition(void) override;
  bool IsValid(void) override;
  void Seek(long offset, int origin) override;
  unsigned long long Size(void) override;
  unsigned long long Tell(void) override;
  void WriteByte(unsigned char byte) override;
  void WriteBytes(void* data, unsigned size) override;
  void WriteLong(long data) override;
  void WriteLongLong(long long data) override;
  void WriteToBoundary(unsigned boundary, unsigned value) override;

private:
  std::vector<unsigned char> m_Buffer;
  unsigned long long m_Position = 0;
  unsigned m_Endianness = 0;
};

#endif
