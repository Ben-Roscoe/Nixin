#ifndef _NIXIN_QUATERNION_H_
#define _NIXIN_QUATERNION_H_

#include "Nixin_Point.h"
#include "Nixin_Matrix.h"

namespace Nixin
{

	class Quaternion
	{



	public:



		float															w;
		float															x;
		float															y;
		float															z;



		static Quaternion												Multiply( const Quaternion& a, const Quaternion& b );
		static Point													Multiply( const Quaternion& q, const Point& p );

		Quaternion();
		Quaternion( const float rotation, const Point& axis );
		~Quaternion();

		Matrix													    	ToMatrix();
		void															Normalise();

		Quaternion													    GetConjugate() const;
		Point															GetForwardVector() const;




	private:




	};

}



#endif

