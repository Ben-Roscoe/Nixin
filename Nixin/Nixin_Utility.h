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
		





	private:



		static std::map<std::thread::id, ShaderProgram*>				NixinSpriteShader;
		static std::map<std::thread::id, ShaderProgram*>				NixinPrimitiveShader;



	};

}



#endif

