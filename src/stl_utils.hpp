#ifndef STL_UTILS_H_
#define STL_UTILS_H_

template<typename C>
typename C::value_type popFront(C& container) {
    auto front = container.front();
    container.pop_front();
    return front;
}



#endif // STL_UTILS_H_
