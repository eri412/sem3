#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <algorithm>

const std::size_t DEFAULT_CAPACITY = 8;
const unsigned int CAPACITY_MULTIPLIER = 2;
const unsigned int FIRST_LEN = 1;
const unsigned int MIDDLE_LEN = 3;
const unsigned int LAST_LEN = 2;
const std::size_t DIGIT_SIZE = 256;

template <typename T>
class TVector {
public:
    TVector() {
        size = 0;
        capacity = DEFAULT_CAPACITY;
        buff = new T[DEFAULT_CAPACITY];
    }
    ~TVector() {
        delete[] buff;
    }
    std::size_t Size() const {
        return size;
    }
    T& operator[](std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Out of range index");
        }
        return buff[index];
    }
    TVector(const TVector& other) {
        size = other.size;
        capacity = other.capacity;
        buff = new T[capacity];
        std::memcpy((void *) buff, (void *) other.buff, size * sizeof(T));
    }
    void Push(T value) {
        if (size == capacity) {
            Grow();
        }
        buff[size++] = value;
    }
    /*void Pop() {
        if (size == 0) {
            return;
        }
        --size;
        if (size * CAPACITY_MULTIPLIER <= capacity) {
            Shrink();
        }       
    }*/
    T *Begin() const {
        return buff;
    }
    T *End() const {
        return buff + size;
    }

private:
    std::size_t size;
    std::size_t capacity;
    T *buff;

    void Grow() {
        capacity *= CAPACITY_MULTIPLIER;
        T *temp = buff;
        buff = new T[capacity];
        std::memcpy((void *) buff, (void *) temp, size * sizeof(T));
        delete[] temp;
    }
    /*void Shrink() {
        if (capacity == DEFAULT_CAPACITY) {
            return;
        }
        capacity /= CAPACITY_MULTIPLIER;
        T *temp = buff;
        buff = new T[capacity];
        std::memcpy((void *) buff, (void *) temp, size * sizeof(T));
        delete[] temp;
    }*/
};

class TRecord {
public:
    char key[FIRST_LEN + MIDDLE_LEN + LAST_LEN + 1];
    std::uint64_t value;
    bool operator<(const TRecord& other) const {
        if (std::strcmp(key, other.key) == -1) {
            return 1;
        }
        else {
            return 0;
        }
    }
};

std::ostream& operator<<(std::ostream& output, const TRecord& record) {
    unsigned char first[FIRST_LEN + 1], middle[MIDDLE_LEN + 1], last[LAST_LEN + 1];
    std::memcpy(first, record.key, FIRST_LEN);
    first[FIRST_LEN] = '\0';
    std::memcpy(middle, record.key + FIRST_LEN, MIDDLE_LEN);
    middle[MIDDLE_LEN] = '\0';
    std::memcpy(last, record.key + FIRST_LEN + MIDDLE_LEN, LAST_LEN);
    last[LAST_LEN] = '\0';
    output << first << ' ' << middle << ' ' << last << '\t' << record.value;
    return output;
}

std::istream& operator>>(std::istream& input, TRecord& record) {
    unsigned char first[FIRST_LEN + 1], middle[MIDDLE_LEN + 1], last[LAST_LEN + 1];
    input >> first >> middle >> last >> record.value;
    std::memcpy(record.key, first, FIRST_LEN);
    std::memcpy(record.key + FIRST_LEN, middle, MIDDLE_LEN);
    std::memcpy(record.key + FIRST_LEN + MIDDLE_LEN, last, LAST_LEN);
    record.key[6] = '\0';
    return input;
}

void CountingSort(TVector<TRecord>& vec, const std::size_t digit) {
    TVector<TRecord> temp(vec);
    std::size_t count[DIGIT_SIZE];
    std::memset(count, 0, DIGIT_SIZE * sizeof(std::size_t));
    for (int i = 0; i < vec.Size(); ++i) {
        count[vec[i].key[digit]]++;
    }
    for (int i = 1; i < DIGIT_SIZE; ++i) {
        count[i] += count[i-1];
    }
    for (int i = temp.Size() - 1; i >= 0; --i) {
        vec[count[temp[i].key[digit]] - 1] = temp[i];
        count[temp[i].key[digit]]--;
    }
}

void RadixSort(TVector<TRecord>& vec) {
    if (vec.Size() <= 1) {
        return;
    }
    for (int digit = FIRST_LEN + MIDDLE_LEN + LAST_LEN - 1; digit >= 0; --digit) {
        CountingSort(vec, digit);
    }
}

void RadixDecorator(TVector<TRecord>& vec) {
    std::clock_t start = std::clock();
    RadixSort(vec);
    std::clock_t end = std::clock();
    std::cout << ((double) (end - start))/CLOCKS_PER_SEC << std::endl;
}

void StableDecorator(TVector<TRecord>& vec) {
    std::clock_t start = std::clock();
    std::stable_sort(vec.Begin(), vec.End());
    std::clock_t end = std::clock();
    std::cout << ((double) (end - start))/CLOCKS_PER_SEC << std::endl;
}

int main() {
    TVector<TRecord> vec;
    TRecord temp_record;
    while (std::cin >> temp_record) {
        vec.Push(temp_record);
    }
    //RadixDecorator(vec);
    //StableDecorator(vec);
    std::stable_sort(vec.Begin(), vec.End());
    for (int i = 0; i < vec.Size(); ++i) {
        std::cout << vec[i] << std::endl;
    }

    return 0;
}