/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: dybuk87
 *
 * Created on 8 listopada 2017, 17:57
 */

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix();
    void ident();
    double det() const;
    void invert(Matrix& destMatrix) const;
    void mulMatrix(Matrix& bM, Matrix& result) const;  // result = this * bM;
    void mul(double& x, double& y) const;
    double* getRaw() const;
private:
    double m[9];
};

void norm(double& x, double& y) ;
void rotate(double angle, double& x, double& y);

void createPerspectiveMatrix(Matrix& result, double lx, double rx, double fy, double ny);

#define M(x,y) (y * 3 + x)

#endif /* MATRIX_H */

