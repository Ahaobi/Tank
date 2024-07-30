#pragma once
// ������ ����ģ��Ĺ��ܴ�������
class CGame
{
public:
	CGame();
	~CGame();

	void SetHandle(HWND hWnd);		// ����������ھ��

	bool EnterFrame(DWORD dwTime);	// ������Ϸ֡

	void OnMouseMove(UINT nFlags, CPoint point);	// ��������ƶ��¼�

	void OnLButoonUp(UINT nFlags, CPoint point);	// �������̧���¼�

private:
	HWND m_hWnd;			// ����
	// ��Ϸ��ͼ����
	// ����滭��Ϸ�еĶ���
	void GameRunDraw();

	// ���fps
	void DrawFps(Graphics& gh);

	// ��¼��Ϸÿ�����֡
	int m_fps{ 0 };
};

