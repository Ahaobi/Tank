
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Tank.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GAME_WIN_W (800)		// 全局变量：窗口宽
#define GAME_WIN_H (600)		// 全局变量：窗口高


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | \
				  WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	// 创建窗口
	Create(NULL, _T("明日科技.坦克大战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	// 设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);			// 获取客户区大小

		RECT rcFrame = { 0, 0,				// 计算边框大小并设置
						m_iWidth + m_iWidth - rcCli.right,
						m_iHeight + m_iHeight - rcCli.bottom
		};
		MoveWindow(&rcFrame, TRUE);			// 调用WindowsAPI设置窗口大小和位置
	}
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(ETimerIdGameLoop, 0, NULL);		// 启动定时器每次都会进入游戏帧
	m_game.SetHandle(GetSafeHwnd());		// 设置游戏主窗口句柄
	return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ETimerIdGameLoop: {				// 游戏循环ID
		static DWORD dwLastUpdate = GetTickCount();		// 记录本次时刻
		if (GetTickCount() - dwLastUpdate >= 20) {
			m_game.EnterFrame(GetTickCount());		// 进入游戏帧处理
			dwLastUpdate = GetTickCount();				// 记录时间间隔
		}
	}
	default:
		break;
	}

	CFrameWnd::OnTimer(nIDEvent);
}

// CMainFrame 消息处理程序

