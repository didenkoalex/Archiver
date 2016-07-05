#ifndef __INCLUDE_COMPRESSOR_H
#define __INCLUDE_COMPRESSOR_H

#include "stream.h"

size_t rle_encode(t_stream *istream, t_stream *ostream);

size_t rle_decode(t_stream *istream, t_stream *ostream);

size_t huf_encode(t_stream *istream, t_stream *ostream);

size_t huf_decode(t_stream *istream, t_stream *ostream);

size_t lzw_encode(t_stream *istream, t_stream *ostream);

size_t lzw_decode(t_stream *istream, t_stream *ostream);

#endif //__INCLUDE_COMPRESSOR_H
