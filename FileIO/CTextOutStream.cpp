#include "COutputStream.h"
#include <cstring>
#include <cstdio>

CTextOutStream::CTextOutStream(void* data, unsigned size, unsigned endianness)
  : m_Data(static_cast<char*>(data)),
    m_Size(size),
    m_Endianness(endianness) {}

void* CTextOutStream::Data() {
  return m_Data;
}

void* CTextOutStream::DataAtPosition() {
  return m_Data + m_Position;
}

bool CTextOutStream::IsValid() {
  return m_Data != nullptr;
}

void CTextOutStream::Seek(long offset, int origin) {
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

unsigned long long CTextOutStream::Size() {
  return m_Size;
}

unsigned long long CTextOutStream::Tell() {
  return m_Position;
}

void CTextOutStream::WriteByte(unsigned char byte) {
  if (m_Position < m_Size)
    m_Data[m_Position++] = static_cast<char>(byte);
}

void CTextOutStream::WriteBytes(void* data, unsigned size) {
  if (m_Position + size > m_Size) return;
  std::memcpy(m_Data + m_Position, data, size);
  m_Position += size;
}

void CTextOutStream::WriteLong(long data) {
  char buffer[32];
  int len = std::snprintf(buffer, sizeof(buffer), "%ld", data);
  if (len > 0)
    WriteBytes(buffer, static_cast<unsigned>(len));
}

void CTextOutStream::WriteLongLong(long long data) {
  char buffer[64];
  int len = std::snprintf(buffer, sizeof(buffer), "%lld", data);
  if (len > 0)
    WriteBytes(buffer, static_cast<unsigned>(len));
}

void CTextOutStream::WriteToBoundary(unsigned boundary, unsigned value) {
  if (boundary == 0) return;
  unsigned long long rem = m_Position % boundary;
  if (rem != 0) {
    unsigned pad = boundary - static_cast<unsigned>(rem);
    for (unsigned i = 0; i < pad; ++i)
      WriteByte(static_cast<char>(value));
  }
}
