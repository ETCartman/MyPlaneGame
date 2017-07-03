#pragma once
#include "GameObject.h"
class MyHelper :public CGameObject
{
public:
	MyHelper(int x,int y);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + (GAME_WIDTH / 2), m_ptPos.y + MYHELPER_HEIGHT));
	}

private:
	static const int MYHELPER_HEIGHT = 70;
	static CImageList m_Images;

	~MyHelper(void);
};

