#pragma once
#include "Base.h"
class AbstractButton : public B
{
protected:

	string m_action_id;
	Shape m_shape;

public:

	AbstractButton(const Shape& shape, const string action_id) 
		: m_action_id(action_id), m_shape(shape) {
	}
	virtual Shape& GetShape()			= 0;
	virtual const string& GetActionId()	= 0;
	virtual void Update()				= 0;
	virtual void Draw()					= 0;
	virtual bool IsAction()				= 0;
	virtual ~AbstractButton()			= default;
};

class ButtonClickActive : public AbstractButton
{
protected: bool m_isClick = false;

public:

	ButtonClickActive(const Shape& shape, const string action_id)
		: AbstractButton(shape, action_id) {
	}

	virtual const string& GetActionId() override {
		return m_action_id;
	}

	virtual void Update() override {
		// Do Nothing...
	}

	virtual void Draw() override {
		B::wnd.draw(m_shape);
	}

	virtual Shape& GetShape() override { 
		return m_shape; 
	}

	virtual bool IsAction() override {

		const bool is_contains = IsContains(m_shape, cur_p_wnd);
		
		if (IsMousePressed(sf::Mouse::Left)) {
			if (is_contains) {
				m_isClick = true;
				m_shape.setScale(.98, .98);
			}
			else {
				m_isClick = false;
				m_shape.setScale(1, 1);
			}
		}
		else if (IsMouseReleased(sf::Mouse::Left) && m_isClick) {
			m_isClick = false;
			m_shape.setScale(1, 1);
			return is_contains;
		}
		return false;
	}

	virtual ~ButtonClickActive() override {
	}
};

class ButtonClickActiveWithText : public ButtonClickActive
{
private: sf::Text text;

public:

	ButtonClickActiveWithText(const Shape& shape, const string action_id)
		: ButtonClickActive(shape, action_id) {
		text = CreateText(m_shape.getPosition(), m_shape.getSize().y, sf::String(m_action_id), resources.font.common, Color(40, 40, 40));
	}
	virtual void Draw() override {
		ButtonClickActive::Draw();
		wnd.draw(text);
	}
	virtual void Update() override {
		
		ButtonClickActive::Update();
	}
	virtual bool IsAction() override {
		if (m_shape.getGlobalBounds().contains(B::cur_p_wnd)) {
			text.setFillColor(Color::Yellow);
		}
		else {
			text.setFillColor(Color(40, 40, 40));
		}
		return ButtonClickActive::IsAction();
	}
	virtual ~ButtonClickActiveWithText() override {
	}

};

class ButtonCheckBox : public AbstractButton
{
private: bool m_isChecked;

public:

	ButtonCheckBox(const Shape& shape, const string action_id, const bool isChecked = false)
		: AbstractButton(shape, action_id), m_isChecked(isChecked) {
		m_shape.setOutlineThickness(2);
		m_shape.setOutlineColor(Color::White);
		if (m_isChecked) m_shape.setFillColor(Color(120, 255, 80));
		else m_shape.setFillColor(Color(80, 80, 80));
	}
	virtual Shape& GetShape() override {
		return m_shape;
	}
	virtual const string& GetActionId() override {
		return m_action_id;
	}
	virtual void Update() override {
		// Do nothing...
	}
	virtual void Draw() override {
		B::wnd.draw(m_shape);
	}
	virtual bool IsAction() override {
		if (IsMousePressed(sf::Mouse::Left) && m_shape.getGlobalBounds().contains(B::cur_p_wnd)) {
			m_isChecked = !m_isChecked;
			if (m_isChecked) m_shape.setFillColor(Color(120, 255, 80));
			else m_shape.setFillColor(Color(80, 80, 80));
		}
		return m_isChecked;
	}
	virtual ~ButtonCheckBox() override {

	}
};