#include <locale>
#include <fstream>

#include "Nixin_Utility.h"
#include "Nixin_Debug.h"



namespace Nixin
{
    std::map<std::thread::id, ShaderProgram*> Utility::NixinSpriteShader;
    std::map<std::thread::id, ShaderProgram*> Utility::NixinPrimitiveShader;


    //
    // GetNixinSpriteShader
    //
    ShaderProgram& Utility::GetNixinSpriteShader()
    {
        return *( NixinSpriteShader[std::this_thread::get_id()] );
    }



    //
    // GetNixinPrimitiveShader
    //
    ShaderProgram& Utility::GetNixinPrimitiveShader()
    {
        return *( NixinPrimitiveShader[std::this_thread::get_id()] );
    }



    //
    // InitialiseNEShaders
    // Initialise all the shaders that are a part of the NE.
    //
    void Utility::InitialiseNEShaders()
    {
        // Set up the default 2D shader.

        NixinSpriteShader[std::this_thread::get_id()] = new ShaderProgram();
        NixinSpriteShader[std::this_thread::get_id()]->AddFile( ShaderFile( "spriteVertex.glsl", GL_VERTEX_SHADER, true ) );
        NixinSpriteShader[std::this_thread::get_id()]->AddFile( ShaderFile( "spriteFragment.glsl", GL_FRAGMENT_SHADER, true ) );
        NixinSpriteShader[std::this_thread::get_id()]->LinkProgram();

        NixinPrimitiveShader[std::this_thread::get_id()] = new ShaderProgram();
        NixinPrimitiveShader[std::this_thread::get_id()]->AddFile( ShaderFile( "primitiveVertex.glsl", GL_VERTEX_SHADER, true ) );
        NixinPrimitiveShader[std::this_thread::get_id()]->AddFile( ShaderFile( "primitiveFragment.glsl", GL_FRAGMENT_SHADER, true ) );
        NixinPrimitiveShader[std::this_thread::get_id()]->LinkProgram();
    }



    //
    // UninitialiseNEShaders
    //
    void Utility::UninitialiseNEShaders()
    {
        delete NixinSpriteShader[std::this_thread::get_id()];
        NixinSpriteShader.erase( std::this_thread::get_id() );

        delete NixinPrimitiveShader[std::this_thread::get_id()];
        NixinPrimitiveShader.erase( std::this_thread::get_id() );
    }



    //
    // TokeniseString
    // Takes a string and returns an std::vector of strings. This vector contains the original string's
    // substrings which are divided by certain characters.
    //
    std::vector<std::string> Utility::TokeniseString( const std::string& str, const std::string& dividers, const bool tokenisePerChar, const bool removeDividers )
    {
        std::vector<std::string>        tokens;
        size_t                          last = 0;

        for( size_t i = 1; i < str.size(); i++ )
        {
            if( dividers.find( str[i] ) )
            {
                if( i - last != 1 && !removeDividers )
                {
                    tokens.push_back( str.substr( last, ( i - last ) ) );
                }
                last = i;
            }
        }
        return tokens;
    }



    //
    // GetNextPowerOfTwo
    // Gets the next power of two after x.
    //
    int Utility::GetNextPowerOfTwo( const int x )
    {
        int					next = 1;

        while( next < x )
        {
            next <<= 1;			// Shift by one bit. Increase by a power of 2 until we are larger than x.
        }
        return next;
    }



    //
    // GetFileText
    // Returns an std::string that contains the file in ASCII characters.
    //
    std::string Utility::GetFileText( const std::string& fileName )
    {
        // File stream.
        std::ifstream				file;
        std::string					contents;
        unsigned int				lineCount	= 0;


        // Open the file.
        file.open( fileName.c_str(), std::fstream::in );
        if( !file.is_open() )
        {
            // Throw if the file failed to open.
            Debug::FatalError( "Could not open file for reading." );
        }

        // Obtain each character in the file and append it to contents.
        while( !file.eof() )
        {
            contents += file.get();
        }

        // Close the file and return the contents.
        file.close();
        return contents;
    }



    //
    // TrimToNext
    //
    void Utility::TrimToNext(std::string &str, char c)
    {
        size_t  i = 0;
        for( ; i < str.size() && str[i] != c; i++ ){}
        str.erase( 0, i );
    }



    //
    // TrimToWhiteSpace
    //
    void Utility::TrimToWhiteSpace( std::string& str )
    {
        size_t  i = 0;
        for( ; i < str.size() && !std::isspace( str[i], std::locale( "C" ) ); i++ ){}
        str.erase( 0, i );
    }



    //
    // TrimLeadingWhiteSpace
    //
    void Utility::TrimLeadingWhiteSpace( std::string& str )
    {
        size_t  i = str.size() - 1;
        for( ; i >= 0 && std::isspace( str[i], std::locale( "C" ) ); i-- ){}
        str.erase( i + 1, ( str.size() - 1 ) - i );
    }



    //
    // TrimTrailingWhiteSpace
    //
    void Utility::TrimTrailingWhiteSpace( std::string& str )
    {
        size_t  i = 0;
        for( ; i < str.size() && std::isspace( str[i], std::locale( "C" ) ); i++ ){}
        str.erase( 0, i );
    }



    //
    // IndexOfNextWhiteSpace
    //
    size_t Utility::IndexOfNextWhiteSpace( const std::string& str )
    {
        size_t  i = 0;
        for( ; i < str.size() && !std::isspace( str[i], std::locale( "C" ) ); i++ ){}
        return i;
    }


    //
    // IndexOfNext
    //
    size_t Utility::IndexOfNext( const std::string& str, char c )
    {
        size_t  i = 0;
        for( ; i < str.size() && str[i] != c; i++ ){}
        return i;
    }



    //
    // FindFirstOf
    //
    size_t Utility::FindFirstOf( const std::vector<std::string>& tokens, const std::string& str, size_t& token, size_t start )
    {
        size_t      closest = str.npos;
        token               = 0;

        for( size_t i = 0; i < tokens.size(); i++ )
        {
            size_t   position = str.find( tokens[i], start );
            if( position < closest )
            {
                closest = position;
                token = i;
            }
        }

        return closest;
    }

}

