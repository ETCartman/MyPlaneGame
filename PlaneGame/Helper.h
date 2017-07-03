#pragma once
#include "MyPlane.h"
class Helper :
	public CMyPlane
{
public:
	Helper(int x, int y);
	static BOOL LoadImage();
	~Helper();
};

