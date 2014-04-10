#ifndef CCYCLETEAM_H
#define CCYCLETEAM_H


#include "CCycleString.hpp"
class CTeam;



class CCycleTeam:public CCycleString {

public:

  CCycleTeam(const std::string &title);

  const CTeam& GetTeam() const;

};


#endif
