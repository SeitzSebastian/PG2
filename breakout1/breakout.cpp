#include "breakout.h"

#include <iostream>
#include <cmath>
using namespace std;

static cairo_t *cr = nullptr;

collistion_type collision(const ball &ball, const block &block) {
    float dist_x = abs(ball.x - block.x - block.w / 2);
    float dist_y = abs(ball.y - block.y - block.h / 2);

    if (dist_x > (block.w / 2 + ball.rad)) {
        return NONE;
    }
    if (dist_y > (block.h / 2 + ball.rad)) {
        return NONE;
    }

    if (dist_x <= (block.w / 2)) {
        return VERT;
    }
    if (dist_y <= (block.h / 2)) {
        return HORI;
    }

    float dx = dist_x - block.w / 2;
    float dy = dist_y - block.h / 2;
    if (dx * dx + dy * dy <= (ball.rad * ball.rad)) {
        return BOTH;
    }

    return NONE;
}

void breakout::createBlocks() {
    blocks.clear();

    std::vector<color> colors = {
            color(0.8, 0.0, 0.0),    // Rot
            color(0.0, 0.8, 0.0),    // Grün
            color(0.0, 0.0, 0.8),    // Blau
            color(1.0, 1.0, 0.0),    // Gelb
            color(1.0, 0.0, 1.0)     // Magenta
    };

    int colorIndex = 0;

    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            color col = colors[colorIndex];
            blocks.push_back(new block(j * 100, i * 40 + 30, col));
            colorIndex = (colorIndex + 1) % colors.size();
        }
    }
}

