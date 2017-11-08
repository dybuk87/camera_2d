/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dybuk87
 *
 * Created on 8 listopada 2017, 15:00
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "Matrix.h"
#include "Camera.h"

using namespace std;


double angle = -13.0f;
double angle_rad = angle * 3.14/180.0;

double camX = -6.0;
double camY = 3.0;

void createPerspectiveMatrix(Matrix& result, double l, double r, double n, double f) {
    double* m = result.getRaw();
    
    m[0] = -2.0 * n / (r - l);   
    m[1] = (r + l) / (r - l);
    m[2] = 0.0;
    
    m[3] = 0.0;
    m[4] = -(f + n) / (f - n);
    m[5] = 2 * f * n / (f - n);
    
    m[6] = 0.0;
    m[7] = -1.0;
    m[8] = 0.0;
    
}

void createViewPort(Matrix& result, double left, double right, int n, int f ) {
    double* m = result.getRaw();
   
    double w = (right - left) + 1;
    
    m[0] = w/2; m[1] = 0.0;     m[2] = left + w/2;
    m[3] = 0.0; m[4] = (f-n)/2; m[5] = (f+n)/2;
    m[6] = 0.0; m[7] = 0.0f; m[8] = 1.0;
 
}

void rayTest() {
    Camera camera;
    camera.setPosition(1.0, 1.0);
    camera.setLookAt(2.0, 2.0);
   
    
    Matrix perspective;
    Matrix viewport;
    
    createPerspectiveMatrix(perspective, -1.0, 1.0, 0.1, 1.0);
    createViewPort(viewport, 0, 639, 1, 100);
    
    Matrix all;
    Matrix pv;
 
    viewport.mulMatrix(perspective, pv);   
    pv.mulMatrix(camera.getMatrix(), all);
    
    
    Matrix iAll;
    all.invert(iAll);
    
    for(int x=0; x<640; x++) {
        double xx = x; double yy = 99;
        iAll.mul(xx, yy);
        
        printf("RAY: (%5.2lf, %5.2lf) -> (%5.2lf, %5.2lf)\n", camera.getPosX(), camera.getPosY(), xx, yy);
    }
   
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    Camera camera;
    camera.setPosition(camX, camY);
    camera.setLookAtByAngle(angle_rad, 6.0);
    
    double testX = 1.6;
    double testY = 3.4;
    
    double expectedX = (testX - camX);
    double expectedY = (testY - camY);
   
    rotate(angle_rad, expectedX, expectedY);
    
    camera.getMatrix().mul(testX, testY);
    
    printf("result   %5.2lf %5.2lf\n", testX, testY);
    printf("expected %5.2lf %5.2lf\n", expectedX, expectedY);
    
    camera.getIMatrix().mul(testX, testY);  
    printf("inverted %5.2lf %5.2lf\n", testX, testY);
    
    
    Matrix p;
    Matrix v;
    
    createPerspectiveMatrix(p, -4, 8, 7, 10);
    
    createViewPort(v, 0, 320,  1, 100);
    
    double xx = 11;
    double yy = 10;
    p.mul(xx, yy);
    printf("p %5.2lf %5.2lf\n", xx, yy);
    
    v.mul(xx, yy);
    printf("p %5.2lf %5.2lf\n", xx, yy);
    
    
    Matrix pv;
    v.mulMatrix(p, pv);
    
    double xx2 = 11;
    double yy2 = 10;
    pv.mul(xx2, yy2);
    
    printf("p %5.2lf %5.2lf\n", xx2, yy2);
    
    Matrix ipv;
    
    pv.invert(ipv);
    ipv.mul(xx2, yy2);
    
    printf("ip %5.2lf %5.2lf\n", xx2, yy2);
    
    rayTest();
    
    return 0;
}

