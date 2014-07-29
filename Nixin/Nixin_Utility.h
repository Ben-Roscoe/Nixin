#ifndef _NIXIN_UTILITY_H_
#define _NIXIN_UTILITY_H_

#include <vector>
#include <string>
#include <map>
#include <thread>

#include "Nixin_ShaderProgram.h"


namespace Nixin
{

	class Utility
	{



	public:



		static void														InitialiseNEShaders();
		static void														UninitialiseNEShaders();
		static std::vector<std::string>									TokeniseString( const std::string& str, const std::string& dividers, const bool tokenisePerChar, const bool removeDividers );
		static int														GetNextPowerOfTwo( const int x );
		static ShaderProgram&											GetNixinSpriteShader();
		static ShaderProgram&											GetNixinPrimitiveShader();
		static std::string												GetFileText( const std::string& fileName );

        static void                                                     TrimToNext( std::string& str, char c );
        static void                                                     TrimToWhiteSpace( std::string& str );
        static void                                                     TrimLeadingWhiteSpace( std::string& str );
        static void                                                     TrimTrailingWhiteSpace( std::string& str );
        static size_t                                                   IndexOfNextWhiteSpace( const std::string& str );
        static size_t                                                   IndexOfNext( const std::string& str, char c );
        static size_t                                                   FindFirstOf( const std::vector<std::string>& tokens, const std::string& str, size_t& token, size_t start = 0 );





	private:



		static std::map<std::thread::id, ShaderProgram*>				NixinSpriteShader;
		static std::map<std::thread::id, ShaderProgram*>				NixinPrimitiveShader;



	};

}



#endif

