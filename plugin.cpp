#include "plugin.h"



DECLARE_ALGORITHM(Plugin1)

void Plugin1::exec(){
	std::cout << "Exec: Algorithm1" << std::endl;
}

DECLARE_ALGORITHM(Plugin2)

void Plugin2::exec() {
	std::cout << "Exec: Algorithm2" << std::endl;
}
