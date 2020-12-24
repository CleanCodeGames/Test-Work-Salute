#pragma once
#include "Resources.h"

class Base
{
public:

	static void SystemUpdate() {
		time = float(clock.getElapsedTime().asMicroseconds()) / 1000.f;
		clock.restart();
		cur_p = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd));
		cur_p_wnd = v2f(sf::Mouse::getPosition(wnd));
		cam_p = cam.getCenter();
	}

	static void CloseEvent() {
		if (event.type == sf::Event::Closed 
			//|| (event.type == sf::Event::KeyPressed && event.key.code == Key::Escape)
			) 
			wnd.close();
	}

	static const sf::FloatRect GetCamVisible() {
		return sf::FloatRect(
			cam.getCenter().x - (cam.getSize().x / 2),
			cam.getCenter().y - (cam.getSize().y / 2),
			cam.getSize().x,
			cam.getSize().y);
	}

	static const v2f GetNormalizedPosition(const v2f& pos, float dist, float angle) {
		const float& A = angle * RAD;
		return pos + v2f(cosf(A), sinf(A)) * dist;
	}

	static const v2f GetNormalizedPosition(Shape& shape, float dist, float angle) {
		const float& A = angle * RAD;
		return shape.getPosition() + v2f(cosf(A), sinf(A)) * dist;
	}

	static const bool IsContains(Shape& shape, const v2f& pos) {
		return shape.getGlobalBounds().contains(pos);
	}

	static const bool GetCollisionCircle(Shape& c1, Shape& c2) {
		const float r1 = c1.getSize().x / 2.f;
		const float r2 = c2.getSize().x / 2.f;
		const v2f& p1 = c1.getPosition();
		const v2f& p2 = c2.getPosition();
		return GetDistance(p1, p2) > float(r1 + r2) ? false : true;
	}

	static const bool GetCollisionRect(Shape& s1, Shape& s2) {
		return s1.getGlobalBounds().intersects(sf::FloatRect(
			s2.getPosition().x - (s2.getSize().x / 2.f), 
			s2.getPosition().y - (s2.getSize().y / 2.f), 
			s2.getSize().x, 
			s2.getSize().y));
	}

	static const float GetDistance(const v2f& p1, const v2f& p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}

	static const float GetDistance(Shape& s1, Shape& s2) {
		const v2f& p1 = s1.getPosition();
		const v2f& p2 = s2.getPosition();
		return GetDistance(p1, p2);
	}

	static const float GetDistance(Shape& s1, const  v2f& pos) {
		const v2f& p1 = s1.getPosition();
		return GetDistance(p1, pos);
	}

	static const Shape CreateShape(v2f pos, v2f siz, IMG& png) {
		Shape shp;
		shp.setOrigin(siz / 2.f);
		shp.setSize(siz);
		shp.setPosition(pos);
		shp.setTexture(&png);
		return shp;
	}

	static const Shape CreateShape(v2f pos, v2f siz) {
		Shape shp;
		shp.setOrigin(siz / 2.f);
		shp.setSize(siz);
		shp.setPosition(pos);
		return shp;
	}

	static const Shape CreateShape(v2f pos, v2f siz, Color color) {
		Shape shp;
		shp.setSize(siz);
		shp.setOrigin(siz / 2.f);
		shp.setFillColor(color);
		shp.setPosition(pos);
		return shp;
	}

	static const Shape CreateShape(v2f pos, v2f siz, float out_siz, Color color = Color::White, Color out_color = Color::White) {
		Shape shp;
		shp.setSize(siz);
		shp.setOrigin(siz / 2.f);
		shp.setFillColor(color);
		shp.setPosition(pos);
		shp.setOutlineThickness(out_siz);
		shp.setOutlineColor(out_color);
		return shp;
	}

	static const sf::Text CreateText(v2f pos, uint siz, sf::String str, sf::Font& font, Color col) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(siz);
		text.setFillColor(col);
		text.setString(str);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(pos.x, pos.y - siz / 3);
		return text;
	}
	
	static const float GetAngle(const v2f& p1, const v2f& p2) {
		return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
	}

	static const float GetAngle(Shape& shp, const v2f& p) {
		return atan2f(p.y - shp.getPosition().y, p.x - shp.getPosition().x) * DEG;
	}

	static const float GetAngle(Shape& shp1, Shape& shp2) {
		const v2f& p1 = shp1.getPosition();
		const v2f& p2 = shp2.getPosition();
		return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
	}

	static void MoveToAngle(Shape& shape, float angle, float speed) {
		const float& A = angle * RAD;
		shape.move(v2f(cos(A), sin(A)) * (speed));
	}

	static void CenteringText(sf::Text& text) {
		text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 1.5f);
	}

	static bool IsKeyPressed(const sf::Keyboard::Key& code) {
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == code) return true;
		return false;
	}
	
	static bool IsKeyReleased(const sf::Keyboard::Key& code) {
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == code) return true;
		return false;
	}

	static bool IsMousePressed(const sf::Mouse::Button& code) {
		if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == code) return true;
		return false;
	}

	static bool IsMouseReleased(const sf::Mouse::Button& code) {
		if (event.type == sf::Event::MouseButtonReleased)
			if (event.key.code == code) return true;
		return false;
	}
	
	Base(string init) {
		if (init == "init")
		{
			scr_h = sf::VideoMode::getDesktopMode().height;
			scr_w = sf::VideoMode::getDesktopMode().width;
			wnd.create(sf::VideoMode(scr_w, scr_h), "Test Work Salute", sf::Style::Close, sf::ContextSettings(0, 0, 8));
			cam.reset(sf::FloatRect(0, 0, scr_w, scr_h));
			cam.setCenter(0, 0);
			cam_p = cam.getCenter();
			cur_p = v2f(0, 0);
			cur_p_wnd = v2f(0, 0);
			wnd.setView(cam);
			gravity = 0.98;
			wnd.setMouseCursorVisible(true);
			wnd.setVerticalSyncEnabled(true);
			srand(::time(0));
			clock.restart();
		}
	}

	Base(void) {
	}

	~Base() {}

	static sf::RenderWindow wnd;
	static float gravity;		 
	static Resources resources;	 
	static sf::Event event;
	static sf::View cam;
	static int scr_w;
	static int scr_h;
	static v2f cam_p;
	static v2f cur_p;
	static v2f cur_p_wnd;
	static float time;

private: 
	static sf::Clock clock;
};

sf::RenderWindow	B::wnd;	
float				B::gravity;	
Resources			B::resources;
sf::Event			B::event;
sf::View			B::cam;	
int					B::scr_w;
int					B::scr_h;
v2f					B::cam_p;
v2f					B::cur_p;
v2f					B::cur_p_wnd;
float				B::time;
sf::Clock			B::clock;