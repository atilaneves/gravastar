#ifndef CSHIPMENUICON_H
#define CSHIPMENUICON_H


#include "CMenu.hpp"
#include "CDirectory.hpp"
#include <string>
class CVersusMenu;
class CDataFile;


class CShipMenuItem: public CMenu {

public:

  CShipMenuItem(const std::string &title, const CVersusMenu &versus);

  const std::string& GetShipName()    const;
  const std::string& GetWeaponName()  const { return mWeaponName; }
  const std::string& GetSpecialName() const { return mSpecialName; }
  const std::string& GetSuperName()   const { return mSuperName; }


private:

  const CVersusMenu &mVersus;
  CDirectory mDir;
  std::string mShipName;
  std::string mWeaponName;
  std::string mSpecialName;
  std::string mSuperName;

  static std::string GetFileName(const std::string &title);
  static int         GetIndex(const std::string &title);
         void        SetNames(const std::string &title,
			      const CDataFile &dataFile);

};


#endif
