#include "StdAfx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_HEIGHT) + 1;

	//随机确定图像索引
	//m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	//m_nMotion=1;
	//m_ptPos.y=-ENEMY_HEIGHT;
	//if (m_nImgIndex%2!=1)//如果是图像索引是偶数
	{
		m_nMotion = 1;
		m_ptPos.y = -BOSS_HEIGHT;
	}
	//随机确定速度
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP4, RGB(0, 0, 0), 64, 45, 2);
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>20)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}