#ifndef CPILOTINPUTFACTORY_H
#define CPILOTINPUTFACTORY_H


class CPilotInputOptions;
class CPilotInput;


class CPilotInputFactory {

public:

  static CPilotInput* CreateInput(const CPilotInputOptions &options);


private:


};


#endif
