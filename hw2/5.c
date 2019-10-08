#include <stdio.h>
#include <math.h>

typedef struct point Point;
typedef struct triangle Triangle;

struct point{
    int x, y;
};

struct triangle{
    Point p1;
    Point p2;
    Point p3;
    double area;
};

double dist(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double mk_area(Triangle trgl) {
    double line_1 = dist(trgl.p1, trgl.p2);
    double line_2 = dist(trgl.p1, trgl.p3);
    double line_3 = dist(trgl.p2, trgl.p3);
    double per = (line_1 + line_2 + line_3) / 2;
    return sqrt(per * (per - line_1) * (per - line_2) * (per - line_3));
}

Triangle create(Point a, Point b, Point c) {
    Triangle t;
    t.p1 = a;
    t.p2 = b;
    t.p3 = c;
    t.area = mk_area(t);
    return t;
}

int main(void) {
    Point a, b, c, d;
    double sum;
    scanf("%d %d %d %d %d %d %d %d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
    Triangle trgl_0 = create(a, b, c);
    Triangle trgl_1 = create(d, a, b);
    Triangle trgl_2 = create(d, b, c);
    Triangle trgl_3 = create(d, a, c);
    sum = trgl_1.area + trgl_2.area + trgl_3.area;
    if (trgl_0.area > sum || (trgl_1.area && trgl_2.area && trgl_3.area && sum == trgl_0.area)) {
        printf("YES\n");
    } else{
        printf("NO\n");
    }
    return 0;
}
