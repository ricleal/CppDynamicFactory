#ifndef plugin_h
#define plugin_h

#include "plugin_impl.h"

/**
 * Algorithm1
 */
class Plugin1: public IPlugin {
public:
	Plugin1() {
	}
	;
	virtual ~Plugin1() {
	}
	;
	void init() {
		std::cout << "Init: Algorithm1" << std::endl;
	}
	;
	void exec();

};

/**
 * Algorithm2
 */
class Plugin2: public IPlugin {
public:
	Plugin2() {
	}
	;
	virtual ~Plugin2() {
	}
	;
	void init() {
		std::cout << "Init: Algorithm2" << std::endl;
	}
	;
	void exec();

};

#endif
