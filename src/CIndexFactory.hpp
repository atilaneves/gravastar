#ifndef CINDEX_FACTORY_H
#define CINDEX_FACTORY_H


#include "CFactory.hpp"


template<typename TAbstract,typename TCreateCB,
	 typename TParam1=int,typename TParam2=int,
	 typename TParam3=int,typename TParam4=int>
class CIndexFactory:public CFactory<TAbstract,int,TCreateCB,TParam1,TParam2,
				    TParam3, TParam4> {

public:
 
        int            GetNbClasses() const { return mNbClasses; }
 static CIndexFactory& Instance();
        int            Register(TCreateCB creator);


private:

 int mNbClasses; 

 CIndexFactory(); //private ctor
 CIndexFactory(const CIndexFactory&); //nobody can call this
 ~CIndexFactory() {} //private dtor

};


template<typename TAbstract,typename TCreateCB,
	 typename TParam1,typename TParam2,typename TParam3,typename TParam4>
CIndexFactory<TAbstract,TCreateCB,TParam1,
	      TParam2,TParam3,TParam4>::CIndexFactory():
   CFactory<TAbstract,int,TCreateCB,TParam1,TParam2,TParam3,TParam4>(),
   mNbClasses(0) {
}


template<typename TAbstract,typename TCreateCB,
	 typename TParam1,typename TParam2,typename TParam3,typename TParam4>
CIndexFactory<TAbstract,TCreateCB,TParam1,TParam2,TParam3,TParam4> &
 CIndexFactory<TAbstract,TCreateCB,TParam1,TParam2,TParam3,TParam4>::Instance() { 
 static CIndexFactory<TAbstract,TCreateCB,TParam1,TParam2,TParam3,TParam4> factory;
 return factory;
}


template<typename TAbstract,typename TCreateCB,
	 typename TParam1,typename TParam2,typename  TParam3,typename TParam4>
int CIndexFactory<TAbstract,TCreateCB,TParam1,TParam2,TParam3,TParam4>::Register(
						 TCreateCB creator) {
 CFactory<TAbstract,int,TCreateCB,TParam1,TParam2,
   TParam3,TParam4>::Register(mNbClasses,
			      creator);
 return mNbClasses++;
}

#endif
