#pragma once

#include "miniz.cpp"
#include <npp/types.h>
#include <npp/option.h>

namespace compress {

  /// Arbitrary data block
  class Block {
    public:

      /// Inner data
      u8* data;
      u64 length;

      /// Create a new instance from raw
      Block(u8 *data, u64 length) {
        this->length = length;
        this->data = (u8 *) malloc(length);
        if (data != NULL)
          memcpy(this->data, data, length);
      }

      /// Create new instance from a string
      Block(string value) {
        auto temp = value.c_str();
        this->length = value.length();
        this->data = (u8 *) malloc(length);
        memcpy(this->data, temp, length);
      }

      /// Convert a Block into a string, as much as possible
      npp::Option<string> AsStr() {
        if (length == 0)
          return npp::Some<string>("");
        else if ((length > 0) && (data != NULL)) {
          auto rtn = string();
          rtn.assign((const char *) data, (size_t) length);
          return npp::Some<string>(rtn);
        }
        return npp::None<string>();
      }

      /// Compress a data block and return a data block
      npp::Option<Block*> Deflate() {
        Block *rtn = new Block(NULL, compressBound(length));
        if (compress_(rtn->data, &rtn->length, data, length) != Z_OK) {
          delete rtn;
          return npp::None<Block*>();
        }
        return npp::Some<Block*>(rtn);
      }

      /// Decompress a data block and return a new data block of size buffer
      /// If buffer < the length of the compressed data, it will return None.
      npp::Option<Block*> Inflate(u64 buffer) {
        Block *rtn = new Block(NULL, buffer);
        if (uncompress(rtn->data, &rtn->length, data, length) != Z_OK) {
          delete rtn;
          return npp::None<Block*>();
        }
        return npp::Some<Block*>(rtn);
      }

      /// Decompress a data block and return a new data block of the best size
      /// This is a binary search for a valid size, and can be very slow!
      /// The maximum size is 10 MB; use Inflate(size) for larger files.
      npp::Option<Block*> Inflate() {
        u64 max_buffer = 1024 * 1024 * 10;
        u64 upper = 1;
        u64 size = 256;
        u64 step = 8;
        Block *rtn = new Block(NULL, size);

        // First find an upper bound that is valid
        while(1) {
          if (!(uncompress(rtn->data, &rtn->length, data, upper) == Z_OK)) {
            upper = upper * 2;
            if (upper > size) {
              delete rtn;
              size = size * step;
              if (size > max_buffer)
                rtn = NULL;
              else
                rtn = new Block(NULL, size);
            }
          }
          else {
            size = rtn->length;
            break;
          }
        }

        // Now return the data in a buffer that big.
        delete rtn;
        return Inflate(size);
      }
  };
}

/*
Memory to Memory Compression

  // Returns Z_OK on success, or one of the error codes from deflate() on failure.
  int compress(Byte *pDest, uLong *pDest_len, const Byte *pSource, uLong source_len);

  // Like compress() but with more control, level may range from 0 (storing) to 9 (max. compression)
  int compress2(Byte *pDest, uLong *pDest_len, const Byte *pSource, uLong source_len, int level);

Memory to Memory Decompression

  // Returns Z_OK on success, or one of the error codes from inflate() on failure.
  int uncompress(Byte *pDest, uLong *pDest_len, const Byte *pSource, uLong source_len);
*/

/*namespace compress {

  // example1.c - Demonstrates miniz.c's compress() and uncompress() functions (same as zlib's).
  // Public domain, May 15 2011, Rich Geldreich, richgel99@gmail.com. See "unlicense" statement at the end of tinfl.c.

  typedef unsigned char uint8;
  typedef unsigned short uint16;
  typedef unsigned int uint;

  // The string to compress.
  static const char *s_pStr = "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
    "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson.";

  int run(int argc, char *argv[])
  {
    uint step = 0;
    int cmp_status;
    uLong src_len = (uLong)strlen(s_pStr);
    uLong cmp_len = compressBound(src_len);
    uLong uncomp_len = src_len;
    uint8 *pCmp, *pUncomp;
    uint total_succeeded = 0;
    (void)argc, (void)argv;

    printf("miniz.c version: %s\n", MZ_VERSION);

    do
    {
      // Allocate buffers to hold compressed and uncompressed data.
      pCmp = (mz_uint8 *)malloc((size_t)cmp_len);
      pUncomp = (mz_uint8 *)malloc((size_t)src_len);
      if ((!pCmp) || (!pUncomp))
      {
        printf("Out of memory!\n");
        return EXIT_FAILURE;
      }

      // Compress the string.
      cmp_status = compress_(pCmp, &cmp_len, (const unsigned char *)s_pStr, src_len);
      if (cmp_status != Z_OK)
      {
        printf("compress() failed!\n");
        free(pCmp);
        free(pUncomp);
        return EXIT_FAILURE;
      }

      printf("Compressed from %u to %u bytes\n", (mz_uint32)src_len, (mz_uint32)cmp_len);

      if (step)
      {
        // Purposely corrupt the compressed data if fuzzy testing (this is a very crude fuzzy test).
        uint n = 1 + (rand() % 3);
        while (n--)
        {
          uint i = rand() % cmp_len;
          pCmp[i] ^= (rand() & 0xFF);
        }
      }

      // Decompress.
      cmp_status = uncompress(pUncomp, &uncomp_len, pCmp, cmp_len);
      total_succeeded += (cmp_status == Z_OK);

      if (step)
      {
        printf("Simple fuzzy test: step %u total_succeeded: %u\n", step, total_succeeded);
      }
      else
      {
        if (cmp_status != Z_OK)
        {
          printf("uncompress failed!\n");
          free(pCmp);
          free(pUncomp);
          return EXIT_FAILURE;
        }

        printf("Decompressed from %u to %u bytes\n", (mz_uint32)cmp_len, (mz_uint32)uncomp_len);

        // Ensure uncompress() returned the expected data.
        if ((uncomp_len != src_len) || (memcmp(pUncomp, s_pStr, (size_t)src_len)))
        {
          printf("Decompression failed!\n");
          free(pCmp);
          free(pUncomp);
          return EXIT_FAILURE;
        }
      }

      free(pCmp);
      free(pUncomp);

      step++;

      // Keep on fuzzy testing if there's a non-empty command line.
    } while (argc >= 2);

    printf("Success.\n");
    return EXIT_SUCCESS;
  }
}
*/
