#include "COutputStream.h"
#include <cstring>

CMemoryOutStream::CMemoryOutStream(void* data, unsigned size, unsigned endianness)
  : m_Data(reinterpret_cast<unsigned char*>(data)),
    m_Size(size),
    m_Endianness(endianness) {}

void* CMemoryOutStream::Data() {
  return m_Data;
}

void* CMemoryOutStream::DataAtPosition() {
  return m_Data + m_Position;
}

bool CMemoryOutStream::IsValid() {
  return m_Data != nullptr;
}

void CMemoryOutStream::Seek(long offset, int origin) {
  if (!m_Data) return;

  long long newPos = 0;

  switch (origin) {
    case SEEK_SET:
      newPos = offset;
      break;
    case SEEK_CUR:
      newPos = static_cast<long long>(m_Position) + offset;
      break;
    case SEEK_END:
      newPos = static_cast<long long>(m_Size) + offset;
      break;
  }

  if (newPos >= 0 && static_cast<unsigned long long>(newPos) <= m_Size)
    m_Position = static_cast<unsigned long long>(newPos);
}

unsigned long long CMemoryOutStream::Size() {
  return m_Size;
}

unsigned long long CMemoryOutStream::Tell() {
  return m_Position;
}

void CMemoryOutStream::WriteByte(unsigned char byte) {
  if (m_Position < m_Size)
    m_Data[m_Position++] = byte;
}

void CMemoryOutStream::WriteBytes(void* data, unsigned size) {
  if (m_Position + size > m_Size) return;
  std::memcpy(m_Data + m_Position, data, size);
  m_Position += size;
}

void CMemoryOutStream::WriteLong(long data) {
  uint32_t val = static_cast<uint32_t>(data);
  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
  }
  WriteBytes(&val, 4);
}

void CMemoryOutStream::WriteLongLong(long long data) {
  uint64_t val = static_cast<uint64_t>(data);
  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x00000000000000FFULL) << 56) |
        ((val & 0x000000000000FF00ULL) << 40) |
        ((val & 0x0000000000FF0000ULL) << 24) |
        ((val & 0x00000000FF000000ULL) << 8) |
        ((val & 0x000000FF00000000ULL) >> 8) |
        ((val & 0x0000FF0000000000ULL) >> 24) |
        ((val & 0x00FF000000000000ULL) >> 40) |
        ((val & 0xFF00000000000000ULL) >> 56);
  }
  WriteBytes(&val, 8);
}

void CMemoryOutStream::WriteToBoundary(unsigned boundary, unsigned value) {
  if (boundary == 0) return;
  unsigned long long rem = m_Position % boundary;
  if (rem != 0) {
    unsigned pad = boundary - static_cast<unsigned>(rem);
    for (unsigned i = 0; i < pad; ++i)
      WriteByte(static_cast<unsigned char>(value));
  }
}
