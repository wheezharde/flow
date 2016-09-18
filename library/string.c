#include "toolchain.h"
#include "string.h"

int parse_commandline( const char * const str,
                       char * const tmp,
                       const size_t tmp_size,
                       int * const argc,
                       const char *** const argv ) {
    const int32_t state_quote = 1 << 0;
    const int32_t state_text  = 1 << 1;
    const int32_t state_space = 1 << 2;
    const size_t  align_mask  = sizeof( void * ) - 1;
    const size_t  str_length  = strlen( str );
    const uintptr_t tmp_end = ( uintptr_t )tmp + tmp_size;

    char * tmp_cur = tmp;
    int32_t state = state_space;

    size_t i;

    *argv = ( const char ** )( ( uintptr_t )( tmp + str_length + 1 ) + align_mask & ~align_mask );
    *argc = 0;

    if ( ( uintptr_t )*argv > tmp_end ) {
        return -1;
    }

    for ( i = 0; str[ i ]; i++ ) {
        const char ch = str[ i ];

        if ( state & state_quote ) {
            if ( ch == '\"' ) {
                state &= ~state_quote;
            } else {
                *tmp_cur = ch;
                tmp_cur++;
            }
        }

        else if ( ch == '\"' ) {
            state |= state_quote | state_text;
            if ( state & state_space ) {
                ( *argv )[ *argc ] = tmp_cur;
                ( *argc )++;
                if ( ( uintptr_t )( *argv + *argc ) > tmp_end ) {
                    return -1;
                }
                state &= ~state_space;
            }
        }

        else if ( isspace( ch ) ) {
            if ( state & state_text ) {
                *tmp_cur = '\0';
                tmp_cur++;
            }
            state &= ~state_text;
            state |= state_space;
        }

        else {
            state |= state_text;
            if ( state & state_space ) {
                ( *argv )[ *argc ] = tmp_cur;
                ( *argc )++;
                if ( ( uintptr_t )( *argv + *argc ) > tmp_end ) {
                    return -1;
                }
            }
            *tmp_cur = ch;
            tmp_cur++;
            state &= ~state_space;
        }
    }

    *tmp_cur = '\0';
    ( *argv )[ *argc ] = NULL;

    return 0;
}
