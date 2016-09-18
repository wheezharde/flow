/* toolchain.h */

#if defined( _MSC_VER )
    /* Microsoft Visual Studio Compiler suite */

    #define TOOLCHAIN_MSVC 1

    #pragma warning( push, 1 )
    #include <malloc.h>
    #include <ctype.h>
    #include <stdint.h>
    #include <string.h>
//    #include <Windows.h>
    #pragma warning( pop )

    #define EXPORT __declspec( dllexport )
    #define NORETURN __declspec(noreturn)

#else /* unknown toolchain */
#error Unknown
#endif /* unknown */

#if !defined( null )
    #define null ( ( void* )0 )
#endif /* !defined( null ) */

#if !defined( align )
    #define align( value, align, type ) ( type )( ( intptr_t )( value ) + ( align - 1 ) & ~( align - 1 ) )
#endif /* !defined( align ) */
