#ifndef _NIXIN_COLOUR_H_
#define _NIXIN_COLOUR_H_

#define NUM_COLOUR_COMPONENTS 4

#include <stdint.h>

namespace Nixin
{
	class Colour
	{



	public:



        static const Colour		White;
        static const Colour		Red;
        static const Colour		Green;
        static const Colour		Blue;
        static const Colour     CornflowerBlue;
        static const Colour		Transparent;


		float				r		=	1.0f;
		float				g		=	1.0f;
		float				b		=	1.0f;
		float				a		=	1.0f;



		// Contructors / Destructors
		Colour( const float red, const float green, const float blue, const float alpha );
		Colour();
		~Colour();



		// Operators
		void				operator +=( const Colour& other );
		void				operator -=( const Colour& other );
		bool				operator ==( const Colour& other );
		void				operator ++();
		void				operator --();



	private:




	};
}

#endif

