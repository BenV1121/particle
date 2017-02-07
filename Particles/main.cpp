#include "sfwdraw.h"

using namespace sfw;

void main()
{
	initContext();

	unsigned sprite =
		loadTextureMap("../res/particle_sprite.png");

	while (stepContext())
	{
		drawTexture(sprite, 400, 300, 100, 100, 0, true, 0, RED);
	}

	termContext();
}