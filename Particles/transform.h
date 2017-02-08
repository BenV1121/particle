#pragma once

#include "sfwdraw.h"
#include "maths.h"
#include "ObjectPool.h"

using namespace sfw;

struct transform
{
	vec2 position, scale;
	float angle;
};

struct rigitbody
{
	vec2 velocity, acceleration;
	void integrate(transform &T, float dt)
	{
		velocity = velocity + acceleration * dt;
		T.position = T.position + velocity * dt;
	}
};

struct lifetime
{
	float time = 0, lifespan;
	void age(float dt) { time += dt; }
	bool isAlive() const { time < lifespan; }
	float pctAlive() const { return time / lifespan; }
};

struct sprite
{
	size_t sprite_id;
	color tint;
	
	void draw(const transform &T)
	{
	drawTexture(sprite_id, T.position.x, T.position.y, T.scale.x, T.scale.y, T.angle, true, 0, tint.ui_color);
	}
};

struct controller
{
	float speed;
	void poll(transform&T, rigitbody &RB)
	{
		vec2 mouse = vec2{ getMouseX(), getMouseY() };

		RB.acceleration = normal(T.position - mouse) * speed;
	}
};

struct particle
{
	vec2 sDim, eDim;
	color sColor, eColor;

	void update(const lifetime &life, transform &trans, sprite &sprt)
	{
		trans.scale = lerp(sDim, eDim, life.pctAlive());
		sprt.tint = lerp(sColor, eColor, life.pctAlive());
	}
};

template<typename T>
using handle = ObjectPool<T>::iterator;
