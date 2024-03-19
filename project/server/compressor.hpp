#ifndef ILRD_RD61_COMPRESSOR_HPP
#define ILRD_RD61_COMPRESSOR_HPP

#include "common_types.hpp"//packet

#include <zlib.h>

namespace ilrd
{

class Compressor
{
public:
    explicit Compressor();
    //~Compressor() = defult

    void Compress(char *toCmpress, size_t bytes);
    void UnCompress(Packet *toUnCmpress, size_t bytes, size_t bytesToDecompress);

    char* GetCompressed() { return m_compressed; }
    char* GetDecompressed() {return m_decompressed; }

private:
    char m_compressed[details::MSG_TOTAL_BYTES];
    char m_decompressed[details::MSG_TOTAL_BYTES];
    z_stream m_defstream;
    z_stream m_infstream;

};

}//ilrd

#endif