/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.cpp
 * Author: dybuk87 
 * 
 * Created on 8 listopada 2017, 17:57
 */

#include "Camera.h"
#include "Matrix.h"
#include <cmath>
#include <cstdio>

void Camera::setPosition(double _posX, double _posY) {
    this->posX = _posX;
    this->posY = _posY;
}

void Camera::setLookAt(double _lookAtX, double _lookAtY) {
    this->lookAtX = _lookAtX;
    this->lookAtY = _lookAtY;
    calculateMatrix();
}

void Camera::setLookAtByAngle(double angle, double len) {
    this->lookAtX = posX + len * sin(angle);
    this->lookAtY = posY + len * cos(angle);
    
    printf("look at : %5.2lf %5.2lf\n", lookAtX, lookAtY);
    
    calculateMatrix();
}

double Camera::getPosX() const {
    return posX;
}
    
double Camera::getPosY() const {
    return posY;
}

void Camera::calculateMatrix() {
    double camRayX = (this->lookAtX - this->posX);
    double camRayY = (this->lookAtY - this->posY);
    norm(camRayX, camRayY);
   
    double camOX_x =  camRayY;
    double camOX_y =  -camRayX;
    
    
    printf("cam %5.2lf %5.2lf\n", camRayX, camRayY);
    printf("cam %5.2lf %5.2lf\n", camOX_x, camOX_y);
    
    double shiftX = -this->posX;
    double shiftY = -this->posY;
    
    double *m = matrix.getRaw();
    
    m[0] = camOX_x;      m[3] = camRayX;      m[2] = 0.0;
    m[1] = camOX_y;      m[4] = camRayY;      m[5] = 0.0;
    m[6] = 0.0;          m[7] = 0.0;          m[8] = 1.0;
    
    matrix.mul(shiftX, shiftY);
    
    m[2] = shiftX;
    m[5] = shiftY;
    
    matrix.invert(imatrix);
}

   Matrix& Camera::getMatrix() {
       return matrix;
   }
   
    Matrix& Camera::getIMatrix() {
        return imatrix;
    }
