//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_RECTANGLE_H
#define INC_2_RECTANGLE_H

#include <string>


class Rectangle {
    double width{};
    double height{};

public:
    Rectangle(double width, double height);
    ~Rectangle();

    void setWidth(double width);
    void setHeight(double height);

    double getWidth() const {return width;}
    double getHeight() const {return height;}

    double face() const;
    double face(double *perimeter) const;

    void show(const std::string &name) const;
};


#endif //INC_2_RECTANGLE_H