breakout::breakout(int w, int h)
        : windowed_app(w, h, "BREAKOUT"),
          cells_x(8),
          cells_y(24),
          block_border_y(13) {
    // To be implemented (A3)
    boards.push_back(new board(width/2,height-50,100,50));
    // To be implemented (A4)
    balls.push_back(ball(width/2, height-65, 10));
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
        board &my_board = *boards[0];
        my_board.draw();
        ball &my_ball = balls[0];
        my_ball.draw();
        for (const auto& block : blocks) {
            block->draw();
        }
        cairo_set_source_rgb (cr, 1, 1, 1);
        cairo_move_to (cr, 0, 30);
        cairo_line_to (cr, 600, 30);
        cairo_set_line_width (cr, 5);
        cairo_stroke (cr);
        string lives_text = "Lives:" + std::to_string(lives);
        string score_text = "Score:" + std::to_string(level*100+score);
        cairo_text_extents_t extents;
        cairo_set_font_size(cr,20);
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_text_extents (cr, score_text.c_str(), &extents);
        cairo_move_to(cr,10, 17);
        cairo_show_text(cr, score_text.c_str());
        cairo_text_extents (cr, lives_text.c_str(), &extents);
        cairo_move_to(cr,400, 17);
        cairo_show_text(cr, lives_text.c_str());
    }
    // To be implemented (A4)
    if (state == PLAY){
        board &my_board = *boards[0];
        my_board.draw();
        ball &my_ball = balls[0];
        my_ball.draw();
        for (const auto& block : blocks) {
            block->draw();
        }
        cairo_set_source_rgb (cr, 1, 1, 1);
        cairo_move_to (cr, 0, 30);
        cairo_line_to (cr, 600, 30);
        cairo_set_line_width (cr, 5);
        cairo_stroke (cr);
        string lives_text = "Lives:" + std::to_string(lives);
        string score_text = "Score:" + std::to_string(level*100+score);
        cairo_text_extents_t extents;
        cairo_set_font_size(cr,20);
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_text_extents (cr, score_text.c_str(), &extents);
        cairo_move_to(cr,10, 17);
        cairo_show_text(cr, score_text.c_str());
        cairo_text_extents (cr, lives_text.c_str(), &extents);
        cairo_move_to(cr,400, 17);
        cairo_show_text(cr, lives_text.c_str());
    }
    // To be implemented (A5)
    if (state == GAMEOVER){
        string line1 = "GAMEOVER";
        string line2 = "PRESS SPACE TO PLAY AGAIN";
        cairo_text_extents_t extents;
        cairo_set_font_size(cr,20);
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
        cairo_text_extents (cr, line1.c_str(), &extents);
        cairo_move_to(cr,width/2-extents.width/2, height/2-extents.height/1);
        cairo_show_text(cr,line1.c_str());
        cairo_text_extents (cr, line2.c_str(), &extents);
        cairo_move_to(cr,width/2-extents.width/2, height/2-extents.height/1 + 30 );
        cairo_show_text(cr,line2.c_str());
    }
    if (state == PAUSE) {
        ball &my_ball = balls[0];
        board &my_board = *boards[0];

        string line1 = "PAUSE";
        cairo_text_extents_t extents;
        cairo_set_font_size(cr, 20);
        cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
        cairo_text_extents(cr, line1.c_str(), &extents);
        cairo_move_to(cr, width / 2 - extents.width / 2, height / 3 - extents.height);
        cairo_show_text(cr, line1.c_str());
        string line2 = "Press Button to get Upgrade";
        cairo_text_extents_t extents2;
        cairo_text_extents(cr, line2.c_str(), &extents);
        cairo_move_to(cr, width / 2 - extents.width / 2, height / 3 - extents.height + 60);
        cairo_show_text(cr, line2.c_str());
        string ballspeedtext = "-10% Ballspeed";
        cairo_set_font_size(cr, 15);
        cairo_move_to(cr, 10, 2 * height / 3);
        cairo_show_text(cr, ballspeedtext.c_str());
        string ballspeedbutton = "y";
        cairo_move_to(cr, 60, 2 * height / 3 + 20);
        cairo_show_text(cr, ballspeedbutton.c_str());

        string boardspeedtext = "+15% Boardspeed";
        cairo_move_to(cr, width / 4, 2 * height / 3);
        cairo_show_text(cr, boardspeedtext.c_str());

        string boardspeedbutton;
        if (my_board.speed <= 10) {
            boardspeedbutton = "x";
        } else {
            boardspeedbutton = "MAX";
        }
        cairo_move_to(cr, width / 4 + 60, 2 * height / 3 + 20);
        cairo_show_text(cr, boardspeedbutton.c_str());

        string widthtext = " +25 Boardwidth";
        cairo_move_to(cr, 2 * width / 4, 2 * height / 3);
        cairo_show_text(cr, widthtext.c_str());

        string widthbutton;
        if (my_board.w <= 200) {
            widthbutton = "c";
        } else {
            widthbutton = "MAX";
        }
            cairo_move_to(cr, 2 * width / 4 + 60, 2 * height / 3 + 20);
        cairo_show_text(cr, widthbutton.c_str());
        string sizetext = "+5 Ballsize";
        cairo_move_to(cr, 3 * width / 4, 2 * height / 3);
        cairo_show_text(cr, sizetext.c_str());

        string sizebutton;
        if (my_ball.rad <= 30) {
            sizebutton = "v";
        } else {
            sizebutton = "MAX";
        }
        cairo_move_to(cr, 3 * width / 4 + 50, 2 * height / 3 + 20);
        cairo_show_text(cr, sizebutton.c_str());
        if (level % 1 == 0 && score == 0 && level != 0) {
            if(lives < 3) {
                string livestext = " +1 Live";
                cairo_move_to(cr, 2 * width / 2, 2 * height / 3 +40);
                cairo_show_text(cr, livestext.c_str());

                string livesbutton;
                if (lives >= 5) {
                    widthbutton = "b";
                } else {
                    widthbutton = "MAX";
                }
                cairo_move_to(cr, 2 * width / 2 + 20, 2 * height / 3 + 60);
                cairo_show_text(cr, livesbutton.c_str());
            }
        }
    }
}

