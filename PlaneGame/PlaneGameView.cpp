// PlaneGameView.cpp : CPlaneGameView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	
	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	
	
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	




	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
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

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
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

	//产生主角(战机)
	m_pMe = new CMyPlane;
	m_pMe->load();
	//启动游戏
	system("del OldGame.exe");
	if (update.CheckNewVersion())
	{
		if (AfxMessageBox(L"游戏已有最新版本是否更新？", MB_YESNO) != 6)
		{
			

		}
		else
		{
			system("ren PlaneGame.exe OldGame.exe");
			update.GetNewVersion();
			
			if (AfxMessageBox(L"更新结束请重启游戏！", MB_YESNO))
			{
				
				exit(0);
			}
		}
	}

	
	


	if (AfxMessageBox(L"直接开始游戏，查看游戏说明请按·否·", MB_YESNO) != 6)
	{
		AfxMessageBox(L"WASD键控制战机方向，空格键射击,G键进入无敌模式,P键暂停。初始生命值为100，消灭一个敌机加10分。\n 游戏开始会自动读取存档，结束会自动存储");
	}
	SetTimer(1,30,NULL);

	return TRUE;
}
int CPlaneGameView::count = 0;
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//绘制天空
	pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	//贴图原理：位图先进入内存设备
	CBitmap bmpDraw;//定义一个位图对象
	CDC memDC;//定义内存设备
			  //1.导入位图


		bmpDraw.LoadBitmap(IDB_BITMAP1);

	//2.创建内存设备
	memDC.CreateCompatibleDC(pMemDC);//让memDC与pDC兼容

									 //3.把位图选入内存设备
	memDC.SelectObject(&bmpDraw);
	pMemDC->BitBlt(0, 0, 900, 2990, &memDC, 0, 0, SRCCOPY);
	//滚屏
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


	//绘制我方战机
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	   wsprintf(hpleft, L"生命值:%d ", m_pMe->m_HP);
	   pMemDC->SetTextColor(RGB(225, 0, 0));//设置字体颜色
	   pMemDC->TextOutW(GAME_WIDTH / 3 + 300, 5, hpleft, _tcslen(hpleft));

	   wsprintf(score, L"得分:%d / %d", m_pMe->m_Score, m_pMe->m_Level * 150);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(2, 2, score, _tcslen(score));

	   wsprintf(score, L"等级:%d", m_pMe->m_Level);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(2, 20, score, _tcslen(score));

	   wsprintf(lifeleft, L"生命数:%d", m_pMe->m_Life);
	   pMemDC->SetTextColor(RGB(237, 28, 36));
	   pMemDC->TextOutW(GAME_WIDTH / 3 + 300, 25, lifeleft, _tcslen(lifeleft));
	 
	}
	
	else
	{   //Game Over
		/*CString str=_T("游戏结束!,您的等级信息已保存！");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
		*/
		KillTimer(1);
		if (AfxMessageBox(L"GAME OVER！COME ON ！重新开始？", MB_YESNO) == 6)
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
		wsprintf(lifeleft, L"无敌模式");
		pMemDC->SetTextColor(RGB(237, 28, 36));
		pMemDC->TextOutW( 250, 5, lifeleft, _tcslen(lifeleft));
		m_pMe->m_HP = 100;
	}
	//绘制 导弹、爆炸、敌机、子弹
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

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() % 5 + 10;
	//BOSS

	//随机产生敌机
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

	//检测四个方向键，移动战机
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
	//无敌模式
	if (GetKey('G'))
	{
		KillTimer(1);
		if (m_pMe->m_God == 0)
		{
			if (AfxMessageBox(L"开启无敌模式？", MB_YESNO) == 6)
			{
				m_pMe->GOD();
			}
		}
		else
		{
			if (AfxMessageBox(L"关闭无敌模式？", MB_YESNO) == 6)
			{
				m_pMe->GOD();
			}
		}
		SetTimer(1, 30, NULL);

	}
	//暂停
	if (GetKey('P'))
	{
		KillTimer(1);
			if (AfxMessageBox(L"开始游戏？", MB_YESNO) == 6)
			{
				SetTimer(1, 30, NULL);
			}

	}

	
	if(GetKey(VK_SPACE)==1)//按下了空格键
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


	//敌机发射子弹

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//敌机子弹炸掉战机

	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL ;) 
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect) )
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//删除战机
			
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

	//战机导弹炸掉敌机
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);

				if (!m_pMe->m_God) {
					m_pMe->m_Score += 10;  //加分
					m_pMe->levelUp();   //是否升级？
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b1Rect.left, b1Rect.top)
				);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(m1Pos2);
				delete p1Bomb;

				//删除敌机BOSS
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
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));

			//删除敌机
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
			//删除战机
			if (m_pMe->m_God == 0 &&  m_pMe->m_Life < 0)//当生命值和生命数均为0时结束游戏
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
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	
	CView::OnTimer(nIDEvent);
}


