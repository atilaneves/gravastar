#ifndef CPILOTOPTIONS_H
#define CPILOTOPTIONS_H


#include "CPilotInput.hpp"
#include "CPilotInputOptions.hpp"
#include "CTeam.hpp"
#include <vector>
#include <string>


typedef std::vector<std::string> shipTypes_t;


class CPilotOptions {

public:

  CPilotOptions(const std::string &name, const std::string& type,
                const CTeam &team,
                const shipTypes_t &ships,
                const CPilotInputOptions &inputOptions);

  const CPilotInputOptions& GetInputOptions() const { return mInputOptions; }
  const std::string& GetName()                const { return mName;         }
  const unsigned int GetNbShips()             const { return mShips.size(); }
  const std::string& GetShipName(unsigned int s) const { return mShips[s]; }
  const CTeam&       GetTeam()                const { return *mTeam;        }
  const std::string& GetType()                const { return mType;         }
        void         SetBot()                       { mType = "Bot"; }


private:

  std::string         mName;
  std::string         mType;
  const CTeam*        mTeam;  //has to be ptr cos of STL
  shipTypes_t         mShips;
  CPilotInputOptions  mInputOptions;

};


#endif
