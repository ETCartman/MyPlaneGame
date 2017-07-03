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

	void GOD()  //�޵�ģʽ
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

	//�Ƿ���Կ����䵼��
	BOOL Fired();
	void save();
	void load();
public:
	static const int PLANE_WIDTH=50;
	static const int PLANE_HEIGHT=60;
	int m_HP; //����ֵ
	int m_God; //�޵�ģʽ
	int m_Score; //����
	int m_Life; //����ֵ
	int m_Level; //�ȼ�

protected:
	
	static CImageList m_Images;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
	
};
