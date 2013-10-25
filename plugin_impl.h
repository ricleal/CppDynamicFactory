#ifndef plugin_impl_h
#define plugin_impl_h


#include "factory.h"

#include <string>
#include <iostream>
#include <cstring>


/**
 * Algorithm / Plugin interface
 */
class IPlugin {
public:
	virtual void init() = 0;
	virtual void exec() = 0;
private:
	bool success;
};

/********************************************
 * RegistrationHelper
 *
 */
class RegistrationHelper
{
public:
	/** Constructor. Does nothing.
	 * @param i :: Takes an int and does nothing with it
	 */
	inline RegistrationHelper(int i) {(void)i;}
};



class PluginFactorySingleton{
public:
   static PluginFactorySingleton* Instance();
   DynamicFactory<IPlugin> pluginFactory;
private:
   PluginFactorySingleton(){};  // Private so that it can  not be called
   PluginFactorySingleton(PluginFactorySingleton const&){};             // copy constructor is private
   PluginFactorySingleton& operator=(PluginFactorySingleton const&){};  // assignment operator is private
   static PluginFactorySingleton* m_pInstance;
};



class PluginFactory{
public:
	static DynamicFactory<IPlugin> pluginFactory;
};




#define DECLARE_ALGORITHM(classname) \
    namespace { \
  RegistrationHelper register_alg_##classname( \
      (( PluginFactorySingleton::Instance()->pluginFactory.registerClass<classname>(#classname) ) \
          , 0)); \
}


#endif
