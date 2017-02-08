#pragma once

#include "transform.h"

struct Entity
{
	handle<transform>  tran;
	handle<rigitbody>  rdby;
	handle<controller> ctrl;
	handle<sprite>	   sprt;
	handle<lifetime>   life;
	handle<particle>   part;

	void onFree()
	{
		if (tran) tran.free();
		if (rdby) rdby.free();
		if (ctrl) ctrl.free();
		if (sprt) sprt.free();
		if (life) life.free();
		if (part) part.free();
	}
};