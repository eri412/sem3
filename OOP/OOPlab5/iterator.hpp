#include <iterator>

template<typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T, int, T*, T&> {
private:
    T *ptr;
public:    
    Iterator(T *start) {
        ptr = start;
    }
    T *get_ptr() {
        return ptr;
    }
    T elem() {
        return *ptr;
    }
    Iterator<T>& operator=(const Iterator<T>& other) {
        ptr = other.ptr;
        return *this;
    }
    Iterator<T>& operator++(int) {
        ptr = ptr->next;
        return *this;
    }
    Iterator<T> operator++() {
        Iterator<T> temp = *this;
        ptr = ptr->next;
        return temp;
    }
    bool operator==(const Iterator<T>& other) const {
        return ptr == other.ptr;
    }
    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }
    T operator*() {
        return *ptr;
    }
};
