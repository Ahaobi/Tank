#pragma once
// 主体类 将各模块的功能串联起来
class CGame
{
public:
	CGame();
	~CGame();

	void SetHandle(HWND hWnd);		// 设置输出窗口句柄

	bool EnterFrame(DWORD dwTime);	// 进入游戏帧

	void OnMouseMove(UINT nFlags, CPoint point);	// 处理鼠标移动事件

	void OnLButoonUp(UINT nFlags, CPoint point);	// 处理左键抬起事件

private:
	HWND m_hWnd;			// 窗口
	// 游戏绘图处理
	// 负责绘画游戏中的对象
	void GameRunDraw();

	// 输出fps
	void DrawFps(Graphics& gh);

	// 记录游戏每秒多少帧
	int m_fps{ 0 };
};

