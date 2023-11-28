#include "TextureComponent.h"

TextureComponent::TextureComponent()
{
	componentType = TEXTURE;
}

void TextureComponent::setTexture(Texture2D::Ptr texture)
{
		_texture = texture;
}

Texture2D::Ptr TextureComponent::getTexture()
{
	return _texture;
}
