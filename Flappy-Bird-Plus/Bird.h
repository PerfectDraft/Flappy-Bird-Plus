#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <vector>
#include "Entity.h"
#include "Pipe.h"

class Bird: public Entity
{
	float velocity;
	float gravity=9.8;
	int speed=150;
	float mode_x=294;
public:
	int width=40;
	int height=28;
	Bird(SDL_Texture* p_tex);
	void update(float elapsed_time);
	void change_mode();
	float get_angle();
	void flap();
	bool check_colision(std::vector<Pipe> &pipes,int offset);
};


#endif // BIRD_H_INCLUDED
