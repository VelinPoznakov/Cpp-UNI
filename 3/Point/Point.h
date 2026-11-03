//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_POINT_H
#define INC_3_POINT_H


class Point {
    double x{};
    double y{};

public:
    Point(double x, double y);
    ~Point();

    double getX() const {return x;}
    double getY() const {return y;}

    void print() const;
    double dist(const Point &p1, const Point &p2) const;
};


#endif //INC_3_POINT_H
