#ifndef _NIXIN_MATERIAL_H_
#define _NIXIN_MATERIAL_H_

#include "Nixin_Colour.h"
#include "Nixin_Texture.h"



namespace Nixin
{
	class Material
	{



	public:



		// Constructors / Destructors.
		Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Colour initialSpecularColour, const float initialReflectiveness );
		Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Colour initialSpecularColour, const float initialReflectiveness, const Texture* materialTexture );
		Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Texture* initialSpecularMap, const float initialReflectiveness, const Texture* materialTexture );
		~Material();


		// Get and Set properties.
		const Colour					GetDiffuseColour() const;
		void							SetDiffuseColour( const Colour& newDiffuseColour );
		const Colour					GetAmbientColour() const;
		void							SetAmbientColour( const Colour& newAmbientColour );
		const Colour					GetSpecularColour() const;
		void							SetSpecularColour( const Colour& newSpecularColour );
		const float						GetReflectiveness() const;
		void							SetReflectiveness( const float newReflectiveness );
		const Texture*					GetTexture() const;
		void							SetNewTexture( const Texture* newTexture );
		void							RemoveTexture();
		const Texture*					GetSpecularMap() const;
		void							SetSpecularMap( const Texture* newSpecularMap );
		void							RemoveSpecularMap();
		const bool						GetTextured() const;
		const bool						GetHasSpecularMap() const;


	private:



		Colour							diffuseColour		= Colour( 1.0f, 1.0f, 1.0f, 1.0f );
		Colour							ambientColour		= Colour( 1.0f, 1.0f, 1.0f, 1.0f );			// Ambient colour of the material.
		Colour							specularColour		= Colour( 1.0f, 1.0f, 1.0f, 1.0f );
		const Texture*					texture				= nullptr;
		const Texture*					specularMap			= nullptr;
		float							reflectiveness		= 0.0f;										// Reflectiveness of the material.



	};

}



#endif

