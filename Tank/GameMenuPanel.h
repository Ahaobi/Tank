#pragma once

#include <tuple>
#include <vector>
#include "GameEntry.h"

using namespace std;

class CGame;

// ѡ��˵�����ʾ����Ӧ
class CGameMenuPanel : public CGameEntryMoveable
{
public:
	CGameMenuPanel();
	~CGameMenuPanel();

	// ���һ��CGame���ָ��
	void SetParent(CGame* g)
	{
		m_pParent = g;
	}

	CGame* m_pParent{ nullptr };		// ���һ��CGame���ָ��

	virtual void Draw(Graphics& gh) const;	// ���Լ�

	RectF m_rect{ 0, 0, 800, 600 };			// �Լ��ķ�Χ

	void OnMouseMove(UINT nFlags, CPoint point);	// ��������ƶ��¼�

	void OnLButtonUp(UINT nFlags, CPoint point);	// ����������̧���¼�

	Image* m_imgBackground;			// ����ͼ

	struct							// �˵���
	{
		vector<tuple<Image*, RectF>> vImgInfoPtr;
		int index;
	} m_menuItems[2];
};