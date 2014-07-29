#include "Nixin_Keyboard.h"



namespace Nixin
{



    // Public static:



    //
    // Initialise
    // Set all key flags to 0.
    //
    void Keyboard::Initialise()
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
    void Keyboard::SetKey( QKeyEvent* e )
    {
        if( e->type() == QEvent::KeyPress )
        {
            inputs++;
            keys[e->key()] = true;
        }
        else if( e->type() == QEvent::KeyRelease )
        {
            inputs--;
            keys[e->key()] = false;
        }
    }



    //
    // IsKeyDown
    // Checks if a key is down.
    //
    bool Keyboard::IsKeyDown( int key )
    {
        return keys[key];
    }



    //
    // IsKeyUp
    // Checks if a key is up.
    //
    bool Keyboard::IsKeyUp( int key )
    {
        return !keys[key];
    }



    //
    // IsAnyKeyDown
    // Checks if any key on the keyboard is being pressed.
    //
    bool Keyboard::IsAnyKeyDown()
    {
        return ( inputs <= 0 );
    }


}
