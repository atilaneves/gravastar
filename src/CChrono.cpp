#include "CChrono.hpp"


using std::chrono::duration_cast;


uint32_t CChrono::SinceStartMs() const {
    static const auto start = mClock.now();
    return duration_cast<std::chrono::milliseconds>(mClock.now() - start).count();
}
