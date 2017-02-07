#pragma once

#include "particles.h"

#define PART_SIZE 24

// Factory
class ParticleEmitter
{
	// Data Structure to store all of our particles
	particle particles[PART_SIZE];

	// Update to update the particles


	// Default ranges of values for the particles


	//emmision of particles
	

//	spawnBullet(...);

	void emit();

	float emitRateLo, emitRateHi;
	float emissionTimer;

	vec2  pos;
	unsigned sprite;
	float angLo, andHi; // direction
	float spdLo, spdHi; // speed = velocity
	vec2  dimLoStart, dimHiStart; // range of acceptable starting dimensions
	vec2  dimLoEnd, dimHiEnd;     // range of acceptacble ending dimensions
	color colLoStart, coHiStart; 
	color colLoEnd, coHiEnd;
	float lifespanLo, lifespanHi;

	void update(float dt)
	{
		for (int i = 0; i < PART_SIZE; ++i)
			if (particles[i].isActive())
				particles[i].refresh(dt);

		emissionTimer -= dt;
		if (emissionTimer < 0)
		{
			do
			{
				emit();
			}
			while(emissionTimer += lerp(emitRateLo, emitRateHi, rand01() < 0));
			// emit a particle()
		}
	}
};

