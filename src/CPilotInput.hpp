#ifndef CPILOTINPUT_H
#define CPILOTINPUT_H


#include <vector>
#include <string>


class CPilotInput {

public:

  static int GetNbControls() { return sNames.size(); }
  static const std::string& GetName(int i)  { return sNames[i]; }

  bool IsOn(const std::string &which) const;
  virtual bool Left()       const = 0;
  virtual bool Right()      const = 0;
  virtual bool Thrust()     const = 0;
  virtual bool Weapon()     const = 0;
  virtual bool Special()    const = 0;
  virtual bool Super()      const = 0; 
  virtual bool Start()      const = 0;
  virtual bool MenuUp()     const = 0;
  virtual bool MenuDown()   const = 0;
  virtual bool MenuSelect() const = 0;
  virtual bool MenuCancel() const = 0;

private:

  static std::vector<std::string> sNames;

};

#endif
