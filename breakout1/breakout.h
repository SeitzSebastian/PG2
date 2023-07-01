#pragma once

#include "gui.h"

#include <vector>

struct ball;
class breakout;
enum collistion_type { NONE, HORI, VERT, BOTH };

struct color {
	float r, g, b;
	color(float r, float g, float b) : r(r), g(g), b(b) {}
	void use(cairo_t *cr) { cairo_set_source_rgb(cr, r, g, b); }
};

struct block {
	int x, y;
    int w = 100;
    int h = 40;
	color col;
	block(int x, int y, color col) : x(x), y(y), col(col) {}
	virtual void draw();
	void collision(const ball &b, breakout *game) {}
};

struct ball {
	float x, y, rad = 10;
	float dx, dy, speed = 1;
    ball(float x, float y, float rad) : x(x), y(y), rad(rad), dx(0), dy(0){};
	void position(float posx, float posy);
	void direction(float dirx, float diry);
	void use_random_start_dir(float scale_x, float scale_y);
	virtual void draw();
	void step(float gamespeed);
	virtual void collision(const block &b, breakout *game, collistion_type type);
};

struct board {
	float x, y;
	float w, h, org_w;
	float speed = 1.0;
	color col;
	board(float x, float y, float w, float h) : x(x), y(y), w(w), org_w(w), h(h), col(1,1,1) {}
	virtual void draw();
	virtual void move_left(float by);
	virtual void move_right(float by);
	virtual void bounce(ball &ball);
	void rest(ball &b);
};

class breakout : public windowed_app {
	enum game_state { INIT, PLAY, WAIT, GAMEOVER, PAUSE};
	game_state state = INIT;
	int cells_x = 0, cells_y = 0, block_border_y = 0;
	std::vector<block*> blocks;

	// There could be multiple boards and balls -- that's the reason why a std::vector is used here.
	// If you intend to use one ball and/or board in your app you can use balls/boards.front() in your implementation.
	std::vector<ball> balls;
	std::vector<board*> boards;
	float game_speed = 0.010;
	int lives = 3;
    int score = 0;
    int level = 0;
public:
	breakout(int w, int h);
	void draw() override;
	void tick(int time_diff) override;
    void createBlocks();
};
