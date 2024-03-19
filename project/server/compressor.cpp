#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "compressor.hpp"

namespace ilrd
{

Compressor::Compressor()
:   m_compressed(),
    m_decompressed()
{    
    m_defstream.zalloc = Z_NULL;
    m_defstream.zfree = Z_NULL;
    m_defstream.opaque = Z_NULL;

    m_infstream.zalloc = Z_NULL;
    m_infstream.zfree = Z_NULL;
    m_infstream.opaque = Z_NULL;
}

void Compressor::Compress(char *toCompress, size_t bytesToCompress)
{
    assert(toCompress != NULL);

    m_defstream.avail_in = bytesToCompress;    
    m_defstream.next_in = (Bytef *)toCompress;  
    
    m_defstream.avail_out = (uInt)details::MSG_TOTAL_BYTES;                       
    m_defstream.next_out = (Bytef *)m_compressed;
    
    deflateInit(&m_defstream, Z_BEST_COMPRESSION);
    deflate(&m_defstream, Z_FINISH);
    deflateEnd(&m_defstream);
}

void Compressor::UnCompress(Packet *toDecompress, size_t freeBytes, size_t bytesToDecompress)
{
    //wrong!
    assert(toDecompress != NULL);

    m_infstream.avail_in = freeBytes;
    m_infstream.next_in = (Bytef *)toDecompress;

    m_infstream.avail_out = (uInt)bytesToDecompress;
    m_infstream.next_out = (Bytef *)m_decompressed;
     
    inflateInit(&m_infstream);
    inflate(&m_infstream, Z_NO_FLUSH);
    inflateEnd(&m_infstream);
}

}//ilrd



/* EXAMPLE */

int testCompressor()
{
    ilrd::Compressor compressor;  
    // original string len = 36
    char a[50] = "Hello Hello Hello Hello Hello Hello!"; 

    // placeholder for the compressed (deflated) version of "a" 
    char b[50] = {0};

    // placeholder for the UNcompressed (inflated) version of "b"
    char c[50] = {0};
     
    printf("Uncompressed size is: %lu\n", strlen(a));
    printf("Uncompressed string is: %s\n", a);
    printf("\n----------\n\n");

    // STEP 1.
    // deflate a into b. (that is, compress a into b)
    z_stream defstream;
    z_stream infstream;

    defstream.avail_in = (uInt)strlen(a)+1; // number of bytes of data in the buffer referenced by next_in.   
    defstream.next_in = (Bytef *)a; //should point to the data to be decompressed. 
    
    defstream.avail_out = (uInt)sizeof(b); //  bytes of the buffer referenced by next_out                      
    defstream.next_out = (Bytef *)b; // should point to a buffer where decompressed data may be placed.
    
    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);
     
    // This is one way of getting the size of the output
    printf("Compressed size is: %lu\n", strlen(b));
    printf("Compressed string is: %s\n", b);
    printf("\n----------\n\n");

    // STEP 2.
    // inflate b into c
    // zlib struct
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = (uInt)((char*)defstream.next_out - b); // size of input
    infstream.next_in = (Bytef *)b; // input char array
    infstream.avail_out = (uInt)sizeof(c); // size of output
    infstream.next_out = (Bytef *)c; // output char array
     
    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    //return val: Z_STREAM_ENDנרא
    inflateEnd(&infstream);
     
    printf("Uncompressed size is: %lu\n", strlen(c));
    printf("Uncompressed string is: %s\n", c);    

    // make sure uncompressed is exactly equal to original.
    assert(strcmp(a,c)==0);

    return 0;
}