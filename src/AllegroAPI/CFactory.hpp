#ifndef CFACTORY_H
#define CFACTORY_H


#include <map>
#include <vector>
#include <iostream>
#include <functional>

template <class TAbstract, typename TIdentifier, typename... Args>
class CFactory {

public:

    using TCreateCB = std::function<TAbstract*(Args ...args)>;
    using AssocMap = std::map<TIdentifier, TCreateCB>;

    const std::vector<TIdentifier>& GetKeys() const { return mKeys; }

    static CFactory& Instance() {
        static CFactory factory;
        return factory;
    }

    bool Register(const TIdentifier& id, TCreateCB creator) {
        mKeys.push_back(id);
        return mMap.insert(typename AssocMap::value_type(id, creator)).second;
    }

    bool Unregister(const TIdentifier& id) {
        return mMap.erase(id) == 1;
    }

    TAbstract* CreateObject(const TIdentifier& id, Args ...args) const {
        typename AssocMap::const_iterator i = mMap.find(id);
        return i != mMap.end() ? (i->second)(args...) : nullptr;
    }

protected:

    CFactory()  {}
    ~CFactory() {}

private:

    AssocMap mMap;
    std::vector<TIdentifier> mKeys;

    CFactory(const CFactory&); //nobody can call this
};


#endif
