#include <math.h>
#include "math2.h"
#include <stdlib.h>

float Cos(float angle) {
    return cos(angle * 0.0174532925);
}

float Sin(float angle) {
    return sin(angle * 0.0174532925);
}

float Rand(float min, float max) {
    return (((float)rand()/(float)RAND_MAX) * (max - min)) + min;
}

float DistSq(float x1, float y1, float x2, float y2) {
    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

float Dist(float x1, float y1, float x2, float y2) {
    return sqrt(DistSq(x1, y1, x2, y2));
}

float Atan2(float y, float x) {
    return atan2(y, x) / 0.0174532925;
}
