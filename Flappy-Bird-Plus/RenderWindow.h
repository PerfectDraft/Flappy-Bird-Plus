#ifndef RENDERWINDOW_H_INCLUDED
#define RENDERWINDOW_H_INCLUDED

#include <SDL.h>

class RenderWindow
{
	SDL_Renderer *renderer=NULL;
	SDL_Window *window=NULL;
	TTF_Font* Sans = NULL;
	SDL_Texture* Message=NULL;
	SDL_Surface* surfaceMessage=NULL;
public:
	RenderWindow(const char* p_title,int p_w,int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void rendertext(char* text,SDL_Color &color,int x,int y,int height,int width);
	void display();
	void clear();
	void cleanup();
	void update_frames(gametime frames);
	SDL_Renderer* get_renderer(){return renderer;}
	SDL_Window* get_window(){return window;}
};


#endif // RENDERWINDOW_H_INCLUDED
