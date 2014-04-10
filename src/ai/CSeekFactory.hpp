#ifndef CSEEK_FACTORY_H
#define CSEEK_FACTORY_H


#include "CFactory.hpp"
#include "CSeekAndDestroy.hpp"
#include <string>


typedef CSeekAndDestroy* (*CreateSeekCB)(CPilotBot&);
typedef CFactory<CSeekAndDestroy, std::string,
                 CPilotBot&> CSeekFactory;

#define REG_SEEK(sname,cname) static CSeekAndDestroy *CreateSeek(CPilotBot &p)\
 { return new cname(p); } \
 static const bool regSeek=\
 CSeekFactory::Instance().Register(sname, CreateSeek);

#define REG_SEEK2(sname,cname) static CSeekAndDestroy *CreateSk2(CPilotBot &p)\
 { return new cname(p); } \
 static const bool regSeek2=\
 CSeekFactory::Instance().Register(sname, CreateSk2);

#define REG_SEEK3(sname,cname) static CSeekAndDestroy *CreateSk3(CPilotBot &p)\
 { return new cname(p); } \
 static const bool regSeek3=\
 CSeekFactory::Instance().Register(sname, CreateSk3);


#endif
