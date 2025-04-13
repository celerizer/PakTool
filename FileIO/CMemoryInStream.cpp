#include "CInputStream.h"
#include <cstring>

CMemoryInStream::~CMemoryInStream() {
  // Nothing to clean up; we don't own the memory
}

void CMemoryInStream::ReadBytes(void* data, unsigned size) {
  if (!m_Data || m_Position + size > m_Size) return;
  std::memcpy(data, m_Data + m_Position, size);
  m_Position += size;
}

uint32_t CMemoryInStream::ReadLong(void) {
  if (m_Position + 4 > m_Size) return 0;
  uint32_t val = 0;
  std::memcpy(&val, m_Data + m_Position, 4);
  m_Position += 4;

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0xFF000000) >> 24) |
          ((val & 0x00FF0000) >> 8)  |
          ((val & 0x0000FF00) << 8)  |
          ((val & 0x000000FF) << 24);
  }

  return val;
}

uint64_t CMemoryInStream::ReadLongLong(void) {
  if (m_Position + 8 > m_Size) return 0;
  uint64_t val = 0;
  std::memcpy(&val, m_Data + m_Position, 8);
  m_Position += 8;

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

short CMemoryInStream::ReadShort(void) {
  if (m_Position + 2 > m_Size) return 0;
  short val = 0;
  std::memcpy(&val, m_Data + m_Position, 2);
  m_Position += 2;

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
  }

  return val;
}

std::string CMemoryInStream::ReadString(void) {
  std::string result;
  while (m_Position < m_Size && m_Data[m_Position] != '\0') {
    result += static_cast<char>(m_Data[m_Position++]);
  }
  if (m_Position < m_Size) m_Position++; // skip null terminator
  return result;
}

void CMemoryInStream::Seek(long offset, int origin) {
  switch (origin) {
    case SEEK_SET:
      m_Position = offset;
      break;
    case SEEK_CUR:
      m_Position += offset;
      break;
    case SEEK_END:
      m_Position = m_Size + offset;
      break;
  }

  if (m_Position > m_Size) m_Position = m_Size;
}

void CMemoryInStream::SeekToBoundary(long boundary) {
  if (boundary <= 0) return;
  unsigned long long remainder = m_Position % boundary;
  if (remainder != 0) {
    m_Position += (boundary - remainder);
    if (m_Position > m_Size) m_Position = m_Size;
  }
}

long CMemoryInStream::PeekLong(void) {
  if (m_Position + 4 > m_Size) return 0;
  uint32_t val = 0;
  std::memcpy(&val, m_Data + m_Position, 4);

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0xFF000000) >> 24) |
          ((val & 0x00FF0000) >> 8)  |
          ((val & 0x0000FF00) << 8)  |
          ((val & 0x000000FF) << 24);
  }

  return static_cast<long>(val);
}

short CMemoryInStream::PeekShort(void) {
  if (m_Position + 2 > m_Size) return 0;
  short val = 0;
  std::memcpy(&val, m_Data + m_Position, 2);

  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
  }

  return val;
}
