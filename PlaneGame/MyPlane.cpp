#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"
#include <iostream>
#include <fstream> 

using  namespace std;
CImageList CMyPlane::m_Images;

CMyPlane::~CMyPlane(void)
{
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0),m_HP(100),m_God(0),m_Score(0),m_Life(3),m_Level(0)
{
	m_nWait = 0;
	m_ptPos.x = 150;
	m_ptPos.y = 200;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}
void CMyPlane::save() //写入
{
	ofstream out ("userfile//savefile.ak47");
	if (out.is_open())
	{
		out << m_Level << "\n";
		out << m_Score;
		out.close();
	}
}
void CMyPlane::load() //读取
{
	int flag = 0;
	ifstream fin("userfile//savefile.ak47");
	while (fin)
	{
		if (flag == 0)
		{
			fin >> m_Level;
			flag = 1;
		}
		fin >> m_Score;
	}
	
}
BOOL CMyPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP2,RGB(0,0,0),84,84,1);
}

void CMyPlane::levelUp()
{
	if (m_Score >= m_Level * 150) //等级的150倍
	{
		m_Level++;
		m_Score = 0;
	}
}

BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>3)
		m_nWait=0;


	if(!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion * 6;
		m_ptPos.y = m_ptPos.y - m_nVerMotion * 6;
	}

	if(m_ptPos.x>=GAME_WIDTH - PLANE_WIDTH)
		m_ptPos.x =GAME_WIDTH - PLANE_WIDTH;
	if(m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if(m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if(m_ptPos.y>=GAME_HEIGHT - PLANE_HEIGHT)
		m_ptPos.y=GAME_HEIGHT - PLANE_HEIGHT;


	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	return TRUE;
}