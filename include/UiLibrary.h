#if defined(USE_SDL) && !defined(_UILIBRARY_H)
#define _UILIBRARY_H

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"

Uint32 getRGBA(SDL_Color& c);

class Debuggable {
	public:
		const std::string name;
		/**
		 * @param name debug string
		 */
		Debuggable(std::string name);
		/**
		 * @note inline because this is very short
		 */
		friend inline std::ostream& operator<<(std::ostream& o, Debuggable& d) {
			return o << d.name;
		}
};

/**
 * That's not really consistent with the standard exception class
 * but since I don't have anything to implement here...
 */
class Exception: public Debuggable {
	public:
		Exception(std::string message);
};

class Surface: public Debuggable {
	public:
		Surface(std::string name);
		void blit(SDL_Rect *from, Surface &dest, SDL_Rect *to) const;
		void flip();
		void thickLine(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, SDL_Color& c);
		void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, SDL_Color& c);
		void trigon(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, SDL_Color& c);
		void filledCircle(Sint16 x, Sint16 y, Sint16 r, SDL_Color& c);
		void circle(Sint16 x, Sint16 y, Sint16 r, SDL_Color& c);
		/**
		 * @param dest NULL indicates the whole surface
		 */
		void rect(SDL_Rect *dest, SDL_Color& c);
		void rect(SDL_Rect *dest, Uint32 rgb);
		int height() const;
		int width() const;
	protected:
		SDL_Surface *surface;
};

class Screen: public Surface {
	public:
		Screen(int w, int h);
};

class Image: public Surface {
	public:
		Image(std::string filename);
		~Image();
};

class Font: public Debuggable {
	public:
		Font(std::string filename, int height);
		~Font();
		TTF_Font *pointer();
	protected:
		TTF_Font *font;
};

class Text: public Surface {
	public:
		Text(Font& font, std::string msg, SDL_Color color);
	protected:
		void render(Font& font, std::string& msg, SDL_Color& fg);
};

/**
 * Basic text input object.
 * @bug no UTF-8 support
 * @bug no cursor support (only backspace is supported)
 * @bug no selection support
 * TODO use templates to display the string
 */
class TextInput: public Text {
	public:
		TextInput(Font& font, std::string& text, SDL_Color& fg);
		void event(SDL_Event& event);
		/**
		 * @note use this when any of the attributes gets modified.
		 */
		void render();
		std::string text;
		Font& font;
		SDL_Color fg;
};

class Direction {
	public:
		Direction();
		void event(SDL_Event& e);
		/**
		 * @return X component sign
		 * @return 0 when opposite direction keys are pressed
		 */
		int x() const;
		int y() const; /**< @see x */
		int z() const; /**< @see x */
		union {
			/**
			 * Beware: because of two's complement,
			 * values we read are negative!
			 * We don't want to use unsigned, though,
			 * since we'll substract them in x(), y(), z().
			 */
			struct {
				int up:1;
				int right:1;
				int down:1;
				int left:1;
				int in:1;
				int out:1;
			} d;
			int as_int;
		} directions;
		bool inverted; /**< swap directions (except in/out) */
	private:
		int invert() const;
};

class Camera {
	public:
		/**
		 * @note speeds are expressed in pixels/second
		 */
		Camera(float x, float y, float z, float sX, float sY, float sZ);
		void update();
		void transform(int& px, int& py) const;
		Direction moveDirection;
		float x, speedX;
		float y, speedY;
		float z, speedZ; /**< zoom */
	private:
		Uint32 prevTicks;
};

class FpsLimiter {
	public:
		FpsLimiter();
		void start();
		/**
		 * Capping: if we've spent less than 1/maxFps seconds,
		 * wait for the next frame instead of wasting CPU time.
		 */
		void wait(int maxFps);
	private:
		Uint32 started;
};

#endif //_UILIBRARY_H
