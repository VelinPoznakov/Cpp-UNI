#ifndef INC_1_LINE_H
#define INC_1_LINE_H

class Line {
    int Len;

    void draw() const;
    void erase() const;

public:
    explicit Line(int length);

    int getLen() const { return Len; }
};

#endif //INC_1_LINE_H