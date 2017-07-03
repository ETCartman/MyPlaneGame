#pragma once
#include "GameObject.h"

class CEnemyboss :
	public CGameObject
{
public:
	CEnemyboss(void);
	~CEnemyboss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYBOSS_WIDETH, m_ptPos.y + ENEMYBOSS_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	BOOL Fired();
private:
	static const int ENEMYBOSS_HEIGHT = 197;
	static const int ENEMYBOSS_WIDETH = 260;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
					 //ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ
	int x;
public:
	int HPBOSS;//BOSSѪ��
};

