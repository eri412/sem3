#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <vector>
#include <limits>
#include <ios>

#define SQUARE 1
#define RECTANGLE 2
#define TRAPEZOID 3
#define COORD_NUM 4

std::ostream& operator<<(std::ostream& out, const std::pair<float, float>& other) {
    std::cout << "(" << other.first << "," << other.second << ")";
    return out;
}

class Figure {
public:
    float get_area() {
        return std::abs((coord_[0].first*coord_[1].second + coord_[1].first*coord_[2].second + coord_[2].first*coord_[3].second + coord_[3].first*coord_[0].second) - 
                        (coord_[1].first*coord_[0].second + coord_[2].first*coord_[1].second + coord_[3].first*coord_[2].second + coord_[0].first*coord_[3].second))/2;
    }
    std::pair<float, float> get_center() {
        return center_;
    }
    void print_coord() {
        std::cout << coord_[0] << coord_[1] << coord_[2] << coord_[3];
    }
protected:
    virtual void get_coord(){}
protected:
    std::pair<float, float> center_;
    std::pair<float, float> coord_[COORD_NUM];
};

class Square : public Figure {
public:
    Square(std::pair<float, float> center, float h) {
        center_ = center;
        h_ = h;
        get_coord();
    }
protected:
    void get_coord() override {
        coord_[0].first = center_.first - h_/2;
        coord_[0].second = center_.second + h_/2;

        coord_[1].first = center_.first + h_/2;
        coord_[1].second = center_.second + h_/2;

        coord_[2].first = center_.first + h_/2;
        coord_[2].second = center_.second - h_/2;

        coord_[3].first = center_.first - h_/2;
        coord_[3].second = center_.second - h_/2;
    }
private:
    float h_;
};

class Rectangle : public Figure {
public:
    Rectangle(std::pair<float, float> center, float h, float wid) {
        center_ = center;
        h_ = h;
        wid_ = wid;
        get_coord();
    }
protected:
    void get_coord() override {
        coord_[0].first = center_.first - wid_/2;
        coord_[0].second = center_.second + h_/2;

        coord_[1].first = center_.first + wid_/2;
        coord_[1].second = center_.second + h_/2;

        coord_[2].first = center_.first + wid_/2;
        coord_[2].second = center_.second - h_/2;

        coord_[3].first = center_.first - wid_/2;
        coord_[3].second = center_.second - h_/2;
    }
private:
    float h_;
    float wid_;
};

class Trapezoid : public Figure {
public:
    Trapezoid(std::pair<float, float> center, float bottom, float up, float h) {
        center_ = center;
        bottom_ = bottom;
        up_ = up;
        h_ = h;
        get_coord();
    }
protected:
    void get_coord() override {
        coord_[0].first = center_.first - up_/2;
        coord_[0].second = center_.second + h_/2;

        coord_[1].first = center_.first + up_/2;
        coord_[1].second = center_.second + h_/2;

        coord_[2].first = center_.first + bottom_/2;
        coord_[2].second = center_.second - h_/2;

        coord_[3].first = center_.first - bottom_/2;
        coord_[3].second = center_.second - h_/2;
    }
private:
    float bottom_;
    float up_;
    float h_;
};

int main() {
    int type;
    std::vector<Figure> vec;
    while (true) {
        std::cin >> type;
        if (std::cin.eof()) {
            break;
        }
        if (type == SQUARE) {
            std::pair<float, float> center;
            float h;
            std::cin >> center.first >> center.second >> h;
            if (std::cin.fail() || h <= 0) {
                std::cout << "bad input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Square temp(center, h);
            vec.push_back(temp);
            std::cout << "type: square" << '\n' << "area: " << temp.get_area() << '\n' << "center: " << temp.get_center() << '\n' << "coordinates: ";
            temp.print_coord();
            std::cout << std::endl;        
        }
        else if (type == RECTANGLE) {
            std::pair<float, float> center;
            float h;
            float wid;
            std::cin >> center.first >> center.second >> h >> wid;
            if (std::cin.fail() || h <= 0 || wid <= 0) {
                std::cout << "bad input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Rectangle temp(center, h, wid);
            vec.push_back(temp);
            std::cout << "type: rectangle" << '\n' << "area: " << temp.get_area() << '\n' << "center: " << temp.get_center() << '\n' << "coordinates: ";
            temp.print_coord();
            std::cout << std::endl;   
        }
        else if (type == TRAPEZOID) {
            std::pair<float, float> center;
            float bottom;
            float up;
            float h;
            std::cin >> center.first >> center.second >> bottom >> up >> h;
            if (std::cin.fail() || bottom <= 0 || up <= 0 || h <= 0) {
                std::cout << "bad input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Trapezoid temp(center, bottom, up, h);
            vec.push_back(temp);
            std::cout << "type: trapezoid" << '\n' << "area: " << temp.get_area() << '\n' << "center: " << temp.get_center() << '\n' << "coordinates: ";
            temp.print_coord();
            std::cout << std::endl;
        }
        else {
            std::cout << "No such type!" << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    float total_area = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        total_area += vec[i].get_area();
    }
    std::cout << "total area: " << total_area << std::endl;
    return 0;
}