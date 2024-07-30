#include "pch.h"
#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::SetHandle(HWND hWnd)		// 设置输出窗口句柄
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)	// 进入游戏帧
{
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)	// 处理鼠标移动事件
{
}

void CGame::OnLButoonUp(UINT nFlags, CPoint point)		// 处理左键抬起事件
{
}

// 游戏绘图
//void CGame::GameRunDraw()
//{
//	HDC hdc = ::GetDC(m_hWnd);		// 从窗口句柄m_hWnd获取设备上下文（DC）用于绘图操作
//									// 获取的窗口设备上下文
//	CRect rc;			// 客户区大小
//	GetClientRect(m_hWnd, &rc);
//
//	CDC* dc = CClientDC::FromHandle(hdc);	// 从原始的 HDC 创建一个 MFC 的 CDC 对象
//											// 方便使用MFC的绘图功能。
//
//	CDC m_dcMemory;				// 双缓冲绘图用
//	CBitmap bmp;
//	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
//	m_dcMemory.CreateCompatibleDC(dc);
//	CBitmap* po1dBitmap = m_dcMemory.SelectObject(&bmp);
//
//	Graphics gh(m_dcMemory.GetSafeHdc());		// 构造对象
//	// m_dcMemory.GetSafeHdc() 获取的是内存设备上下文
//	gh.Clear(Color::White);						// 清除背景
//	gh.ResetClip();
//
//	DrawFps(gh);								// 画入内存
//
//	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),	// 拷贝到hdc代表的设备，即复制到屏幕
//		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);	// SRCCOPY:直接拷贝
//
//	dc->DeleteDC();								// 释放
//	return;
//}

// 画fps
//void CGame::DrawFps(Graphics& gh)
//{
//	static int fps = 0;			// 定义静态变量，每次进入函数时保存上次的值
//	m_fps++;					// 记录已经画了多少帧
//	static DWORD dwLast = GetTickCount();		// 记录上次输出fps的时间
//	if (GetTickCount() - dwLast >= 1000)	// 如果超过1秒，输出fps
//	{
//		fps = m_fps;
//		m_fps = 0;
//		dwLast = GetTickCount();			// 记录本次输出的时间
//	}
//
//	// 输出fps
//	CString s;
//	s.Format(_T("FPS:%d"), fps);			// 将fps格式化到字符串
//	SolidBrush brush(Color(0x00, 0x00, 0xFF));	// 创建蓝色的画刷
//	Gdiplus::Font font(_T("宋体"), 10.0);	// 创建输出字体
//	CRect rc;
//	::GetClientRect(m_hWnd, &rc);			// 获取输出的窗口大小，用来定位文字的输出位置
//	PointF origin(static_cast<float>(rc.right - 50),			// 在右上角显示
//		static_cast<float>(rc.top + 2));
//	gh.DrawString(s.GetString(), -1, &font, origin, &brush);	//输出文字
//
//}