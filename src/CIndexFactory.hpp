#ifndef CINDEX_FACTORY_H
#define CINDEX_FACTORY_H


#include "CFactory.hpp"


template<typename TAbstract, typename... Args>
class CIndexFactory:public CFactory<TAbstract, int, Args...> {

public:
    using TCreateCB = typename CFactory<TAbstract, int, Args...>::TCreateCB;
    int                   GetNbClasses() const { return mNbClasses; }
    static CIndexFactory& Instance();
    int                   Register(TCreateCB creator);


private:

    int mNbClasses; 

    CIndexFactory(); //private ctor
    CIndexFactory(const CIndexFactory&); //nobody can call this
    ~CIndexFactory() {} //private dtor

};


template<typename TAbstract, typename...Args>
CIndexFactory<TAbstract, Args...>::CIndexFactory():
                  CFactory<TAbstract, int, Args...>(),
                  mNbClasses(0) {
}


template<typename TAbstract, typename...Args>
CIndexFactory<TAbstract, Args...>&
CIndexFactory<TAbstract, Args...>::Instance() { 
    static CIndexFactory<TAbstract, Args...> factory;
    return factory;
}


template<typename TAbstract, typename...Args>
int CIndexFactory<TAbstract, Args...>::Register(TCreateCB creator) {
    CFactory<TAbstract, int, Args...>::Register(mNbClasses, creator);
    return mNbClasses++;
}

#endif
