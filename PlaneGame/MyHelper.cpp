#include "StdAfx.h"
#include "Myhelper.h"
#include "resource.h"

CImageList MyHelper::m_Images;

MyHelper::MyHelper(int x,int y) :CGameObject(x, y)
{

}

BOOL MyHelper::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP2, RGB(0, 0, 0), 80, 80, 1);
}

MyHelper::~MyHelper(void)
{

}
BOOL MyHelper::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - 8;
	}

	if (m_ptPos.y < -MYHELPER_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
