#include "CInputStream.h"
#include <cstdio>
#include <cstring>

CFileInStream::CFileInStream(std::string path, unsigned endianness)
  : m_File(nullptr), m_Endianness(endianness) {
  m_File = std::fopen(path.c_str(), "rb");
}

CFileInStream::~CFileInStream() {
  if (m_File) std::fclose(m_File);
}

bool CFileInStream::IsValid(void) {
  return m_File != nullptr;
}

void CFileInStream::ReadBytes(void* data, unsigned size) {
  if (!m_File) return;
  std::fread(data, 1, size, m_File);
}

uint32_t CFileInStream::ReadLong(void) {
  uint32_t val = 0;
  ReadBytes(&val, 4);

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0xFF000000) >> 24) |
          ((val & 0x00FF0000) >> 8)  |
          ((val & 0x0000FF00) << 8)  |
          ((val & 0x000000FF) << 24);
  }

  return val;
}

uint64_t CFileInStream::ReadLongLong(void) {
  uint64_t val = 0;
  ReadBytes(&val, 8);

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0xFF00000000000000ULL) >> 56) |
          ((val & 0x00FF000000000000ULL) >> 40) |
          ((val & 0x0000FF0000000000ULL) >> 24) |
          ((val & 0x000000FF00000000ULL) >> 8)  |
          ((val & 0x00000000FF000000ULL) << 8)  |
          ((val & 0x0000000000FF0000ULL) << 24) |
          ((val & 0x000000000000FF00ULL) << 40) |
          ((val & 0x00000000000000FFULL) << 56);
  }

  return val;
}

short CFileInStream::ReadShort(void) {
  short val = 0;
  ReadBytes(&val, 2);

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
  }

  return val;
}

std::string CFileInStream::ReadString(void) {
  std::string result;
  char ch;
  while (std::fread(&ch, 1, 1, m_File) == 1 && ch != '\0') {
    result += ch;
  }
  return result;
}

void CFileInStream::Seek(long offset, int origin) {
  if (!m_File) return;
  std::fseek(m_File, offset, origin);
}

void CFileInStream::SeekToBoundary(long boundary) {
  if (!m_File || boundary <= 0) return;

  long pos = std::ftell(m_File);
  long remainder = pos % boundary;
  if (remainder != 0) {
    std::fseek(m_File, boundary - remainder, SEEK_CUR);
  }
}

unsigned long long CFileInStream::Tell(void) {
  if (!m_File) return 0;
  return static_cast<unsigned long long>(std::ftell(m_File));
}

long CFileInStream::PeekLong(void) {
  if (!m_File) return 0;
  long pos = std::ftell(m_File);
  uint32_t val = ReadLong();
  std::fseek(m_File, pos, SEEK_SET);
  return static_cast<long>(val);
}

short CFileInStream::PeekShort(void) {
  if (!m_File) return 0;
  long pos = std::ftell(m_File);
  short val = ReadShort();
  std::fseek(m_File, pos, SEEK_SET);
  return val;
}
