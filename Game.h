#pragma once

#include "window_manager.h"

class game
{
public:
	game();
	~game();
	bool init();
	void run() const;

private:
	std::unique_ptr<window_manager> window_;
};

