#pragma once
#include "GameObject.h"

class CMyPlane :public CGameObject
{
public:
	CMyPlane(void);
	~CMyPlane(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}
	void levelUp();

	void GOD()  //无敌模式
	{
		if (m_God == 1)
		{
			m_God = 0;
			m_HP = 100;
		}
		else
		{
			m_God = 1;
		}
	}

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
	}

	//是否可以开火发射导弹
	BOOL Fired();
	void save();
	void load();
public:
	static const int PLANE_WIDTH=50;
	static const int PLANE_HEIGHT=60;
	int m_HP; //生命值
	int m_God; //无敌模式
	int m_Score; //分数
	int m_Life; //生命值
	int m_Level; //等级

protected:
	
	static CImageList m_Images;
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
	int    m_nWait;//发射延时
	
};
