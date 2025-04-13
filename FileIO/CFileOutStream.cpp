#include "COutputStream.h"

CFileOutStream::CFileOutStream(std::string path, unsigned endianness)
    : m_Endianness(endianness) {
    m_File = std::fopen(path.c_str(), "wb");
}

CFileOutStream::~CFileOutStream() {
    if (m_File)
        std::fclose(m_File);
}

void* CFileOutStream::Data() {
    return nullptr;
}

void* CFileOutStream::DataAtPosition() {
    return nullptr;
}

bool CFileOutStream::IsValid() {
    return m_File != nullptr;
}

void CFileOutStream::Seek(long offset, int origin) {
    if (m_File)
        std::fseek(m_File, offset, origin);
}

unsigned long long CFileOutStream::Size() {
    if (!m_File) return 0;
    long current = std::ftell(m_File);
    std::fseek(m_File, 0, SEEK_END);
    long size = std::ftell(m_File);
    std::fseek(m_File, current, SEEK_SET);
    return static_cast<unsigned long long>(size);
}

unsigned long long CFileOutStream::Tell() {
    if (!m_File) return 0;
    return static_cast<unsigned long long>(std::ftell(m_File));
}

void CFileOutStream::WriteByte(unsigned char byte) {
    if (m_File)
        std::fwrite(&byte, 1, 1, m_File);
}

void CFileOutStream::WriteBytes(void* data, unsigned size) {
    if (m_File)
        std::fwrite(data, 1, size, m_File);
}

void CFileOutStream::WriteLong(long data) {
    uint32_t val = static_cast<uint32_t>(data);
    if (m_Endianness == IOUtil::BigEndian) {
        val = ((val & 0x000000FF) << 24) |
              ((val & 0x0000FF00) << 8) |
              ((val & 0x00FF0000) >> 8) |
              ((val & 0xFF000000) >> 24);
    }
    WriteBytes(&val, 4);
}

void CFileOutStream::WriteLongLong(long long data) {
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

void CFileOutStream::WriteToBoundary(unsigned boundary, unsigned value) {
    if (boundary == 0) return;
    unsigned long long pos = Tell();
    unsigned rem = static_cast<unsigned>(pos % boundary);
    if (rem != 0) {
        unsigned pad = boundary - rem;
        for (unsigned i = 0; i < pad; ++i)
            WriteByte(static_cast<unsigned char>(value));
    }
}
