// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
#include "MyHelper.h"
#include "Friend.h"
#include "Boss.h"
#include "EnemyBoss.h"
#include "UpDate.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CUpDate update;

// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	
	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	
	
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	




	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	
	
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CMyPlane::LoadImage();
	MyHelper::LoadImage();
	//Friend::Load();
	CBoss::LoadImage();
	CEnemyboss::LoadImage();

	//��������(ս��)
	m_pMe = new CMyPlane;
	m_pMe->load();
	//������Ϸ
	system("del OldGame.exe");
	if (update.CheckNewVersion())
	{
		if (AfxMessageBox(L"��Ϸ�������°汾�Ƿ���£�", MB_YESNO) != 6)
		{
			

		}
		else
		{
			system("ren PlaneGame.exe OldGame.exe");
			update.GetNewVersion();
			
			if (AfxMessageBox(L"���½�����������Ϸ��", MB_YESNO))
			{
				
				exit(0);
			}
		}
	}

	
	


	if (AfxMessageBox(L"ֱ�ӿ�ʼ��Ϸ���鿴��Ϸ˵���밴����", MB_YESNO) != 6)
	{
		AfxMessageBox(L"WASD������ս�����򣬿ո�����,G�������޵�ģʽ,P����ͣ����ʼ����ֵΪ100������һ���л���10�֡�\n ��Ϸ��ʼ���Զ���ȡ�浵���������Զ��洢");
	}
	SetTimer(1,30,NULL);

	return TRUE;
}
int CPlaneGameView::count = 0;
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	//��ͼԭ��λͼ�Ƚ����ڴ��豸
	CBitmap bmpDraw;//����һ��λͼ����
	CDC memDC;//�����ڴ��豸
			  //1.����λͼ


		bmpDraw.LoadBitmap(IDB_BITMAP1);

	//2.�����ڴ��豸
	memDC.CreateCompatibleDC(pMemDC);//��memDC��pDC����

									 //3.��λͼѡ���ڴ��豸
	memDC.SelectObject(&bmpDraw);
	pMemDC->BitBlt(0, 0, 900, 2990, &memDC, 0, 0, SRCCOPY);
	//����
	CRect m_client;
	GetClientRect(&m_client);

	CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);

	pMemDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &memDC, 0, 0, SRCCOPY);
	pMemDC->BitBlt(0, 0, m_client.Width(), count, &memDC, 0, m_client.Height() - count, SRCCOPY);
	pMemDC->BitBlt(0, count, m_client.Width(), m_client.Height() - count, &memDC, 0, 0, SRCCOPY);
	count += 1;
	if (count>m_client.Height())
		count = 0;
	memDC.SelectObject(pbmpOld);


	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	   wsprintf(hpleft, L"����ֵ:%d ", m_pMe->m_HP);
	   pMemDC->SetTextColor(RGB(225, 0, 0));//����������ɫ
	   pMemDC->TextOutW(GAME_WIDTH / 3 + 300, 5, hpleft, _tcslen(hpleft));

	   wsprintf(score, L"�÷�:%d / %d", m_pMe->m_Score, m_pMe->m_Level * 150);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(2, 2, score, _tcslen(score));

	   wsprintf(score, L"�ȼ�:%d", m_pMe->m_Level);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(2, 20, score, _tcslen(score));

	   wsprintf(lifeleft, L"������:%d", m_pMe->m_Life);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(GAME_WIDTH / 3 + 300, 25, lifeleft, _tcslen(lifeleft));
	 
	}
	
	else
	{   //Game Over
		/*CString str=_T("��Ϸ����!,���ĵȼ���Ϣ�ѱ��棡");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
		*/
		KillTimer(1);
		if (AfxMessageBox(L"GAME OVER��COME ON �����¿�ʼ��", MB_YESNO) == 6)
		{
			m_pMe = new CMyPlane;
			m_pMe->load();
			SetTimer(1, 30, NULL);
		}
		else
			exit(1);
		
	}

	if (m_pMe != NULL && m_pMe->m_God)
	{
		wsprintf(lifeleft, L"�޵�ģʽ");
		pMemDC->SetTextColor(RGB(237, 28, 36));
		pMemDC->TextOutW( 250, 5, lifeleft, _tcslen(lifeleft));
		m_pMe->m_HP = 100;
	}
	//���� ��������ը���л����ӵ�
	for(int i=0;i<4;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() % 5 + 10;
	//BOSS

	//��������л�
	if(nCreator <= 0)
	{
		nCreator = rand() % 5 + ( 12 - m_pMe->m_Level);
		m_ObjList[enEnemy].AddTail(new CEnemy);
		if (m_pMe->m_Level % 2 == 0)
		{
			m_ObjList[enEnemy].AddTail(new CBoss);
		}
		
		if (m_pMe->m_Level >= 4 && flag == 0)
		{
			m_ObjList[enEnemy].AddTail(new CEnemyboss);
			flag++;
		}
	}
	nCreator--;
		
	if(m_pMe==NULL)
		return;

	//����ĸ���������ƶ�ս��
	for(int i=0;i<5;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey('W');
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey('S');
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey('D');
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey('A');
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);

		
		
		
	}
	//�޵�ģʽ
	if (GetKey('G'))
	{
		KillTimer(1);
		if (m_pMe->m_God == 0)
		{
			if (AfxMessageBox(L"�����޵�ģʽ��", MB_YESNO) == 6)
			{
				m_pMe->GOD();
			}
		}
		else
		{
			if (AfxMessageBox(L"�ر��޵�ģʽ��", MB_YESNO) == 6)
			{
				m_pMe->GOD();
			}
		}
		SetTimer(1, 30, NULL);

	}
	//��ͣ
	if (GetKey('P'))
	{
		KillTimer(1);
			if (AfxMessageBox(L"��ʼ��Ϸ��", MB_YESNO) == 6)
			{
				SetTimer(1, 30, NULL);
			}

	}

	
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if (m_pMe != NULL && m_pMe->Fired() && m_pMe->m_God)
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x - 30, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x - 10, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 50, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 70, pt.y + 10));
			m_ObjList[enBomb].AddTail(new MyHelper(pt.x + 190, pt.y + 10));
			m_ObjList[enBomb].AddTail(new MyHelper(pt.x - 190, pt.y + 10));
		}
		else if(m_pMe!=NULL && m_pMe->Fired())
		{
				CPoint pt = m_pMe->GetPoint();
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 50, pt.y + 10));
		}
	}


	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//�л��ӵ�ը��ս��

	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL ;) 
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect) )
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//ɾ��ս��
			
			if (!m_pMe->m_God)//GOD MOD
			{
				m_pMe->m_HP -= 20;
				if (m_pMe->m_HP <= 0)
				{
					m_pMe->m_Life -= 1;
					m_pMe->m_HP = 100;
					if (m_pMe->m_Life < 0)
					{
					m_pMe->save();
					delete m_pMe;
					m_pMe = NULL;
					}
				}
			}
			break;
		}
	}

	//ս������ը���л�
	POSITION mPos1=NULL,mPos2=NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;

			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);

				if (!m_pMe->m_God) {
					m_pMe->m_Score += 10;  //�ӷ�
					m_pMe->levelUp();   //�Ƿ�������
				}
				
				delete pEnemy;
				break;

			}
		}
	}
	///////////////////////////////
	/*
	
	*/
	POSITION m1Pos1 = NULL, m1Pos2 = NULL;
	for (m1Pos1 = m_ObjList[enBomb].GetHeadPosition(); (m1Pos2 = m1Pos1) != NULL;)
	{
		CBomb* p1Bomb = (CBomb*)m_ObjList[enBomb].GetNext(m1Pos1);
		CRect b1Rect = p1Bomb->GetRect();

		POSITION e1Pos1 = NULL, e1Pos2 = NULL;
		for (e1Pos1 = m_ObjList[enBigBoss].GetHeadPosition(); (e1Pos2 = e1Pos1) != NULL;)
		{
			CEnemyboss* p1Enemy = (CEnemyboss*)m_ObjList[enBigBoss].GetNext(e1Pos1);
			CRect m1Rect = p1Enemy->GetRect();
			CRect tmp1Rect;
			if (tmp1Rect.IntersectRect(&b1Rect, m1Rect))
			{
				//PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b1Rect.left, b1Rect.top)
				);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(m1Pos2);
				delete p1Bomb;

				//ɾ���л�BOSS
				p1Enemy->HPBOSS -= 2;
				if (p1Enemy->HPBOSS == 0)
				{
					m_ObjList[enBigBoss].RemoveAt(e1Pos2);
					delete p1Enemy;
					
				}
				
				break;
			}
		}
	}
//////////////////////////////////////////////////
	POSITION mmPos1 = NULL, mmPos2 = NULL;
	for (mmPos1 = m_ObjList[enEnemy].GetHeadPosition(); (mmPos2 = mmPos1) != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(mmPos1);
		CRect bmRect = pEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bmRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));

			//ɾ���л�
			m_ObjList[enEnemy].RemoveAt(mmPos2);
			delete pEnemy;
			
			if (!m_pMe->m_God)
			{
				m_pMe->m_HP -= 50;
				if (m_pMe->m_HP <= 0)
				{
					m_pMe->m_Life -= 1;
					m_pMe->m_HP += 100;
				}
			}
			//ɾ��ս��
			if (m_pMe->m_God == 0 &&  m_pMe->m_Life < 0)//������ֵ����������Ϊ0ʱ������Ϸ
			{
				m_pMe->save();
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}


	}
	
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	AI();
	
	CView::OnTimer(nIDEvent);
}


