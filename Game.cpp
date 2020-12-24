#pragma once
#include "Game.h"

Game::Game() : B("init")
{
	m_game_state = GameState::PLAY;
	m_level = make_unique<Level>(Level());
	vec_button.push_back(make_shared<ButtonClickActiveWithText>(CreateShape(v2f(scr_w / 2,scr_h / 2 - 26), v2f(250,50), 2, Color::Green, Color::Black), "Continue"));
	vec_button.push_back(make_shared<ButtonClickActiveWithText>(CreateShape(v2f(scr_w / 2,scr_h / 2 + 26), v2f(250,50), 2, Color::Red, Color::Black), "Exit"));
	SystemUpdate();
}

void Game::InfoUpdate() {
	upd_info_timer += time;
	fps_counter++;
	fps_timer += time;
	if(upd_info_timer >= 500) {
		m_text_bang_count = CreateText(v2f(0, 50), 25, "Bangs Elems: " + to_string(m_level->GetBangCount()), resources.font.erica_type, Color::Yellow);
		m_text_bang_count.setOrigin(0,0);
		m_text_volley_count = CreateText(v2f(0, 75), 25, "Volley Elems: " + to_string(m_level->GetVolleyCount()), resources.font.erica_type, Color::Yellow);
		m_text_volley_count.setOrigin(0,0);
		m_text_tail_count = CreateText(v2f(0, 100), 25, "Tail Elems: " + to_string(m_level->GetTailCount()), resources.font.erica_type, Color::Yellow);
		m_text_tail_count.setOrigin(0,0);
		m_text_all_count = CreateText(v2f(0, 125), 25, "All Elems: " + to_string(m_level->GetTailCount() + m_level->GetBangCount() + m_level->GetVolleyCount()), resources.font.erica_type, Color::Yellow);
		m_text_all_count.setOrigin(0,0);
		if(fps_timer >= 1000) {
			m_text_fps_count = CreateText(v2f(0, 25), 25, "FPS: " + to_string(fps_counter), resources.font.erica_type, Color::Yellow);
			m_text_fps_count.setOrigin(0,0);
			fps_timer = 0;
			fps_counter = 0;
		}
		upd_info_timer = 0;
	}
}

void Game::InfoDraw() {
	wnd.draw(m_text_fps_count);
	wnd.draw(m_text_bang_count);
	wnd.draw(m_text_volley_count);
	wnd.draw(m_text_tail_count);
	wnd.draw(m_text_all_count);
}

void Game::Update() {
	switch (m_game_state)
	{
	case GameState::PAUSE: UpdateUI(); break;
	case GameState::PLAY: m_level->Update(); break;
	default: break;
	}
}

void Game::Action() {
	switch (m_game_state)
	{
	case GameState::PAUSE:
		if(IsKeyPressed(Key::Escape)) m_game_state = GameState::PLAY;
		ActionUI();
		break;
	case GameState::PLAY:
		if(IsKeyPressed(Key::Escape)) m_game_state = GameState::PAUSE;
		m_level->Action();
		break;
	default: break;
	} 
}

void Game::Draw() {
	wnd.clear();
	m_level->Draw();
	DrawUI();
	switch (m_game_state)
	{
	case GameState::PAUSE:
		
		break;
	case GameState::PLAY:
		break;
	default: break;
	}
	
	
	wnd.display();
}

void Game::UpdateUI() {
	wnd.setView(wnd.getDefaultView());
	for(auto button : vec_button)
		button->Update();
	wnd.setView(cam);
}

void Game::ActionUI() {
	wnd.setView(wnd.getDefaultView());
	for(auto button : vec_button)
		if(button->IsAction()) {
			if(button->GetActionId() == "Continue") m_game_state = GameState::PLAY;
			if(button->GetActionId() == "Exit") wnd.close();
		}
	wnd.setView(cam);
}

void Game::DrawUI() {
	wnd.setView(wnd.getDefaultView());
	InfoDraw();
	if(m_game_state == GameState::PAUSE)
		for(auto button : vec_button)
			button->Draw();
	wnd.setView(cam);
}

void Game::Play() {
	while (wnd.isOpen()) {
		SystemUpdate();
		InfoUpdate();
		Update();
		while (wnd.pollEvent(event)) {
			CloseEvent();
			Action();
		}
		Draw();
	}
}

Game::~Game() { }

int main()
{
	Game game;
	game.Play();
	return 0;
}