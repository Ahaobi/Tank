#include "pch.h"
#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::SetHandle(HWND hWnd)		// ����������ھ��
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)	// ������Ϸ֡
{
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)	// ��������ƶ��¼�
{
}

void CGame::OnLButoonUp(UINT nFlags, CPoint point)		// �������̧���¼�
{
}

// ��Ϸ��ͼ
//void CGame::GameRunDraw()
//{
//	HDC hdc = ::GetDC(m_hWnd);		// �Ӵ��ھ��m_hWnd��ȡ�豸�����ģ�DC�����ڻ�ͼ����
//									// ��ȡ�Ĵ����豸������
//	CRect rc;			// �ͻ�����С
//	GetClientRect(m_hWnd, &rc);
//
//	CDC* dc = CClientDC::FromHandle(hdc);	// ��ԭʼ�� HDC ����һ�� MFC �� CDC ����
//											// ����ʹ��MFC�Ļ�ͼ���ܡ�
//
//	CDC m_dcMemory;				// ˫�����ͼ��
//	CBitmap bmp;
//	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
//	m_dcMemory.CreateCompatibleDC(dc);
//	CBitmap* po1dBitmap = m_dcMemory.SelectObject(&bmp);
//
//	Graphics gh(m_dcMemory.GetSafeHdc());		// �������
//	// m_dcMemory.GetSafeHdc() ��ȡ�����ڴ��豸������
//	gh.Clear(Color::White);						// �������
//	gh.ResetClip();
//
//	DrawFps(gh);								// �����ڴ�
//
//	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),	// ������hdc������豸�������Ƶ���Ļ
//		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);	// SRCCOPY:ֱ�ӿ���
//
//	dc->DeleteDC();								// �ͷ�
//	return;
//}

// ��fps
//void CGame::DrawFps(Graphics& gh)
//{
//	static int fps = 0;			// ���徲̬������ÿ�ν��뺯��ʱ�����ϴε�ֵ
//	m_fps++;					// ��¼�Ѿ����˶���֡
//	static DWORD dwLast = GetTickCount();		// ��¼�ϴ����fps��ʱ��
//	if (GetTickCount() - dwLast >= 1000)	// �������1�룬���fps
//	{
//		fps = m_fps;
//		m_fps = 0;
//		dwLast = GetTickCount();			// ��¼���������ʱ��
//	}
//
//	// ���fps
//	CString s;
//	s.Format(_T("FPS:%d"), fps);			// ��fps��ʽ�����ַ���
//	SolidBrush brush(Color(0x00, 0x00, 0xFF));	// ������ɫ�Ļ�ˢ
//	Gdiplus::Font font(_T("����"), 10.0);	// �����������
//	CRect rc;
//	::GetClientRect(m_hWnd, &rc);			// ��ȡ����Ĵ��ڴ�С��������λ���ֵ����λ��
//	PointF origin(static_cast<float>(rc.right - 50),			// �����Ͻ���ʾ
//		static_cast<float>(rc.top + 2));
//	gh.DrawString(s.GetString(), -1, &font, origin, &brush);	//�������
//
//}