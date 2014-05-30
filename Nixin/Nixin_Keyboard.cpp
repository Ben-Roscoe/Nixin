#include "Nixin_Keyboard.h"



// Initialises static members.
bool Nixin::Keyboard::keys[65536];
int Nixin::Keyboard::inputs;



// Public static:



//
// Initialise
// Set all key flags to 0.
//
void Nixin::Keyboard::Initialise()
{
    for( int i = 0; i < std::numeric_limits<uint16_t>::max(); i++ )
	{
        keys[i] = false;
	}
}



//
// SetKey
// Set a certain key to be either up or down.
//
void Nixin::Keyboard::SetKey( const uint16_t wParam, const bool isDown )
{
	isDown ? inputs++ : inputs--;						// Increases / decreases the inputs count.
    keys[wParam] = isDown;
}



//
// IsKeyDown
// Checks if a key is down.
//
bool Nixin::Keyboard::IsKeyDown( const Key key )
{
    return keys[( uint16_t )key];
}



//
// IsKeyUp
// Checks if a key is up.
//
bool Nixin::Keyboard::IsKeyUp( const Key key )
{
    return !keys[( uint16_t )key];
}



//
// IsAnyKeyDown
// Checks if any key on the keyboard is being pressed.
//
bool Nixin::Keyboard::IsAnyKeyDown()
{
	return ( inputs <= 0 );
}
