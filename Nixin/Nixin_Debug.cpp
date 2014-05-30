#include <fstream>
#include "Nixin_Debug.h"




//
// Assert
// If the predicate is false, output a fatal error and throw an exception.
//
void Nixin::Debug::Assert( const bool predicate, const char* const subject )
{
	if( !predicate )
	{
		std::printf( "Nixin Fatal Error: Assertion failed with subject '" );
		std::printf( subject );
		std::printf( "'\n" );

		// Throw assertion failed exception.
    }
}



//
// PrintFramebufferStatus
//
void Nixin::Debug::PrintFramebufferStatus( GLenum status )
{
    std::cout << "OpenGL Framebuffer Status: ";
    switch( status )
    {
    case GL_FRAMEBUFFER_COMPLETE:
        std::cout << "The framebuffer is complete." << std::endl;
        break;
    case GL_FRAMEBUFFER_UNDEFINED:
        std::cout << "The framebuffer is undefined." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cout << "The framebuffer has all necessary attachments, however one or more are uninitialised." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cout << "The framebuffer is missing a necessary attachment." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cout << "The framebuffer is incomplete for writing." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cout << "The framebuffer is incomplete for reading." << std::endl;
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cout << "The framebuffer is unsupported." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        std::cout << "All attachments on the framebuffer do not have a common sample count." << std::endl;
        break;
    }
}



//
// PrintCurrentGLError
//
GLenum Nixin::Debug::PrintGLError( GLenum error, const std::string& functionName )
{
    if( error != GL_NO_ERROR )
    {
        std::cout << "OpenGL Error in function " << functionName << ": ";
        switch( error )
        {
        case GL_INVALID_ENUM:
            std::cout << "Invalid enum. An unacceptable value was specified for an enumerated argument. Command has been ignored." << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << "A numeric argument is out of range. Command has been ignored." << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << "Attempted to perform an invaild operation given the current state. Command has been ignored." << std::endl;
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << "The framebuffer object is not complete. Command has been ignored." << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << "There is not enough memory left to execute the command. The state of OpenGL is undefined, except for the state of error flags." << std::endl;
            break;
        case GL_STACK_UNDERFLOW:
            std::cout << "An attempt has been made to perform an operation that would cause an internal stack to underflow." << std::endl;
            break;
        case GL_STACK_OVERFLOW:
            std::cout << "An attempt has been made to perform an operation that would cause an internal stack to overflow." << std::endl;
            break;
        }
    }
    return error;
}
