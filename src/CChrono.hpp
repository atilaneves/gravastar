#ifndef CCHRONO_HPP_
#define CCHRONO_HPP_

#include <chrono>

class CChrono {

public:

    uint32_t SinceStartMs() const;

private:

    std::chrono::high_resolution_clock mClock;
};


#endif
