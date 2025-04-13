#ifndef FILEIO_H
#define FILEIO_H

#include <stdint.h>
#include <vector>
#include <string>

#include "CInputStream.h"
#include "COutputStream.h"

namespace IOUtil
{
  enum Endianness
  {
    Invalid = 0,
    LittleEndian,
    BigEndian
  };
}

#endif
