#ifndef _NIXIN_MEMORY_UTILITY_H_
#define _NIXIN_MEMORY_UTILITY_H_


#include <memory>
#include <cstring>
#include "Nixin_Debug_Output.h"

namespace Nixin
{
	class MemoryUtility
	{




	public:




		//
		// MemAssign
		// Assigns value so that copy constructors or assignment operators are run.
		//
		template<typename type>
		static void MemAssign( type* destination, const type& value, const unsigned int count )
		{
			for( unsigned int i = 0; i < count; i++ )
			{
				destination[i] = value;
			}
		}



		//
		// MemSet
		// Sets memory. No copy constructors or assignment operators are run.
		//
		template<typename type>
		static void MemSet( type* destination, const type& value, const unsigned int count )
		{
			for( unsigned int i = 0; i < count; i++ )
			{
				std::memcpy( &destination[i], value, 1 );
			}
		}



		//
		// MemCpy
		//
		template<typename type>
		static void MemCpy( type* const destination, const type* const source, const unsigned int count )
		{
			std::memcpy( destination, source, count * sizeof( type ) );
		}



		//
		// SwapBytes
		// Swaps endiness up to 8 bytes. Anymore than this should be split into multiple method calls.
		//
		template<typename type>
		static void SwapBytes( type& x )
		{
			if( sizeof( type ) == 2 )
			{
				unsigned char* bytes = ( unsigned char* )&x;
				unsigned char  temp  = bytes[0];

				temp = bytes[0];
				bytes[0] = bytes[1];
				bytes[1] = temp;
			}
			else if( sizeof( type ) == 4 )
			{
				unsigned char* bytes = ( unsigned char* )&x;
				unsigned char  temp  = bytes[0];

				temp = bytes[0];
				bytes[0] = bytes[3];
				bytes[3] = temp;
					
				temp = bytes[1];
				bytes[1] = bytes[2];
				bytes[2] = temp;
			}
			else if( sizeof( type ) == 8 )
			{
				unsigned char* bytes = ( unsigned char* )&x;
				unsigned char  temp  = bytes[0];

				temp = bytes[0];
				bytes[0] = bytes[7];
				bytes[7] = temp;
					
				temp = bytes[1];
				bytes[1] = bytes[6];
				bytes[6] = temp;

				temp = bytes[2];
				bytes[2] = bytes[5];
				bytes[5] = temp;

				temp = bytes[3];
				bytes[3] = bytes[4];
				bytes[4] = temp;
			}
			else if( sizeof( type ) > 8 || sizeof( type ) % 2 != 0 )
			{
				// Warn invalid byte count.
				Debug::Warning( "Tried to swap invalid number of bytes. Bytes were not swapped." );
			}
		}



		//
		// GetAlignedSize
		// Return size aligned to 'align' number of bytes.
		//
		static const size_t	GetAlignedSize( const size_t size, const size_t align )
		{
			return ( size - ( size % align ) ) + ( ( size % align ) == 0 ? 0 : align );
		}




	};
}

#endif