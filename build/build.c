#include "../library/toolchain.h"
#include "../library/string.h"

#if TOOLCHAIN_MSVC
int __stdcall WinMain( void * inst, void * prev, char * args, int show ) {
    size_t argc;
    const char ** argv;
    char * tmp = null;
    size_t tmp_size = 0;

    ( void )inst;
    ( void )prev;
    ( void )show;

    args = "a b c d";

    tmp_size = strlen( args );
    tmp_size = ( ( ( tmp_size / 2 ) + 3 ) * sizeof( void * ) + tmp_size + 1 );

    tmp = alloca( tmp_size );

    parse_commandline( args, tmp, tmp_size, &argc, &argv );

#else /* unknown */
int main( const int argc, const char ** const argv ) {
#endif /* unknown */

    return 0;
}
