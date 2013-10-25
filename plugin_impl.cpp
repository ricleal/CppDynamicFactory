
#include "plugin_impl.h"

// Global static pointer used to ensure a single instance of the class.
PluginFactorySingleton* PluginFactorySingleton::m_pInstance = NULL;

PluginFactorySingleton* PluginFactorySingleton::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new PluginFactorySingleton;

   return m_pInstance;
}
