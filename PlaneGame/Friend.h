#pragma once
#include "Bomb.h"
#include "resource.h"
class Friend :
	public CBomb
{
public:
	Friend(int x,int y);
	static BOOL Load();
	~Friend();

};

