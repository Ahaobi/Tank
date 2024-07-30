#pragma once

#include <tuple>
#include <vector>
#include "GameEntry.h"

using namespace std;

class CGame;

// 选择菜单的显示与响应
class CGameMenuPanel : public CGameEntryMoveable
{
public:
	CGameMenuPanel();
	~CGameMenuPanel();

	// 存放一个CGame类的指针
	void SetParent(CGame* g)
	{
		m_pParent = g;
	}

	CGame* m_pParent{ nullptr };		// 存放一个CGame类的指针

	virtual void Draw(Graphics& gh) const;	// 画自己

	RectF m_rect{ 0, 0, 800, 600 };			// 自己的范围

	void OnMouseMove(UINT nFlags, CPoint point);	// 处理鼠标移动事件

	void OnLButtonUp(UINT nFlags, CPoint point);	// 处理鼠标左键抬起事件

	Image* m_imgBackground;			// 背景图

	struct							// 菜单项
	{
		vector<tuple<Image*, RectF>> vImgInfoPtr;
		int index;
	} m_menuItems[2];
};