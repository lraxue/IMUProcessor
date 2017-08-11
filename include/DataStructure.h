//
// Created by feixue on 17-8-11.
//

#ifndef IMUPROCESSOR_DATASTRUCTURE_H
#define IMUPROCESSOR_DATASTRUCTURE_H

#define PI 3.1415926535898

#include "ostream"
#include "istream"
#include "iostream"

struct Quaternion
{
    Quaternion() : x(0), y(0), z(0), w(1)
    {};

    Quaternion(const double _x, const double _y, const double _z, const double _w) : x(_x), y(_y), z(_z), w(_w)
    {}

    Quaternion(const Quaternion& q):x(q.x), y(q.y), z(q.z), w(q.w)
    {

    }

    void normalize()
    {
        double norm = std::sqrt(x * x + y * y + z * z + w * w);

        x /= norm;
        y /= norm;
        z /= norm;
        w /= norm;
    }

    double norm()
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Quaternion operator*(const Quaternion& q1)
    {
        Quaternion q;
        q.w = q1.w*w - q1.x*x - q1.y*y - q1.z*z;
        q.x = q1.w*x + q1.x*w + q1.y*z - q1.z*y;
        q.y = q1.w*y - q1.x*z + q1.y*w + q1.z*x;
        q.z = q1.w*z + q1.x*y - q1.y*x + q1.z*w;
        return q;
    }

//    ostream& operator<<(std::ostream& stream, const Quaternion& q)
//    {
//        std::cout << q.w << " " << q.x << "i " << q.y << "j " << q.z << "k";
//        // std::cout << noshowpos;
//    }

//    Quaternion operator*(const Quaternion& q1, const Quaternion& q2);


    double x;
    double y;
    double z;
    double w;
};


//Quaternion operator = (Quaternion q1)
//{
//    Quaternion q;
//    q.x = q1.x;
//    q.y = q1.y;
//    q.z = q1.z;
//    q.w = q1.w;
//}



struct Euler
{
    Euler():X(0), Y(0), Z(0){}
    Euler(const double _X, const double _Y, const double _Z):X(_X), Y(_Y), Z(_Z){}

    Euler(const Euler& euler): X(euler.X), Y(euler.Y), Z(euler.Z)
    {

    }

    double X;
    double Y;
    double Z;
};


#endif //IMUPROCESSOR_DATASTRUCTURE_H
