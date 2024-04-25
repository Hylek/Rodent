#pragma once

#include "window_manager.h"

class game
{
public:
	game();
	~game();
	bool init();
	void run();

private:
	std::unique_ptr<window_manager> window_;

	void handle_input();
	void update();
	void render();
};

