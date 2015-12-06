#include "../config.h"
#ifdef USE_SDL

#include <sstream>
#include <vector>
#include "Ui.h"
#include "UiLibrary.h"

class Node {
	public:
		int x;
		int y;
		Node(int a, int b): x(a), y(b) {}
};

class Edge: public Node {
	public:
		Edge(int a, int b): Node(a, b) {}
};

inline std::string itos(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

void draw(Screen& screen, Font& font, const Camera& camera, const std::vector<Node>& nodes, const std::vector<Edge>& edges) {
	static SDL_Color red = {176, 14, 60};
	static SDL_Color green = {45, 193, 80};
	static SDL_Color white = {255, 255, 255};
	//instead of using some basic trigonometry,
	//let's just draw the edges first!
	std::vector<Edge>::const_iterator it;
	for (it=edges.begin(); it!=edges.end(); ++it) {
		//first, avoid duplicate labels (undirected graph).
		//second, ignore loops which would look ugly.
		if (it->x < it->y) {
			const Node *a = &nodes.at(it->x);
			const Node *b = &nodes.at(it->y);
			//edge
			int x1=a->x, y1=a->y;
			int x2=b->x, y2=b->y;
			camera.transform(x1, y1);
			camera.transform(x2, y2);
			screen.thickLine(x1, y1, x2, y2, 3, red);
			//caption
			Text capa(font, "999", white); //TODO
			int xc=a->x+(b->x-a->x)/2, yc=a->y+(b->y-a->y)/2;
			camera.transform(xc, yc);
			SDL_Rect pos = {xc-capa.width()/2, yc-capa.height()/2, 0, 0};
			capa.blit(NULL, screen, &pos);
		}
	}
	std::vector<Node>::const_iterator it2;
	int i=0; //display indexes we actually use
	for (it2=nodes.begin(); it2!=nodes.end(); ++it2, ++i) {
		int x=it2->x, y=it2->y;
		camera.transform(x, y);
		screen.filledCircle(x, y, 10, green);
		Text num(font, itos(i), white);
		SDL_Rect pos = {x-num.width()/2, y-num.height()/2, 0, 0};
		num.blit(NULL, screen, &pos);
	}
}

void view(const std::vector<Node>& nodes, const std::vector<Edge>& edges) {
	Screen screen(640, 480);
	Camera camera(0, 0, 2, 40, 40, 1.2);
	Font font("DejaVuSansMono.ttf", 16);
	FpsLimiter limiter;
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		limiter.start();
		//rendering
		screen.rect(NULL, 0); //clear
		draw(screen, font, camera, nodes, edges);
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
					const Node *a = &nodes.at(0);
					camera.x = camera.z*a->x-screen.width()/2;
					camera.y = camera.z*a->y-screen.height()/2;
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
	//FIXME
	SDL_WM_SetCaption("nodes display test", NULL);
	TTF_Init();
	try {
		std::vector<Node> l;
		std::vector<Edge> e;
		l.push_back(Node(20, 30));
		l.push_back(Node(60, 30));
		l.push_back(Node(30, 60));
		e.push_back(Edge(0, 1));
		e.push_back(Edge(0, 2));
		view(l, e);
	}
	catch (Exception& e) {
		std::cout << e << std::endl;
	}
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}

#endif //USE_SDL
