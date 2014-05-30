#ifndef _NIXIN_DEBUG_OUTPUT_H_
#define _NIXIN_DEBUG_OUTPUT_H_


#include <cstdarg>
#include <iostream>
#include <QOpenGLFunctions>


namespace Nixin
{
	class Debug
	{




	public:



		template<typename...Args>
		static void						Warning( const char* const message, Args... args )
		{
			// Print the messages:
			std::printf( "Nixin Warning: " ); 
			std::printf( message, args... );
			std::printf( "\n" );
		}
		template<typename...Args>
		static void						Error( const bool throwException, const char* const message, Args... args )
		{
			// Print the messages:
			std::printf( "Nixin Error: " ); 
			std::printf( message, args... );
			std::printf( "\n" );

			if( throwException )
			{
				// Throw exception.
			}
		}
		template<typename...Args>
		static void						FatalError( const char* const message, Args... args )
		{
			// Print the messages:
			std::printf( "Nixin Fatal Error: " ); 
			std::printf( message, args... );
			std::printf( "\n" );

			// Throw exception.
		}
		template<typename...Args>
		static void						Write( const char* const messsage, Args... args )
		{
			// Print the messages:
			std::printf( messsage, args... );
		}
		static void						Assert( const bool predicate, const char* const subject );
        static void                     PrintFramebufferStatus( GLenum status );
        static GLenum                   PrintGLError( GLenum status, const std::string& functionName );



	private:



		static const unsigned int		maxMessageLength = 2048;
	


	};
}



#endif
