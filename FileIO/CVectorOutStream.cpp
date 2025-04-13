#include "COutputStream.h"
#include <cstring>

CVectorOutStream::CVectorOutStream(unsigned size, unsigned endianness)
  : m_Buffer(size, 0),
    m_Endianness(endianness) {}

void* CVectorOutStream::Data() {
  return m_Buffer.data();
}

void* CVectorOutStream::DataAtPosition() {
  return m_Buffer.data() + m_Position;
}

bool CVectorOutStream::IsValid() {
  return !m_Buffer.empty();
}

void CVectorOutStream::Seek(long offset, int origin) {
  long long newPos = 0;

  switch (origin) {
    case SEEK_SET:
      newPos = offset;
      break;
    case SEEK_CUR:
      newPos = static_cast<long long>(m_Position) + offset;
      break;
    case SEEK_END:
      newPos = static_cast<long long>(m_Buffer.size()) + offset;
      break;
  }

  if (newPos >= 0 && static_cast<unsigned long long>(newPos) <= m_Buffer.size())
    m_Position = static_cast<unsigned long long>(newPos);
}

unsigned long long CVectorOutStream::Size() {
  return m_Buffer.size();
}

unsigned long long CVectorOutStream::Tell() {
  return m_Position;
}

void CVectorOutStream::WriteByte(unsigned char byte) {
  if (m_Position >= m_Buffer.size())
    m_Buffer.resize(m_Position + 1);
  m_Buffer[m_Position++] = byte;
}

void CVectorOutStream::WriteBytes(void* data, unsigned size) {
  if (m_Position + size > m_Buffer.size())
    m_Buffer.resize(m_Position + size);
  std::memcpy(&m_Buffer[m_Position], data, size);
  m_Position += size;
}

void CVectorOutStream::WriteLong(long data) {
  uint32_t val = static_cast<uint32_t>(data);
  if (m_Endianness == IOUtil::BigEndian) {
    val = ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
  }
  WriteBytes(&val, 4);
}

void CVectorOutStream::WriteLongLong(long long data) {
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

void CVectorOutStream::WriteToBoundary(unsigned boundary, unsigned value) {
  if (boundary == 0) return;
  unsigned long long rem = m_Position % boundary;
  if (rem != 0) {
    unsigned pad = boundary - static_cast<unsigned>(rem);
    for (unsigned i = 0; i < pad; ++i)
      WriteByte(static_cast<unsigned char>(value));
  }
}
