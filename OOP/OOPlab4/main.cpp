#include <iostream>
#include <tuple>
#include <utility>
#include <cmath>

#define COORD_NUM 4

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::pair<T, T>& other) {
    std::cout << "(" << other.first << "," << other.second << ")";
    return out;
}

template<typename T>
struct Square {
    std::pair<T, T> center_;
    std::pair<T, T> coord_[COORD_NUM];
    Square(std::pair<T, T> center, T h) {
        center_ = center;

        coord_[0].first = center_.first - h/2;
        coord_[0].second = center_.second + h/2;

        coord_[1].first = center_.first + h/2;
        coord_[1].second = center_.second + h/2;

        coord_[2].first = center_.first + h/2;
        coord_[2].second = center_.second - h/2;

        coord_[3].first = center_.first - h/2;
        coord_[3].second = center_.second - h/2;
    }
};

template<typename T>
struct Rectangle {
    std::pair<T, T> center_;
    std::pair<T, T> coord_[COORD_NUM];
    Rectangle(std::pair<T, T> center, T h, T wid) {
        center_ = center;

        coord_[0].first = center_.first - wid/2;
        coord_[0].second = center_.second + h/2;

        coord_[1].first = center_.first + wid/2;
        coord_[1].second = center_.second + h/2;

        coord_[2].first = center_.first + wid/2;
        coord_[2].second = center_.second - h/2;

        coord_[3].first = center_.first - wid/2;
        coord_[3].second = center_.second - h/2;
    }
};

template<typename T>
struct Trapezoid {
    std::pair<T, T> center_;
    std::pair<T, T> coord_[COORD_NUM];
    Trapezoid(std::pair<T, T> center, T bottom, T up, T h) {
        center_ = center;
        coord_[0].first = center_.first - up/2;
        coord_[0].second = center_.second + h/2;

        coord_[1].first = center_.first + up/2;
        coord_[1].second = center_.second + h/2;

        coord_[2].first = center_.first + bottom/2;
        coord_[2].second = center_.second - h/2;

        coord_[3].first = center_.first - bottom/2;
        coord_[3].second = center_.second - h/2;
    }
};

template<typename T>
double get_area(T& figure) {
    return std::abs((figure.coord_[0].first*figure.coord_[1].second + figure.coord_[1].first*figure.coord_[2].second + 
                     figure.coord_[2].first*figure.coord_[3].second + figure.coord_[3].first*figure.coord_[0].second) 
                    - 
                    (figure.coord_[1].first*figure.coord_[0].second + figure.coord_[2].first*figure.coord_[1].second + 
                     figure.coord_[3].first*figure.coord_[2].second + figure.coord_[0].first*figure.coord_[3].second))/2;
}

template <typename T, size_t index>
double square(T& tup) {
    auto figure = std::get<index>(tup);
    double res = get_area(figure);
    if constexpr ((index + 1) < std::tuple_size<T>::value) {
        return res + square<T, index + 1>(tup);
    }
    return res;
}

template<typename T>
void print(T& figure) {
    std::cout << figure.coord_[0] << figure.coord_[1] << figure.coord_[2] << figure.coord_[3] << std::endl;
}

template <typename T,size_t index> 
typename std::enable_if<index >= std::tuple_size<T>::value, void>::type 
printTuple(T& tuple){
    std::cout << std::endl;
}

template <typename T,size_t index>
typename std::enable_if<index < std::tuple_size<T>::value, void>::type 
printTuple(T& tuple){
    auto figure = std::get<index>(tuple);
    print(figure);
    printTuple<T, index + 1>(tuple);
}


std::tuple<Square<int>, Rectangle<int>, Trapezoid<int>, Square<double>, Rectangle<double>, Trapezoid<double>>
make_tuple() {
    std::pair<double, double> c1, c2, c3, c4, c5, c6;
    double h1;
    std::cin >> c1.first >> c1.second >> h1;

    double h2, wid2;
    std::cin >> c2.first >> c2.second >> h2 >> wid2;

    double bot3, up3, h3;
    std::cin >> c3.first >> c3.second >> bot3 >> up3 >> h3;

    double h4;
    std::cin >> c4.first >> c4.second >> h4;

    double h5, wid5;
    std::cin >> c5.first >> c5.second >> h5 >> wid5;

    double bot6, up6, h6;
    std::cin >> c6.first >> c6.second >> bot6 >> up6 >> h6;

    std::tuple<Square<int>, Rectangle<int>, Trapezoid<int>, Square<double>, Rectangle<double>, Trapezoid<double>> temp = 
    {Square<int>(c1, h1), Rectangle<int>(c2, h2, wid2), Trapezoid<int>(c3, bot3, up3, h3), 
    Square<double>(c4, h4), Rectangle<double>(c5, h5, wid5), Trapezoid<double>(c6, bot6, up6, h6)};
    return temp;
}

int main() {
    std::cout << "int:: square -> rectangle -> trapezoid -> double:: square -> rectangle -> trapezoid" << std::endl;
    std::tuple<Square<int>, Rectangle<int>, Trapezoid<int>, Square<double>, Rectangle<double>, Trapezoid<double>> tup = make_tuple();
    std::cout << "coordinates:" << std::endl;
    printTuple<decltype(tup), 0>(tup);
    std::cout << "total area:\n" << square<decltype(tup), 0>(tup) << std::endl;

    return 0;
}