void breakout::tick(int time_diff) {
    // To be implemented (A2)
    if (key_pressed[ESC_KEY]) {
        quit_gui();
    }
    // To be implemented (A3)
    if ((key_pressed[' '] && state == INIT) || (state == GAMEOVER && key_pressed[' '])) {
        createBlocks();
        state = WAIT;
    }
    if (state == WAIT) {
        board &my_board = *boards[0];
        for (auto it = balls.begin(); it != balls.end(); ++it) {
            ball &current_ball = *it;
            current_ball.x = my_board.x;
            current_ball.y = my_board.y - (current_ball.rad + 5);
            if (key_pressed['a'] || key_pressed['d']) {
                current_ball.x = my_board.x;
                current_ball.use_random_start_dir(5, 5);
            }
        }
    }

    if (key_pressed['s'] && state == WAIT) {
        state = PLAY;
    }
    board &my_board = *boards[0];
    ball &my_ball = balls[0];
    if (key_pressed['a']) {
        my_board.move_left(10);
        if (my_board.x < 0) {
            my_board.x = 0 + my_board.w / 2;
        }
        boards[0]->x = my_board.x;
    } else if (key_pressed['d']) {
        my_board.move_right(10);
        if (my_board.x > width) {
            my_board.x = width - my_board.w / 2;
        }
        boards[0]->x = my_board.x;
    }

    if (state == PLAY) {
        if (my_ball.dx == 0 && my_ball.dy == 0) {
            my_ball.use_random_start_dir(10, 10);
        }
        my_ball.step(1);
        my_board.bounce(my_ball);
        if (my_ball.y >= height + 22) {
            lives -= 1;
            if (lives > 0) {
                state = WAIT;
                my_ball.x = my_board.x;
                my_ball.y = my_board.y - 20;
            } else if (lives == 0) {
                state = GAMEOVER;
            }
        }
        for (auto it = blocks.begin(); it != blocks.end();) {
            block *current_block = *it;
            collistion_type col_type = collision(my_ball, *current_block);
            if (col_type != NONE) {
                my_ball.collision(*current_block, this, col_type);
                delete current_block;
                score += 10;
                it = blocks.erase(it);
            } else {
                ++it;
            }
        }
        if (blocks.empty()) {
            createBlocks();
            state = WAIT;
        }
        if (score >= 100) {
            level += 1;
            score -= 100;
            cout << level << score;
            state = PAUSE;
        }
    }
    // To be implemented (A5)

    if (state == GAMEOVER) {
        my_ball.x = my_board.x;
        my_ball.y = my_board.y - 20;
        my_ball.dx = 0;
        my_ball.dy = 0;
        my_ball.rad = 10;
        my_board.speed = 1;
        my_board.w = 100;
        lives = 3;
        level = 0;
        score = 0;
    }
    if (state == PAUSE) {
        if (key_pressed['y']) {
            my_ball.dy *= 0.9;
            my_ball.dx *= 0.9;
            state = PLAY;
        }
        if(my_board.speed <= 3) {
            if (key_pressed['x']) {
                my_board.speed *= 1.15;
                state = PLAY;
            }
        }
        if(my_board.w <= 200) {
            if (key_pressed['c']) {
                my_board.w += 25;
                state = PLAY;
            }
        }
        if(my_ball.rad <= 40) {
            if (key_pressed['v']) {
                my_ball.rad += 5;
                state = PLAY;
            }
        }
        if(lives < 3 && lives <= 5) {
            if (key_pressed['b']) {
                lives += 1;
                state = PLAY;
            }
        }
    }
}

// ball
void ball::position(float posx, float posy) {
    x = posx;
    y = posy;
}

void ball::direction(float dirx, float diry) {
    // To be implemented (A4)
    dx = dirx;
    dy = diry;
}

void ball::draw() {
    // To be implemented (A4)
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_arc (cr, x, y, rad, 0., 2 * M_PI);
    cairo_fill(cr);
}

void ball::use_random_start_dir(float scale_x, float scale_y) {
    // To be implemented (A4)
    dx = -1*std::abs(scale_x*random_number());
    dy = -1*std::abs(scale_y*random_number());
}

void ball::step(float gamespeed) {
    // To be implemented (A4)
    if((x-rad <= 0 && y-rad <= 30)||(x+rad >= 600 && y-rad <= 30)){
        dy = -dy;
        dx = -dx;
    }
    else if ( x-rad <= 0 || x+rad >= 600){
        dx = -dx;
    }
    else if (y-rad <= 30){
        dy = -dy;
    }
    x = x+dx;
    y = y+dy;
}

void ball::collision(const block& b, breakout* game, collistion_type type) {
    if (type == BOTH) {
        dy = -dy;
        dx = -dx;
    }
    else if (type == VERT) {
        dy = -dy;
    }
    else if (type == HORI) {
        dx = -dx;
    }
}


// board
void board::draw() {
    // To be implemented (A3)
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_move_to (cr, x-w/2, y);
    cairo_line_to (cr, x+w/2, y);
    cairo_set_line_width (cr, 5);
    cairo_stroke (cr);
}


void board::move_left(float by) {
    // To be implemented (A3)
    this->x = x - by*speed;
}

void board::move_right(float by) {
    // To be implemented (A3)
    this->x = x + by*speed;
}

void board::bounce(ball &ball) {
    // Überprüfe, ob der Ball das Board berührt
    if (ball.y + ball.rad >= this->y && ball.y - ball.rad <= this->y) {
        if (ball.x + ball.rad >= this->x - this->w / 2 && ball.x - ball.rad <= this->x + this->w / 2) {
            ball.dy = -ball.dy;
            if(abs(ball.dy)<10) {
                ball.dy*= 1.01;
            }
            if(abs(ball.dx)<10) {
                ball.dx *= 1.01;
            }
        }
    }
}

void board::rest(ball &ball) {
    // To be implemented (A4)
}

// blocks
void block::draw() {
    cairo_set_line_width (cr, 1);
    cairo_set_source_rgb (cr, col.r, col.g, col.b);
    cairo_rectangle (cr, x, y, w, h);
    cairo_fill (cr);
}