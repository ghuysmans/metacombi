#include <sstream>

std::string itos(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}
