#include "breakout.h"

#include <iostream>
#include <cmath>
using namespace std;

static cairo_t *cr = nullptr;

collistion_type collision(const ball &ball, const block &block) {
    return NONE;
}


breakout::breakout(int w, int h)
        : windowed_app(w, h, "BREAKOUT"),
          cells_x(8),
          cells_y(24),
          block_border_y(13) {
    // To be implemented (A3)
    boards.push_back(new board(width/2,height-50,50,50));
    // To be implemented (A4)
}

void breakout::draw() {
    ::cr = cr;
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    if (state == INIT) {
        // To be implemented (A2)
        string text = "Press SPACE to start";
        cairo_text_extents_t extents;
        cairo_set_font_size(cr,20);
        cairo_text_extents (cr, text.c_str(), &extents);
        cairo_move_to(cr,width/2-extents.width/2, height/2-extents.height/1);
        cairo_show_text(cr,text.c_str());
    }

    if (state == WAIT){
        // To be implemented (A3)
        board my_board = *boards[0];
        my_board.draw();
        ball my_ball;
        my_ball.position(my_board.x, my_board.y-10);
        my_ball.draw();
        cout << my_ball.y << ' ' << my_board.y << endl;
        if(key_pressed['a']){
            my_board.move_left(10);
            if (my_board.x < 0){
                my_board.x = 0 + my_board.w/2;
            }
            boards[0]->x = my_board.x;
        }
        else if(key_pressed['d']){
            my_board.move_right(10);
            if (my_board.x > width){
                my_board.x = width - my_board.w/2;
            }
            boards[0]->x = my_board.x;
        }

    }
    // To be implemented (A4)
    // To be implemented (A5)

}

void breakout::tick(int time_diff) {
    // To be implemented (A2)
    if (key_pressed[ESC_KEY]){
        quit_gui();
    }
    // To be implemented (A3)
    if (key_pressed[' ']){
        state = WAIT;
    }
    // To be implemented (A4)
    // To be implemented (A5)
}

// ball
void ball::position(float posx, float posy) {
    x = posx;
    y = posy;
}

void ball::direction(float dirx, float diry) {
    // To be implemented (A4)
}

void ball::draw() {
    // To be implemented (A4)
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_arc (cr, x, y, 0.3, 0., 2 * M_PI);
}

void ball::use_random_start_dir(float scale_x, float scale_y) {
    // To be implemented (A4)
}

void ball::step(float gamespeed) {
    // To be implemented (A4)
}

void ball::collision(const block &b, breakout *game, collistion_type type) {
}

// board
void board::draw() {
    // To be implemented (A3)
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_move_to (cr, x-50, y);
    cairo_line_to (cr, x+50, y);
    cairo_set_line_width (cr, 5);
    cairo_stroke (cr);
}


void board::move_left(float by) {
    // To be implemented (A3)
        this->x = x - by;
}

void board::move_right(float by) {
    // To be implemented (A3)
    this->x = x + by;
}

void board::bounce(ball &ball) {
}

void board::rest(ball &ball) {
    // To be implemented (A4)
}

// blocks
void block::draw() {
}
