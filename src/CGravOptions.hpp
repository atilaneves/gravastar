#ifndef CGRAVOPTIONS_H
#define CGRAVOPTIONS_H


#include "CMeleeOptions.hpp"
#include "CClientOptions.hpp"
#include <vector>
#include <utility>

class CGravOptions {

public:

    CGravOptions() { }
    CGravOptions(CMeleeOptions meleeOptions, CClientOptions clientOptions)
        : mMeleeOptions(std::move(meleeOptions)),
          mClientOptions(std::move(clientOptions)) {}

    const CClientOptions& GetClientOptions() const { return mClientOptions; }
    const CMeleeOptions&  GetMeleeOptions()  const { return mMeleeOptions;  }
    const int GetServerPort() const { return mServerPort; }

    void push_back(const CClientOptions& clientOptions);


private:

    CMeleeOptions  mMeleeOptions;
    CClientOptions mClientOptions;
    static const int mServerPort = 12346;
};


#endif
