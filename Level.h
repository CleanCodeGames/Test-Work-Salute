#pragma once
#include "Button.h"
#include "Volley.h"
#include "TailEffect.h"

class Level : public B
{
private:

	Shape m_shape_back_ground;
	list<shared_ptr<Volley>> vec_volley;
	list<shared_ptr<Volley>> vec_bang;
	list<shared_ptr<TailEffect>> vec_tail;
	float m_timer_create_effect = 0;
	
protected:
//...
public:

	Level() {
		resources.texture.LoadLevel_0();
		m_shape_back_ground = CreateShape(v2f(), v2f(scr_w, scr_h), resources.texture.background);
	}

	const int GetVolleyCount() {
		return vec_volley.size();
	}

	const int GetBangCount() {
		return vec_bang.size();
	}

	const int GetTailCount() {
		return vec_tail.size();
	}

	bool IsTailEffectCreate() {
		return m_timer_create_effect > 25.f;
	}

	void Update() {
		m_timer_create_effect += time;

		for (auto it = vec_volley.begin(); it != vec_volley.end();) {
			auto& volley = *(*it);
			volley.Update();

			if (IsTailEffectCreate()) {
				vec_tail.push_back(make_shared<TailEffect>(500.f, volley.GetShape()));
			}

			if(volley.IsEnd()) {
				int nums_volley = rand()%10+25;
				for(int i = 0; i < nums_volley; i++)
				switch (volley.GetType()) {
				case TypeVolley::SIMPLE:
					vec_bang.push_back(make_shared<Volley>(
						Volley(volley.GetShape().getPosition(), TypeVolley::SIMPLE, rand()%360, rand()%4+5, true))); break;
				case TypeVolley::HUMBLE:
					vec_bang.push_back(make_shared<VolleyHumble>(
						VolleyHumble(volley.GetShape().getPosition(), TypeVolley::HUMBLE, rand()%360, rand()%4+5, true))); break;
				case TypeVolley::BLINK:
					vec_bang.push_back(make_shared<VolleyBlink>(
						VolleyBlink(volley.GetShape().getPosition(), TypeVolley::BLINK, rand()%360, rand()%4+5, true))); break;
				case TypeVolley::CRANK:
					vec_bang.push_back(make_shared<VolleyCrank>(
						VolleyCrank(volley.GetShape().getPosition(), TypeVolley::CRANK, rand()%360, rand()%4+5, true))); break;
						default: break;
				}
				
				it = vec_volley.erase(it);
			}
			else ++it;
		}

		for(auto it = vec_bang.begin(); it != vec_bang.end();) {
			auto& bang = *(*it);
			bang.Update();
			if(IsTailEffectCreate()) {
				vec_tail.push_back(make_shared<TailEffect>(1200.f, bang.GetShape()));
			}
			if(bang.IsEnd()) it = vec_bang.erase(it);
			else ++it;
		}

		for (auto it = vec_tail.begin(); it != vec_tail.end();) 
		{
			auto& tail = *(*it);
			tail.Update();
			if (tail.IsEnd()) it = vec_tail.erase(it);
			else ++it;
		}

		if (IsTailEffectCreate()) { 
			m_timer_create_effect = 0;
		}
	}

	void Draw() {
		wnd.draw(m_shape_back_ground);
		for (auto& volley : vec_volley)
			volley->Draw();

		for (auto& tail : vec_tail)
			tail->Draw();

		for(auto& bang : vec_bang)
			bang->Draw();
	}

	virtual void Action() {
		if (IsMousePressed(sf::Mouse::Left)) {
			const TypeVolley type = static_cast<TypeVolley>(uint(rand()%4));
			switch (type)
			{
				case TypeVolley::SIMPLE: vec_volley.push_back(make_shared<Volley>(Volley(cur_p))); break;
				case TypeVolley::HUMBLE: vec_volley.push_back(make_shared<VolleyHumble>(VolleyHumble(cur_p))); break;
				case TypeVolley::BLINK:  vec_volley.push_back(make_shared<VolleyBlink>(VolleyBlink(cur_p))); break;
				case TypeVolley::CRANK:  vec_volley.push_back(make_shared<VolleyCrank>(VolleyCrank(cur_p))); break;
				default: break;
			}
			
		}
	}



	~Level() {

	}
};

