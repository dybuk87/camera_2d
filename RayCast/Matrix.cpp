/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.cpp
 * Author: dybuk87
 * 
 * Created on 8 listopada 2017, 17:57
 */

#include "Matrix.h"
#include <cmath>
#include <cstdio>

Matrix::Matrix() {
    ident();
}

void Matrix::ident() {
    m[0] = 1.0; m[1] = 0.0; m[2] = 0.0;
    m[3] = 0.0; m[4] = 1.0; m[5] = 0.0;
    m[6] = 0.0; m[7] = 0.0; m[8] = 1.0;
}


void norm(double& x, double& y) {
    double len = sqrt(x * x + y * y);
    if (len != 0.0) {
        x /= len;
        y /= len;
    }
}

void rotate(double angle, double& x, double& y) {
    
    printf("ROTATE: %5.2lf %5.2lf\n", x, y);
    
    double xo = x * cos(angle) - y * sin(angle);
    double yo = y * cos(angle) + x * sin(angle);
    
    x = xo;
    y = yo;
}

double Matrix::det() const {
    return + m[M(0,0)]  * m[M(1,1)] * m[M(2,2)]
            + m[M(1,0)]  * m[M(2,1)] * m[M(0,2)]
            + m[M(2,0)]  * m[M(0,1)] * m[M(1,2)]
            - m[M(2,0)]  * m[M(1,1)] * m[M(0,2)]
            - m[M(0,0)]  * m[M(2,1)] * m[M(1,2)]
            - m[M(1,0)]  * m[M(0,1)] * m[M(2,2)];
}

void Matrix::invert(Matrix& destMatrix) const {
    double *dest = destMatrix.m;
    dest[M(0,0)] = m[M(1,1)] * m[M(2,2)] - m[M(2,1)]  * m[M(1,2)]; 
    dest[M(1,0)] = m[M(2,0)] * m[M(1,2)] - m[M(1,0)]  * m[M(2,2)];   
    dest[M(2,0)] = m[M(1,0)] * m[M(2,1)] - m[M(2,0)]  * m[M(1,1)]; 
    
    dest[M(0,1)] = m[M(2,1)] * m[M(0,2)] - m[M(0,1)]  * m[M(2,2)];
    dest[M(1,1)] = m[M(0,0)] * m[M(2,2)] - m[M(2,0)]  * m[M(0,2)];
    dest[M(2,1)] = m[M(2,0)] * m[M(0,1)] - m[M(0,0)]  * m[M(2,1)];
    
    dest[M(0,2)] = m[M(0,1)] * m[M(1,2)] - m[M(1,1)]  * m[M(0,2)];
    dest[M(1,2)] = m[M(1,0)] * m[M(0,2)] - m[M(0,0)]  * m[M(1,2)];
    dest[M(2,2)] = m[M(0,0)] * m[M(1,1)] - m[M(1,0)]  * m[M(0,1)];
    
    double detA = det();
    
    if (detA == 0.0) {
        detA = 0.00001;
    }
    
    for(int i=0; i<9; i++) {
        dest[i] /= detA;
    }
}
// A * B
void Matrix::mulMatrix(Matrix& bM, Matrix& resultM) const {
    double *a = (double*)this->m;
    double *b = bM.m;
    double *result = resultM.m;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            double r = 0.0f;
            
            for(int k=0;k<3; k++) {
                r += a[M(k, y)] * b[M(x, k)];
            }
            
            result[M(x, y)] = r;
        }
    }
}

double* Matrix::getRaw() const {
    return (double*)m;
}

void Matrix::mul(double& x, double& y) const {
    double outX = x * m[0] + y * m[1] + m[2] * 1.0;
    double outY = x * m[3] + y * m[4] + m[5] * 1.0;
    double    w = x * m[6] + y * m[7] + m[8] * 1.0;
    
    x = outX/w;
    y = outY/w;
}
