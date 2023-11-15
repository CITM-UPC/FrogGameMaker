#pragma once
#include "Component.h"

class TextureComponent : public Component {
public:

	TextureComponent() {
		componentType = TEXTURE;
	}

	void setTexture(Texture2D::Ptr texture) {
		_texture = texture;
	}

	Texture2D::Ptr getTexture() {
		return _texture;
	}

protected:

private:
	Texture2D::Ptr _texture = nullptr;
};