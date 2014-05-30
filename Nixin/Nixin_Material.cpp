#include "Nixin_Material.h"


// Public:




//
// Material
// Constructs a new NEMaterial with no texture.
//
Nixin::Material::Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Colour initialSpecularColour, const float initialReflectiveness )
{
	diffuseColour		= initialDiffuseColour;
	ambientColour		= initialAmbientColour;
	reflectiveness		= initialReflectiveness;
}



//
// Material
// Constructs a new NEMaterial with a texture.
//
Nixin::Material::Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Colour initialSpecularColour, const float initialReflectiveness, const Texture* materialTexture )
{
	diffuseColour		= initialDiffuseColour;
	ambientColour		= initialAmbientColour;
	specularColour		= initialSpecularColour;
	reflectiveness		= initialReflectiveness;
	texture			= materialTexture;
}



//
// NEMaterial
// Constructs a new NEMaterial with a texture.
//
Nixin::Material::Material( const Colour& initialDiffuseColour, const Colour& initialAmbientColour, const Texture* initialSpecularMap, const float initialReflectiveness, const Texture* materialTexture )
{
	diffuseColour		= initialDiffuseColour;
	ambientColour		= initialAmbientColour;
	specularMap		= initialSpecularMap;
	reflectiveness		= initialReflectiveness;
	texture			= materialTexture;
}



//
// ~NEMaterial
//
Nixin::Material::~Material()
{
	// Nothing to dispose of.
}



//
// GetDiffuseColour
//
const Nixin::Colour Nixin::Material::GetDiffuseColour() const
{
	return diffuseColour;
}



//
// SetDiffuseColour
//
void Nixin::Material::SetDiffuseColour( const Colour& newDiffuseColour )
{
	diffuseColour = newDiffuseColour;
}



//
// GetAmbientColour
//
const Nixin::Colour Nixin::Material::GetAmbientColour() const
{
	return ambientColour;
}



//
// SetAmbientColour
//
void Nixin::Material::SetAmbientColour( const Colour& newAmbientColour )
{
	ambientColour = newAmbientColour;
}



//
// GetSpecularColour
//
const Nixin::Colour Nixin::Material::GetSpecularColour() const
{
	return specularColour;
}



//
// SetSpecularColour
//
void Nixin::Material::SetSpecularColour( const Colour& newSpecularColour )
{
	specularColour = newSpecularColour;
}



//
// GetReflectiveness
//
const float Nixin::Material::GetReflectiveness() const
{
	return reflectiveness;
}



//
// SetReflectiveness 
//
void Nixin::Material::SetReflectiveness( const float newReflectiveness  )
{
	reflectiveness = newReflectiveness;
}



//
// SetNewTexture
// Replaces the current texture with a new one. If no
// texture is currently set, it will set one.
//
void Nixin::Material::SetNewTexture( const Texture* newTexture )
{
	texture =  newTexture;
}



//
// RemoveTexture
// Deletes the current texture if one is set.
//
void Nixin::Material::RemoveTexture()
{
	texture = nullptr;
}



//
// GetTexture
//
const Nixin::Texture* Nixin::Material::GetTexture() const
{
	return texture;
}



//
// GetTextured
//
const bool Nixin::Material::GetTextured() const
{
	return texture != nullptr;
}



//
// RemoveSpecularMap
//
void Nixin::Material::RemoveSpecularMap()
{
	specularMap = nullptr;
}



//
// GetSpecularMap
//
const Nixin::Texture* Nixin::Material::GetSpecularMap() const
{
	return specularMap;
}



//
// SetSpecularMap
//
void Nixin::Material::SetSpecularMap( const Texture* newSpecularMap )
{
	specularMap = newSpecularMap;
}



//
// GetHasSpecularMap
//
const bool Nixin::Material::GetHasSpecularMap() const
{
	return specularMap != nullptr;
}
