#include "Nixin_Colour.h"



//
// Static const colours.
//
const Nixin::Colour Nixin::Colour::White				= Nixin::Colour( 1.0f, 1.0f, 1.0f, 1.0f );
const Nixin::Colour Nixin::Colour::Red					= Nixin::Colour( 1.0f, 0.0f, 0.0f, 1.0f );
const Nixin::Colour Nixin::Colour::Green				= Nixin::Colour( 0.0f, 1.0f, 0.0f, 1.0f );
const Nixin::Colour Nixin::Colour::Blue					= Nixin::Colour( 0.0f, 0.0f, 1.0f, 1.0f );
const Nixin::Colour Nixin::Colour::CornflowerBlue       = Nixin::Colour( 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 100.0f, 1.0f );
const Nixin::Colour Nixin::Colour::Transparent			= Nixin::Colour( 1.0f, 1.0f, 1.0f, 0.0f );




//
// Colour
// Creates an Colour with the specified components.
//
Nixin::Colour::Colour( const float red, const float green, const float blue, const float alpha )
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}



//
// Colour
// Creates a Colour initialised to white.
//
Nixin::Colour::Colour()
{
}



//
// ~Colour
//
Nixin::Colour::~Colour()
{
}



// Operators



//
// operator +=
//
void Nixin::Colour::operator+=( const Colour& other )
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
}



//
// operator -=
//
void Nixin::Colour::operator-=( const Colour& other )
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
}



//
// operator ==
//
bool Nixin::Colour::operator==( const Colour& other )
{
	return( r == other.r && g == other.g && b == other.b && a == other.a );
}


//
// operator ++
//
void Nixin::Colour::operator++()
{
	r++;
	g++;
	b++;
	a++;
}



//
// operator --
//
void Nixin::Colour::operator--()
{
	r--;
	g--;
	b--;
	a--;
}
