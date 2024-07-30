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

// ���ƶ������� �ٶ���ط�����λ����ط������Ƕȷ�����ط���
class CGameEntryMoveable : public CGameEntry
{
public:
	CGameEntryMoveable() {}
	virtual ~CGameEntryMoveable() {}

	// �������캯��
	CGameEntryMoveable(const CGameEntryMoveable& rhs)
	{
		if (this != &rhs)
		{
			this->m_bActive = rhs.m_bActive;		// �Ƿ���Ч
			this->m_rect = rhs.m_rect;				// ռ�õ�����
			this->m_fSpeed = rhs.m_fSpeed;			// �ƶ��ٶ�
			this->m_direction = rhs.m_direction;	// ��ǰ�ĽǶ�
			this->m_directionTurn = rhs.m_directionTurn;	// ÿ����ת�ĽǶ�
		}
	}

	// ���ظ�ֵ�����
	CGameEntryMoveable& operator=(const CGameEntryMoveable& rhs)
	{
		if (this != &rhs) {
			this->m_bActive = rhs.m_bActive;		// �Ƿ���Ч
			this->m_rect = rhs.m_rect;				// ռ�õ�����
			this->m_fSpeed = rhs.m_fSpeed;			// �ƶ��ٶ�
			this->m_direction = rhs.m_direction;	// ��ǰ�ĽǶ�
			this->m_directionTurn = rhs.m_directionTurn;	// ÿ����ת�ĽǶ�
		}
		return *this;
	}
public:
	virtual void Draw(Gdiplus::Graphics& gh) const = 0;
	/********************���ƶ����干ͬ����********************/
	// ��ת
	virtual void RotateRight()
	{
		m_direction += m_directionTurn;		// ��ǰ�Ƕ�����
		if (m_direction >= 360)
		{
			m_direction -= 360;			// ת��һ�ܺ󣬼�ȥ360�ȣ�����С�Ƕ�
		}
	}

	// ��ת
	virtual void RotateLeft()
	{
		m_direction -= m_directionTurn;		// ��ǰ�Ƕȼ���
		if (m_direction < 0)		// ʹ�䱣���ڴ���0�ĽǶ�
		{
			m_direction = static_cast<float>(360 - m_directionTurn);
		}
	}

	// ǰ��
	virtual void Forward()
	{
		// ���ݵ�ǰ�Ƕȣ���x��y�����Ϸֱ��������
		m_rect.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}

	// ����
	virtual void Backward()
	{
		// ���ݵ�ǰ�Ƕȣ���x��y�����Ϸֱ��������
		m_rect.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		m_rect.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}

	// ��ȡˮƽ������ٶȷ���
	virtual float GetXSpeed() const
	{
		return static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
	}
	// ��ȡ��ֱ������ٶȷ���
	virtual float GetYSpeed() const
	{
		return -static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
	}
	// ��һ��ǰ����λ��
	virtual RectF ForwardNextRect() const
	{
		RectF rc = m_rect;
		rc.X += static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		rc.Y -= static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
		return rc;
	}
	// ��һ�����˵�λ��
	virtual RectF BackwardNextRect() const
	{
		RectF rc = m_rect;
		rc.X -= static_cast<Gdiplus::REAL>((m_fSpeed)*sin(GetDirectionArc()));
		rc.Y += static_cast<Gdiplus::REAL>((m_fSpeed)*cos(GetDirectionArc()));
		return rc;
	}
	// ��ȡͷ��λ�ã�ͼƬΪ���Σ�ͷ��λ�þ��ǽǶ�Ϊ0ʱ
	// �������ĵ�Ϊ�뾶���Խ���/2���������Լ���X���ϵ�λ��
	virtual PointF GetHeadPos() const
	{
		PointF ptCenter = GetCenterPoint();
		PointF ptHead = ptCenter;
		float fRadius = std::sqrt(std::pow(m_rect.Width / 2, 2)		// ����뾶
						+ std::pow(m_rect.Height / 2, 2));
		ptHead.X += fRadius * sin(GetDirectionArc());				// ����ͷ������X
		ptHead.Y -= fRadius * cos(GetDirectionArc());				// ����ͷ������Y
		return ptHead;
	}

	// ��ȡ���ĵ�
	virtual PointF GetCenterPoint() const
	{
		PointF center = PointF(m_rect.X + m_rect.Width / 2, 
							   m_rect.Y + m_rect.Height / 2);
		return center;
	}
	// �������ĵ�
	virtual void SetCenterPoint(const PointF& ptCenter)
	{
		PointF cen = GetCenterPoint();
		cen.X = ptCenter.X - cen.X;
		cen.Y = ptCenter.Y - cen.Y;
		m_rect.Offset(cen);
	}
	// ���Դ�ȡ��
#ifndef PI
#define PI (3.1415926f)
#endif // !PI
	// 1�� = ��/180 ����
	// 1���� = 180 / �� ��
	// degrees = radians * 180 / ��  ����ת��Ϊ�Ƕ�
	// ���ýǶȣ���λΪ��a*PI�� �ɻ���תΪ�Ƕ�
	virtual void SetDirectionArc(float dir)
	{
		m_direction = dir * 180.0f / PI;	// �Ƕ�
	}
	// ���ýǶȣ���λ�ǡ��Ƕȡ���
	virtual void SetDirection(float dir)
	{
		m_direction = dir;
	}
	// ��ȡ��ǰ�Ļ���
	virtual float GetDirectionArc() const
	{
		return PI * m_direction / 180.0f;
	}
	// ��ȡ��ǰ�Ƕȣ���λ�ǡ��ȡ���
	virtual float GetDirection() const
	{
		return m_direction;
	}
	// ����ÿ����ת�ĽǶ�
	virtual void SetDirectionTurnArc(float dir)
	{
		m_directionTurn = PI * dir / 180.0f;
	}
	// ����ÿ����ת�ĽǶ�
	virtual void SetDirectionTurn(float dir)
	{
		m_directionTurn = dir;
	}
	// ��ȡ��ǰ�ĽǶȣ���λ�ǡ�PI����
	virtual float GetDirectionTurnArc() const
	{
		return PI * m_directionTurn / 180.0f;
	}
	// ��ȡ��ǰ�Ļ��ȣ���λ�ǡ��ȡ���
	virtual float GetDirectionTurn() const
	{
		return m_direction;
	}
	// �Ƿ�����Ч��
	virtual bool  IsActive() const
	{
		return m_bActive;
	}
	// ������Ч��־λ
	virtual void SetActive(bool bActive)
	{
		m_bActive = bActive;
	}
	// ռ�÷�Χ
	virtual RectF GetRect() const
	{
		return m_rect;
	}
	// �����ƶ��ٶ�
	virtual void SetSpeed(float speed)
	{
		m_fSpeed = speed;
	}
	// ��ȡ�ƶ��ٶ�
	virtual float GetSpeed() const
	{
		return m_fSpeed;
	}
private:
	bool m_bActive{ false };			// �Ƿ���Ч
	RectF m_rect{ 0, 0, 100, 100 };		// ռ�õ����� X, Y, Width, Height X, Y�������Ͻ�����
	float m_fSpeed{ 10 };				// �ƶ��ٶ�
	float m_direction{ 0 };				// ��ǰ�ĽǶ�
	float m_directionTurn{ 5 };			// ÿ����ת�ĽǶ�
};