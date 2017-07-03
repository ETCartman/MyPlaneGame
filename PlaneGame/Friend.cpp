#include "stdafx.h"
#include "Friend.h"


Friend::Friend(int x,int y) : CBomb(x, y)
{

}
BOOL Friend::Load()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP2, RGB(0, 0, 0), 84, 84, 1);
}

Friend::~Friend()
{
}
