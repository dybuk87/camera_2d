/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.h
 * Author: dybuk87
 *
 * Created on 8 listopada 2017, 17:57
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"

class Camera {
public:
    void setPosition(double _posX, double _posY);
    void setLookAt(double _lookAtX, double _lookAtY);
    void setLookAtByAngle(double angle, double len);
    
    Matrix& getMatrix();
    Matrix& getIMatrix();
    
    double getPosX() const;
    double getPosY() const;
private:
    void calculateMatrix();
    
    double posX, posY;
    double lookAtX, lookAtY;
    
    Matrix matrix;
    Matrix imatrix;
};


#endif /* CAMERA_H */

