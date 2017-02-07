#include "sfwdraw.h"
#include "maths.h"
#include <iostream>

using namespace sfw;
using namespace std;

void main()
{
	initContext();

	unsigned sprite =
	loadTextureMap("../res/particle_sprite.png");

	color startColor, endColor;

	startColor.ui_color = RED;
	endColor.ui_color = GREEN;
	float timer = 0;

	while (stepContext())
	{
		timer += getDeltaTime();

		color currentColor = lerp(startColor, endColor, timer/10.f);

		//cout << currentColor.r << " " << currentColor.g << " " << ;

		drawTexture(sprite, 400, 300, 100, 100, 0, true, 0, currentColor.ui_color);
	}

	termContext();
}