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
	virtual void Draw(Gdiplus::Graphics& gh) const = 0;		// ���ڻ����Լ��Ĵ��麯��
};

// ���ƶ�������
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
	bool m_bActive{ false };			// �Ƿ���Ч
	RectF m_rect{ 0, 0, 100, 100 };		// ռ�õ�����
};