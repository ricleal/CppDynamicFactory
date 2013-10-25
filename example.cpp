// SimpleDynCreate.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "plugin_impl.h"
#include "plugin.h"

int main(int argc, char* argv[]) {


//	DynamicFactory<IPlugin> pluginFactory;

	std::cout << "Main start..." << std::endl;
	PluginFactorySingleton::Instance()->pluginFactory.printMapContents();
//
//	pluginFactory.registerClass<Plugin1>("Plugin1");
//	pluginFactory.printMapContents();
//	pluginFactory.registerClass<Plugin2>("Plugin2");
//	pluginFactory.printMapContents();

	IPlugin *p1 = PluginFactorySingleton::Instance()->pluginFactory.createInstance("Plugin1");
	p1->init();
	p1->exec();
	delete p1;

	std::cout << "Main end!" << std::endl;
	return 0;
}
