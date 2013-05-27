#ifndef NETWORK_BUFFERS_H_
#define NETWORK_BUFFERS_H_


#include <deque>
#include <iostream>



template<class A>
std::deque<std::string> msgBufToDeque(const A& buf, size_t len) {
    std::string bufStr{buf.cbegin(), buf.cbegin() + len};
    std::istringstream stream{bufStr};
    std::deque<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(stream),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::deque<std::string>>(tokens));
    return tokens;
}




#endif // NETWORK_BUFFERS_H_
