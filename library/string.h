/* string.h */

#include "toolchain.h"

/*
  input:
    str not null
    tmp not null
    tmp_size >= ( ( ( strlen( string ) / 2 ) + 3 ) * sizeof( void * ) + strlen( string ) + 1 ) bytes
      worst case, every arg is one character: 'a b c d'
        argv[ 4 ] + null + "a\0b\0c\0d\0"
        48 of 56 characters used
      best case, one argument: 'abcd'
        argv[ 1 ] + null + "abcd\0"
        21 of 56 characters used
      one extra sizeof( void * ) is required to guarantee alignment
  output:
    argc receives number of arguments stored to argv
    argv is an array of argc null terminated strings
  return:
    0 on success
    error code on failure
*/
int parse_commandline( const char * const str,
                       char * const tmp,
                       const size_t tmp_size,
                       size_t * const argc,
                       const char *** const argv );
