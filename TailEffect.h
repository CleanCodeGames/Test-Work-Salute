#pragma once
#include "Base.h"

class TailEffect : public B
{
private:

	float m_timer_of_life;
	float TIMER_OF_LIFE_MAX;
	Shape m_shape;
	float m_angle;
	
public:

	TailEffect(const float timer, const Shape& shape) 
		: TIMER_OF_LIFE_MAX(timer), 
		m_timer_of_life(timer) 
	{
		m_angle = rand() % 360;
		m_shape = shape;
	}
	
	void Update() {
		Color c = m_shape.getFillColor();
		Color co = m_shape.getOutlineColor();
		c.a = 255.f * (m_timer_of_life / TIMER_OF_LIFE_MAX);
		co.a = 255.f * (m_timer_of_life / TIMER_OF_LIFE_MAX);
		m_shape.setFillColor(c);
		m_shape.setOutlineColor(co);
		m_timer_of_life -= time;
		MoveToAngle(m_shape, m_angle, 0.25f);
	}

	void Draw() {
		wnd.draw(m_shape);
	}

	bool IsEnd() {
		return m_timer_of_life <= 0;
	}

	~TailEffect() {
	}
};