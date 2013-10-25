#ifndef factory_h
#define factory_h

/***
 *
 * Adapted from POCO library
 *
 */

#include <iostream>       // std::cerr
#include <exception>      // std::exception
#include <mutex>
#include <map>
#include <memory> //shared_ptr
/*
 *  The common base class for all Instantiator instantiations.
 *  Used by DynamicFactory.
 *
 */
template<class Base> class AbstractInstantiator {
public:
	/// Creates the AbstractInstantiator.
	AbstractInstantiator() {
	}

	/// Destroys the AbstractInstantiator.
	virtual ~AbstractInstantiator() {
	}

	/// Creates an instance of a concrete subclass of Base.
	virtual Base* createInstance() const = 0;

private:
	AbstractInstantiator(const AbstractInstantiator&);
	AbstractInstantiator& operator =(const AbstractInstantiator&);
};

/**
 * /// A template class for the easy instantiation of
 /// instantiators.
 ///
 /// For the Instantiator to work, the class of which
 /// instances are to be instantiated must have a no-argument
 /// constructor.
 *
 */
template<class C, class Base> class Instantiator: public AbstractInstantiator<Base> {
public:
	Instantiator()
	/// Creates the Instantiator.
	{
	}

	virtual ~Instantiator()
	/// Destroys the Instantiator.
	{
	}

	Base* createInstance() const {
		return new C;
	}
};


template<class Base>
class DynamicFactory
/// A factory that creates objects by class name.
{
public:
	typedef AbstractInstantiator<Base> AbstractFactory;

	DynamicFactory()
	/// Creates the DynamicFactory.
	{
	}

	~DynamicFactory()
	/// Destroys the DynamicFactory and deletes the instantiators for
	/// all registered classes.
	{
		for (typename FactoryMap::iterator it = _map.begin(); it != _map.end();
				++it) {
			delete it->second;
		}
		std::cout << "Deleting Dynamic Factory..." << std::endl;

	}

	Base* createInstance(const std::string& className) const
	/// Creates a new instance of the class with the given name.
	/// The class must have been registered with registerClass.
	/// If the class name is unknown, a NotFoundException is thrown.
			{

		std::lock_guard < std::mutex > lock(_mutex);

		typename FactoryMap::const_iterator it = _map.find(className);
		if (it != _map.end())
			return it->second->createInstance();
		else
			std::cerr << className << " not found!" << std::endl;
	}

	template<class C>
	void registerClass(const std::string& className)
	/// Registers the instantiator for the given class with the DynamicFactory.
	/// The DynamicFactory takes ownership of the instantiator and deletes
	/// it when it's no longer used.
	/// If the class has already been registered, an ExistsException is thrown
	/// and the instantiator is deleted.
			{
		registerClass(className, new Instantiator<C, Base>);
	}

	/**
	 * Registers the instantiator for the given class with the DynamicFactory.
	 * The DynamicFactory takes ownership of the instantiator and deletes
	 * it when it's no longer used.
	 * If the class has already been registered, an ExistsException is thrown
	 * and the instantiator is deleted.
	 *
	 */
	void registerClass(const std::string& className,
			AbstractFactory* pAbstractFactory)
			{
		if (!pAbstractFactory)
			std::cerr << "Abstract factory null pointer!" << std::endl;

		std::lock_guard < std::mutex > lock(_mutex);


		//std::shared_ptr<AbstractFactory> ptr(pAbstractFactory);
		//std::shared_ptr<AbstractFactory> ptr = std::make_shared<AbstractFactory>(pAbstractFactory);
		//std::shared_ptr<AbstractFactory> ptr = pAbstractFactory;
		typename FactoryMap::iterator it = _map.find(className);
		if (it == _map.end()) {
			_map[className] = pAbstractFactory;
			//std::cout << " -> "<< _map.size() << std::endl;
		}
		else
			std::cerr << className << " not found!" << std::endl;

		std::cout << "Registered class: " << className << " :: Map size = "<< _map.size() << std::endl;

	}

	void unregisterClass(const std::string& className)
	/// Unregisters the given class and deletes the instantiator
	/// for the class.
	/// Throws a NotFoundException if the class has not been registered.
			{
		std::lock_guard < std::mutex > lock(_mutex);

		typename FactoryMap::iterator it = _map.find(className);
		if (it != _map.end()) {
			delete it->second;
			_map.erase(it);
		} else
			std::cerr << className << " not found!" << std::endl;
	}

	bool isClass(const std::string& className) const
	/// Returns true iff the given class has been registered.
			{
		std::lock_guard < std::mutex > lock(_mutex);

		return _map.find(className) != _map.end();
	}

	void printMapContents(){
		std::lock_guard < std::mutex > lock(_mutex);

		typename FactoryMap::iterator it;
		std::cout << "Map Contents :: size = " << _map.size() << std::endl;
		for (it = _map.begin(); it != _map.end(); it++) {
			std::cout << " - " << it->first << std::endl;
		}

	}

private:
	DynamicFactory(const DynamicFactory&);
	DynamicFactory& operator =(const DynamicFactory&);

	typedef std::map<std::string, AbstractFactory*> FactoryMap;

	FactoryMap _map;
	mutable std::mutex _mutex;
};

#endif

