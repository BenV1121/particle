#include "sfwdraw.h"
#include "maths.h"
#include <iostream>
#include "particles.h"

using namespace sfw;
using namespace std;

void main()
{
	initContext();

	unsigned sprite =
	loadTextureMap("../res/particle_sprite.png");

	particle part;

	part.sprite = sprite;
	part.pos    = vec2{400,300};
	part.vel    = randDir(0 ,360) * lerp(20, 80, rand01());
	part.sDim   = randRange(vec2{ 8 , 8 },   vec2{ 64, 64 });
	part.eDim   = lerp (vec2{ 256,256 }, vec2{ 512, 512 }, rand01());

	part.sColor.ui_color = RED;
	part.sColor.ui_color = RED;
	part.lifespan = 4.5f;
	part.lifetime = 0;

	//color startColor, endColor;

	//startColor.ui_color = RED;
	//endColor.ui_color = GREEN;
	//float timer = 0;

	while (stepContext())
	{

		float dt = getDeltaTime();

		if (!part.refresh(dt))
		{
			part.pos = vec2{ 400,300 };
			part.vel = randDir(0, 360) * lerp(20, 80, rand01());
			part.sDim = randRange(vec2{ 8 , 8 }, vec2{ 32, 32 });
			part.eDim = lerp(vec2{ 256,256 }, vec2{ 512, 512 }, rand01());
			part.lifetime = 0;
		}
		//timer += getDeltaTime();

		//color currentColor = lerp(startColor, endColor, timer/10.f);

		////cout << currentColor.r << " " << currentColor.g << " " << ;

		//drawTexture(sprite, 400, 300, 100, 100, 0, true, 0, currentColor.ui_color);


	}

	termContext();
}