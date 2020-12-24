#pragma once
#include "Base.h"

enum class TypeVolley : uint {
	SIMPLE,
	HUMBLE,
	BLINK,
	CRANK
};

class AVolley : public B {
protected:

	const TypeVolley m_TYPE;
	const float m_FORCE_POWER;
	float m_velocity;
	float m_angle;
	bool m_is_bang;

	virtual void ReColor(Shape& shape) {
		const int num_color = rand()%3;
		 if(num_color == 0)	{
			 shape.setFillColor(Color(255, rand()%255, rand()%255));
		 }
		 else if (num_color == 1) { 
			 shape.setFillColor(Color(rand()%255, 255, rand()%255));
		 }
		 else { 
			 shape.setFillColor(Color(rand()%255, rand()%255, 255));
		 }
	 }

public:
	 
	 AVolley(const TypeVolley type = TypeVolley::SIMPLE, 
	 const float angle = rand()%30-100, 
	 const float force_power = 13.0f, 
	 bool is_bang = false) 
	 : 
	 m_FORCE_POWER(force_power), 
	 m_TYPE(type), 
	 m_angle(angle), 
	 m_is_bang(is_bang) {
		 m_velocity = 0.f;
	 }
	 virtual void Update() = 0;
	 virtual void Draw() = 0;
	 virtual const bool IsEnd() = 0;
	 virtual const TypeVolley& GetType() {
		 return m_TYPE;
	 }
	 
	~AVolley() {

	}
};

class Volley : public AVolley
{
protected:

	Shape m_shape;

public:

	Volley(v2f position, 
	const TypeVolley type = TypeVolley::SIMPLE, 
	const float angle = rand()%30-100, 
	const float force_power = 13.0f, 
	bool is_bang = false) 
	: AVolley(type, angle, force_power, is_bang) {
		m_shape = CreateShape(position, v2f(3,21));
		ReColor(m_shape);
		m_velocity = m_FORCE_POWER * gravity;
	}

	virtual void Update() override {
		MoveToAngle(m_shape, m_angle, m_velocity);
		m_velocity *= gravity;
		if(m_is_bang) m_angle+=2;
	}

	const Shape& GetShape() {
		return m_shape;
	}

	virtual const bool IsEnd() override {
		return m_velocity < 0.35f;
	}

	virtual void Draw() override {
		wnd.draw(m_shape);
	}

	~Volley() {
	}
};

class VolleyHumble : public Volley {
	protected:

	void ReColor(Shape& shape) override {
		const int num_color = rand()%3;
		 if(num_color == 0)	{
			 shape.setFillColor(Color(255, rand()%255, rand()%255));
			 shape.setOutlineColor(Color(rand()%255, rand()%255, 255));
		 }
		 else if (num_color == 1) { 
			 shape.setFillColor(Color(rand()%255, 255, rand()%255));
			 shape.setOutlineColor(Color(rand()%255, 255, rand()%255));
		 }
		 else { 
			 shape.setFillColor(Color(rand()%255, rand()%255, 255));
			 shape.setOutlineColor(Color(255, rand()%255, rand()%255));
		 }
	}

	bool m_is_rotate_left;

	public:

	VolleyHumble(v2f position, const TypeVolley type = TypeVolley::HUMBLE, const float angle = rand()%30-100, const float force_power = 13.0f, bool is_bang = false) 
	: Volley(position ,type, angle, force_power, is_bang) {
		m_shape = CreateShape(position, v2f(6,6));
		m_shape.setOutlineThickness(1.f);
		ReColor(m_shape);
		m_shape.setOrigin(-m_shape.getSize());
		m_velocity = m_FORCE_POWER * gravity;
		m_is_rotate_left = static_cast<bool>(rand()%2);
	}

	void Update() override {
		MoveToAngle(m_shape, m_angle, m_velocity);
		if(m_is_rotate_left) m_shape.rotate(-24);
		else m_shape.rotate(24);
		m_velocity *= gravity;
		if(m_is_bang) m_angle++;
	}

	void Draw() override {
		wnd.draw(m_shape);
	}

	~VolleyHumble() {
	}
};

class VolleyBlink : public Volley {
	protected:

	float alpha_scale = 0;

	public:

	VolleyBlink(v2f position, const TypeVolley type = TypeVolley::BLINK, const float angle = rand()%30-100, const float force_power = 13.0f, bool is_bang = false) 
	: Volley(position, type, angle, force_power, is_bang) {
		m_shape = CreateShape(position, v2f(6,6));
		ReColor(m_shape);
		m_velocity = m_FORCE_POWER * gravity;
	}

	void Update() override {
		alpha_scale += 0.5;
		MoveToAngle(m_shape, m_angle, m_velocity);
		m_shape.setScale(1.f + cos(alpha_scale), 1.f + cos(alpha_scale));
		m_shape.rotate(16);
		m_velocity *= gravity;
		if(m_is_bang) m_angle++;
	}

	const Shape& GetShape() {
		return m_shape;
	}

	~VolleyBlink() {
	}
};

class VolleyCrank : public Volley {
	protected:

	float alpha_crank = 0;

	public:

	VolleyCrank(v2f position, const TypeVolley type = TypeVolley::CRANK, const float angle = rand()%30-100, const float force_power = 13.0f, bool is_bang = false) 
	: Volley(position, type, angle, force_power, is_bang) {
		m_shape = CreateShape(position, v2f(5,5));
		ReColor(m_shape);
		m_velocity = m_FORCE_POWER * gravity;
	}

	void Update() override {
		alpha_crank += 0.5;
		MoveToAngle(m_shape, m_angle, m_velocity);
		m_shape.setOrigin(m_shape.getSize().x * (cos(alpha_crank) * 4), m_shape.getOrigin().y);
		m_velocity *= gravity;
		if(m_is_bang) m_angle++;
	}

	void Draw() override {
		wnd.draw(m_shape);
	}

	~VolleyCrank() {
	}
};