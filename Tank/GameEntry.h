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

// 可移动的物体 速度相关方法、位置相关方法、角度方向相关方法
class CGameEntryMoveable : public CGameEntry
{
public:
	CGameEntryMoveable() {}
	virtual ~CGameEntryMoveable() {}

	// 拷贝构造函数
	CGameEntryMoveable(const CGameEntryMoveable& rhs)
	{
		if (this != &rhs)
		{
			this->m_bActive = rhs.m_bActive;		// 是否有效
			this->m_rect = rhs.m_rect;				// 占用的区域
			this->m_fSpeed = rhs.m_fSpeed;			// 移动速度
			this->m_direction = rhs.m_direction;	// 当前的角度
			this->m_directionTurn = rhs.m_directionTurn;	// 每次旋转的角度
		}
	}

	// 重载赋值运算符
	CGameEntryMoveable& operator=(const CGameEntryMoveable& rhs)
	{
		if (this != &rhs) {
			this->m_bActive = rhs.m_bActive;		// 是否有效
			this->m_rect = rhs.m_rect;				// 占用的区域
			this->m_fSpeed = rhs.m_fSpeed;			// 移动速度
			this->m_direction = rhs.m_direction;	// 当前的角度
			this->m_directionTurn = rhs.m_directionTurn;	// 每次旋转的角度
		}
		return *this;
	}
public:
	virtual void Draw(Gdiplus::Graphics& gh) const = 0;
	/********************可移动物体共同属性********************/
	// 右转
	virtual void RotateRight()
	{
		m_direction += m_directionTurn;		// 当前角度增加
		if (m_direction >= 360)
		{
			m_direction -= 360;			// 转满一周后，减去360度，保持小角度
		}
	}

	// 左转
	virtual void RotateLeft()
	{
		m_direction -= m_directionTurn;		// 当前角度减少
		if (m_direction < 0)		// 使其保持在大于0的角度
		{
			m_direction = static_cast<float>(360 - m_directionTurn);
		}
	}

	// 前移
	virtual void Forward()
	{
		// 根据当前角度，在x，y方向上分别进行增减
		m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}

	// 后移
	virtual void Backward()
	{
		// 根据当前角度，在x，y方向上分别进行增减
		m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}

	// 获取水平方向的速度分量
	virtual float GetXSpeed() const
	{
		return static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	}
	// 获取竖直方向的速度分量
	virtual float GetYSpeed() const
	{
		return -static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}
	// 下一步前进的位置
	virtual RectF ForwardNextRect() const
	{
		RectF rc = m_rect;
		rc.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
		return rc;
	}
	// 下一步后退的位置
	virtual RectF BackwardNextRect() const
	{
		RectF rc = m_rect;
		rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
		return rc;
	}
	// 获取头部位置：图片为矩形：头部位置就是角度为0时
	// 距离中心点为半径（对角线/2），重置自己在X轴上的位置
	virtual PointF GetHeadPos() const
	{
		PointF ptCenter = GetCenterPoint();
		PointF ptHead = ptCenter;
		float fRadius = std::sqrt(std::pow(m_rect.Width / 2, 2)		// 计算半径
						+ std::pow(m_rect.Height / 2, 2));
		ptHead.X += fRadius * sin(GetDirectionArc());				// 计算头部坐标X
		ptHead.Y -= fRadius * cos(GetDirectionArc());				// 计算头部坐标Y
		return ptHead;
	}

	// 获取中心点
	virtual PointF GetCenterPoint() const
	{
		PointF center = PointF(m_rect.X + m_rect.Width / 2, 
							   m_rect.Y + m_rect.Height / 2);
		return center;
	}
	// 设置中心点
	virtual void SetCenterPoint(const PointF& ptCenter)
	{
		PointF cen = GetCenterPoint();
		cen.X = ptCenter.X - cen.X;
		cen.Y = ptCenter.Y - cen.Y;
		m_rect.Offset(cen);
	}
	// 属性存取器
#ifndef PI
#define PI (3.1415926f)
#endif // !PI
	// 1度 = π/180 弧度
	// 1弧度 = 180 / π 度
	// degrees = radians * 180 / π  弧度转换为角度
	// 设置角度：单位为“a*PI” 由弧度转为角度
	virtual void SetDirectionArc(float dir)
	{
		m_direction = dir * 180.0f / PI;	// 角度
	}
	// 设置角度（单位是“角度”）
	virtual void SetDirection(float dir)
	{
		m_direction = dir;
	}
	// 获取当前的弧度
	virtual float GetDirectionArc() const
	{
		return PI * m_direction / 180.0f;
	}
	// 获取当前角度（单位是“度”）
	virtual float GetDirection() const
	{
		return m_direction;
	}
	// 设置每次旋转的角度
	virtual void SetDirectionTurnArc(float dir)
	{
		m_directionTurn = PI * dir / 180.0f;
	}
	// 设置每次旋转的角度
	virtual void SetDirectionTurn(float dir)
	{
		m_directionTurn = dir;
	}
	// 获取当前的角度（单位是“PI”）
	virtual float GetDirectionTurnArc() const
	{
		return PI * m_directionTurn / 180.0f;
	}
	// 获取当前的弧度（单位是“度”）
	virtual float GetDirectionTurn() const
	{
		return m_direction;
	}
	// 是否是有效的
	virtual bool  IsActive() const
	{
		return m_bActive;
	}
	// 设置有效标志位
	virtual void SetActive(bool bActive)
	{
		m_bActive = bActive;
	}
	// 占用范围
	virtual RectF GetRect() const
	{
		return m_rect;
	}
	// 设置移动速度
	virtual void SetSpeed(float speed)
	{
		m_fSpeed = speed;
	}
	// 获取移动速度
	virtual float GetSpeed() const
	{
		return m_fSpeed;
	}
private:
	bool m_bActive{ false };			// 是否有效
	RectF m_rect{ 0, 0, 100, 100 };		// 占用的区域 X, Y, Width, Height X, Y决定左上角坐标
	float m_fSpeed{ 10 };				// 移动速度
	float m_direction{ 0 };				// 当前的角度
	float m_directionTurn{ 5 };			// 每次旋转的角度
};