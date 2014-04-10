#include "CPilotOptions.hpp"



CPilotOptions::CPilotOptions(const std::string &name,
                             const std::string &type,
                             const CTeam &team,
                             const shipTypes_t &ships,
                             const CPilotInputOptions &inputOptions):
    mName(name), mType(type), mTeam(&team), mShips(ships),
    mInputOptions(inputOptions) {

}
