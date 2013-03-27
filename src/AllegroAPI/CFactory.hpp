#ifndef CFACTORY_H
#define CFACTORY_H


#include <map>
#include <vector>
#include <iostream>

template <class TAbstract, typename TIdentifier, typename TCreateCB,
          typename TParam1=int, typename TParam2=int, typename TParam3=int,
          typename TParam4=int, typename TParam5=int> 
class CFactory {

public:

    typedef std::map<TIdentifier, TCreateCB> AssocMap;

    const std::vector<TIdentifier>& GetKeys() const { return mKeys; }

    static CFactory& Instance() { 
        static CFactory factory;
        return factory;
    }

    bool Register(const TIdentifier& id, TCreateCB creator) {
        std::cout << "Registering " << id << std::endl;
        mKeys.push_back(id);
        return mMap.insert(typename AssocMap::value_type(id, creator)).second;
    }

    bool Unregister(const TIdentifier& id) {
        return mMap.erase(id) == 1;
    }

    TAbstract* CreateObject(const TIdentifier& id) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)() : 0;
    }

    TAbstract* CreateObject(const TIdentifier& id, TParam1 param1) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(param1) : 0;
    }

    TAbstract* CreateObject(const TIdentifier& id,
                            TParam1 param1, TParam2 param2) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(param1, param2) : 0;
    }

    TAbstract* CreateObject(const TIdentifier& id,
                            TParam1 param1, TParam2 param2, TParam3 param3) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(param1, param2, param3) : 0;
    }

    TAbstract* CreateObject(const TIdentifier& id,
                            TParam1 param1, TParam2 param2,
                            TParam3 param3, TParam4 param4) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(param1, param2, param3, param4) : 0;
    }

    TAbstract* CreateObject(const TIdentifier& id,
                            TParam1 param1, TParam2 param2,
                            TParam3 param3, TParam4 param4, TParam5 param5) {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(param1, param2, param3, param4,
                                             param5) : 0;
    }


protected:

    CFactory()  {} //protected ctor
    ~CFactory() {} //protected dtor


private:
 
    AssocMap mMap;
    std::vector<TIdentifier> mKeys;

    CFactory(const CFactory&); //nobody can call this


};


#endif
