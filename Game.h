#pragma once
#include "Level.h"

enum class GameState : uint {
	PAUSE,
	PLAY
};

class Game : public B
{
public:

	void Play();

	Game();
	~Game();

private:

	GameState m_game_state;
	unique_ptr<Level> m_level;
	vector<shared_ptr<AbstractButton>> vec_button;

	sf::Text m_text_volley_count;
	sf::Text m_text_bang_count;
	sf::Text m_text_tail_count;
	sf::Text m_text_all_count;
	sf::Text m_text_fps_count;

	float timer_info_update = 0;
	float upd_info_timer = 0;
	float fps_timer = 0;
	int fps_counter = 0;

private:

	void InfoUpdate();
	void InfoDraw();
	void Update();
	void Action();
	void Draw();

	void UpdateUI();
	void ActionUI();
	void DrawUI();
};