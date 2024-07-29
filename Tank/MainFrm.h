
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#include"Game.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
protected: // 仅从序列化创建
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:

// 实现
public:
	virtual ~CMainFrame();

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	int m_iWidth{ 800 };
	int m_iHeight{ 600 };
	enum ETimerId
	{
		ETimerIdGameLoop = 1
	};	// 定时器ID 定时器ID和OnTimer()方法提供给定时器使用
		// 一个ID代表一个定时器，程序中存在多个定时器
	CGame m_game;		// 游戏对象 游戏中的操作都会用到 m_game
public:
	afx_msg void OnTimer(UINT_PTR nTDEvent);
};


