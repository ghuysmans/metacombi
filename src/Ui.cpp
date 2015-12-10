#include "../config.h"
#ifdef USE_SDL

#include <sstream>
#include <vector>
#include "Ui.h"
#include "UiLibrary.h"
#include "Solution.h"

inline std::string itos(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

void draw(Screen& screen, Font& font, const Camera& camera, const Graph& graph, const Solution* const solution) {
	static SDL_Color palette[] = {
		{255, 0, 0}, //red
		{255, 231, 0}, //yellow
		{34, 255, 0}, //light green
		{0, 255, 210}, //light blue
		{251, 124, 18}, //orange
		{171, 11, 35}, //dark red
		{4, 120, 147}, //blue
		{79, 11, 84}, //purple
		{113, 201, 11} //green
	};
	static SDL_Color node = {45, 193, 80};
	static SDL_Color text = {0, 0, 0};
	//instead of using some basic trigonometry,
	//let's just draw the edges first!
	for (int a=0; a<graph.head.size(); a++) {
		const int f = graph.head.at(a);
		const int ct = graph.getCount(a);
		for (int edge=f; edge<f+ct; edge++) {
			const int b = graph.succ.at(edge);
			//first, avoid duplicate labels (undirected graph).
			//second, ignore loops which would look ugly.
			if (a < b) {
				//edge
				int x1=graph.x.at(a), y1=graph.y.at(a);
				int x2=graph.x.at(b), y2=graph.y.at(b);
				int xc=x1+(x2-x1)/2, yc=y1+(y2-y1)/2;
				int s = solution ? solution->getVector().at(edge) : 0;
				camera.transform(x1, y1);
				camera.transform(x2, y2);
				screen.thickLine(x1, y1, x2, y2, 3, palette[s]);
				//caption
				Text capa(font, itos(graph.weights.at(edge)), text);
				camera.transform(xc, yc);
				SDL_Rect pos = {xc-capa.width()/2, yc-capa.height()/2, 0, 0};
				capa.blit(NULL, screen, &pos);
			}
		}
	}
	for (int a=0; a<graph.head.size(); a++) {
		int x=graph.x.at(a), y=graph.y.at(a);
		camera.transform(x, y);
		screen.filledCircle(x, y, 20, node);
		Text num(font, itos(a), text);
		SDL_Rect pos = {x-num.width()/2, y-num.height()/2, 0, 0};
		num.blit(NULL, screen, &pos);
	}
}

/*
 * TODO implement the same thing as c but with the graph's center
 * (arithmetic mean between min and max)
 */
void view(const Graph& graph, const Solution* const solution) {
	Screen screen(1280, 960);
	Camera camera(0, 0, 2, 200, 200, 1.2);
	Font font("DejaVuSansMono.ttf", 16);
	FpsLimiter limiter;
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		limiter.start();
		//rendering
		screen.rect(NULL, -1); //white
		draw(screen, font, camera, graph, solution);
		screen.flip();
		//events processing
		while (SDL_PollEvent(&event)) {
			camera.moveDirection.event(event);
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.unicode == 'd') {
					std::cout << "camera:" << std::endl;
					std::cout << "x=" << camera.x << std::endl;
					std::cout << "y=" << camera.y << std::endl;
					std::cout << "z=" << camera.z << std::endl;
				}
				else if (event.key.keysym.unicode == 'c') {
					int x = graph.x.at(0);
					int y = graph.y.at(0);
					camera.x = camera.z*x-screen.width()/2;
					camera.y = camera.z*y-screen.height()/2;
				}
				else if (event.key.keysym.unicode=='?') {
					std::cout << "zoom (i)n/(o)ut" << std::endl;
					std::cout << "swap directions (x)" << std::endl;
					std::cout << "(c)enter camera" << std::endl;
					std::cout << "(d)ebug" << std::endl;
				}
				else if (event.key.keysym.unicode=='q')
					quit = true;
			}
			else if (event.type == SDL_QUIT)
				quit = true;
		}
		camera.update();
		limiter.wait(30);
	}
	std::cout << "leaving" << std::endl;
}

void ui_main(const Graph& graph) {
	IMG_Init(IMG_INIT_JPG);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableUNICODE(SDL_ENABLE); //also interprets Caps Lock
	SDL_WM_SetCaption(graph.filename.c_str(), NULL);
	TTF_Init();
	try {
		std::vector<int> s(graph.succ.size());
		for (int i=0; i<s.size(); i++)
			s.at(i) = i%4;
		Solution sol(s, graph);
		view(graph, &sol);
	}
	catch (Exception& e) {
		std::cout << e << std::endl;
	}
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}

#endif //USE_SDL