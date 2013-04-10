#ifndef CREF_OR_POINTER_HPP_
#define CREF_OR_POINTER_HPP_

#include <memory>

template<class T>
class CRefOrPointer {
public:

    CRefOrPointer(T* obj):mReference(*obj), mPointer(obj) { }
    CRefOrPointer(T& obj):mReference(obj) { }
    
    explicit operator T*() { return &mReference; }
    operator const T*() const { return &mReference; }
    T* operator->() const { return &mReference; }
    T& operator*() { return mReference; }
    const T& operator*() const { return mReference; }

private:

    T& mReference;
    std::unique_ptr<T> mPointer;
};

#endif
