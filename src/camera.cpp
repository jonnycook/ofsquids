#include "camera.h"

Camera::Camera() {
    y = 0;
}

Camera &Camera::GetInstance() {
    static Camera instance;
    return instance;
}
