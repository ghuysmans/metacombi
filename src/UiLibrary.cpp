#include "../config.h"
#ifdef USE_SDL
#include <iostream>
#include <string>
#include "UiLibrary.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"

Uint32 getRGBA(SDL_Color& c) {
	return c.r<<24|c.g<<16|c.b<<8|0xFF;
}

Debuggable::Debuggable(std::string name): name(name) {}
Exception::Exception(std::string message): Debuggable(message) {};

Surface::Surface(std::string name): Debuggable(name) {}
void Surface::blit(SDL_Rect *from, Surface &dest, SDL_Rect *to) const {
	SDL_BlitSurface(surface, from, dest.surface, to);
}
void Surface::flip() {
	SDL_Flip(surface);
}
void Surface::thickLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, SDL_Color& c) {
	thickLineColor(surface, x1, y1, x2, y2, width, getRGBA(c));
}
void Surface::line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, SDL_Color& c) {
	aalineColor(surface, x1, y1, x2, y2, getRGBA(c));
}
void Surface::trigon(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, SDL_Color& c) {
	aatrigonColor(surface, x1, y1, x2, y2, x3, y3, getRGBA(c));
}
void Surface::filledCircle(Sint16 x, Sint16 y, Sint16 r, SDL_Color& c) {
	filledCircleColor(surface, x, y, r, getRGBA(c));
	aacircleColor(surface, x, y, r, getRGBA(c));
}
void Surface::circle(Sint16 x, Sint16 y, Sint16 r, SDL_Color& c) {
	aacircleColor(surface, x, y, r, getRGBA(c));
}
void Surface::rect(SDL_Rect *dest, SDL_Color& c) {
	SDL_FillRect(surface, dest, getRGBA(c));
}
void Surface::rect(SDL_Rect *dest, Uint32 rgb) {
	SDL_FillRect(surface, dest, rgb);
}
int Surface::height() const {
	return surface->h;
}
int Surface::width() const {
	return surface->w;
}

Screen::Screen(int w, int h): Surface("Screen") {
	surface = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE);
	if (!surface)
		throw Exception("SDL_SetVideoMode failed");
}

Image::Image(std::string filename): Surface("I"+filename) {
	std::cout << "loading image " << filename << std::endl;
	surface = IMG_Load(filename.c_str());
	if (!surface)
		throw Exception("IMG_Load failed");
}
Image::~Image() {
	SDL_FreeSurface(surface);
}

Font::Font(std::string filename, int height): Debuggable("F"+filename) {
	std::cout << "loading font " << filename << ", " << height << " px" << std::endl;
	font = TTF_OpenFont(filename.c_str(), height);
	if (!font)
		throw Exception("TTF_OpenFont failed");
}
Font::~Font() {
	TTF_CloseFont(font);
}
TTF_Font* Font::pointer() {
	return font;
}

Text::Text(Font& font, std::string msg, SDL_Color color): Surface("T"+msg) {
	surface = TTF_RenderText_Solid(font.pointer(), msg.c_str(), color);
	if (!surface)
		throw Exception("TTF_RenderText_Solid failed");
}

//TODO turn this into a class handling events
void stringInput(std::string& dest, SDL_Event& event) {
	if (event.type != SDL_KEYDOWN)
		return;
	else {
		char c = event.key.keysym.unicode;
		if (isalpha(c))
			dest += c;
		else if (c == '\b')
			dest.erase(dest.size()-1, 1);
	}
}

Direction::Direction(): inverted(0) {
	/**
	 * TODO is there any way to init the union with an int
	 * directly from the initializer list?
	 */
	directions.as_int = 0;
}
void Direction::event(SDL_Event& e) {
	bool v = e.type==SDL_KEYDOWN;
	if (v || e.type==SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case 'k':
			case SDLK_UP:
				directions.d.up = v;
				break;
			case 'j':
			case SDLK_DOWN:
				directions.d.down = v;
				break;
			case 'h':
			case SDLK_LEFT:
				directions.d.left = v;
				break;
			case 'l':
			case SDLK_RIGHT:
				directions.d.right = v;
				break;
			case 'i': directions.d.in = v; break;
			case 'o': directions.d.out = v; break;
			case 'x':
				//only swap it on KEYDOWN events
				inverted ^= v;
				break;
			default: return;
		}
	}
}
int Direction::x() const {
	return invert()*(directions.d.left-directions.d.right);
}
int Direction::y() const {
	return invert()*(directions.d.up-directions.d.down);
}
int Direction::z() const {
	return directions.d.out-directions.d.in;
}
int Direction::invert() const {
	/**
	 * 1 - 0*2 = 1-0 = 1
	 * 1 - 1*2 = 1-2 = -1
	 */
	return 1-2*(int)inverted;
}

Camera::Camera(float x, float y, float z, float sX, float sY, float sZ): x(x), y(y), z(z), speedX(sX), speedY(sY), speedZ(sZ) {
	prevTicks = SDL_GetTicks();
}
void Camera::update() {
	Uint32 ticks = SDL_GetTicks();
	int dt = ticks-prevTicks;
	x += speedX/1000*dt*moveDirection.x();
	y += speedY/1000*dt*moveDirection.y();
	z += speedZ/1000*dt*moveDirection.z();
	prevTicks = ticks;
}
void Camera::transform(int& px, int& py) const {
	px = z*px - x;
	py = z*py - y;
}

FpsLimiter::FpsLimiter(): started(0) {}
void FpsLimiter::start() {
	started = SDL_GetTicks();
}
/**
 * Capping: if we've spent less than 1/maxFps seconds,
 * wait for the next frame instead of wasting CPU time.
 */
void FpsLimiter::wait(int maxFps) {
	int cap=1000/maxFps, delta;
	if ((delta=SDL_GetTicks()-started) < cap)
		SDL_Delay(cap-delta);
}
#endif //USE_SDL
