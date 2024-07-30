#pragma once

#include "pch.h"
#include <gdiplus.h>
#include <math.h>
#include <cmath>

class CGameEntry
{
public:
	CGameEntry() {}

	virtual ~CGameEntry() {}
public:
	virtual void Draw(Gdiplus::Graphics& gh) const = 0;		// 用于绘制自己的纯虚函数
};

// 可移动的物体
class CGameEntryMoveable : public CGameEntry
{
public:
	CGameEntryMoveable() {}
	virtual ~CGameEntryMoveable() {}

	CGameEntryMoveable(const CGameEntryMoveable& rhs)
	{
		if (this != &rhs)
		{

		}
	}
private:
	bool m_bActive{ false };			// 是否有效
	RectF m_rect{ 0, 0, 100, 100 };		// 占用的区域
};