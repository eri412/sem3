#pragma once

#include <utility>
#include <cmath>
#include <iostream>

template<typename T>
struct Pentagon {
    std::pair<T, T> center;
    std::pair<T, T> coord[5];
    T area;
    Pentagon() {}
    Pentagon(std::pair<T, T> c, T a) {
        area = sqrt(25 + 10*sqrt(5))/4 * a * a;
        center = c;
        T R = a * sin((M_PI - 2*M_PI/5)/2)/sin(2*M_PI/5);

        coord[0].first = c.first;
        coord[0].second = c.second + R;

        coord[1].first = c.first + cos(M_PI/2 - 2*M_PI/5) * R;
        coord[1].second = c.second + sin(M_PI/2 - 2*M_PI/5) * R;

        coord[4].first = c.first - cos(M_PI/2 - 2*M_PI/5) * R;
        coord[4].second = c.second + sin(M_PI/2 - 2*M_PI/5) * R;

        coord[2].first = c.first + a/2;
        coord[2].second = c.second - R;

        coord[3].first = c.first - a/2;
        coord[3].second = c.second - R;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, Pentagon<T>& subj) {
    out << "coordinates: ";
    for (int i = 0; i < 5; ++i) {
        out << "(" << subj.coord[i].first << ";" << subj.coord[i].second << ") ";
    }
    out << std::endl;

    return out;
}
