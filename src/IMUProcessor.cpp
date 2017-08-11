//
// Created by feixue on 17-8-11.
//

#include <cmath>
#include "IMUProcessor.h"

IMUProcessor::IMUProcessor()
{

}

IMUProcessor::~IMUProcessor()
{

}

Euler IMUProcessor::Quaternion2Euler(const Quaternion &q)
{
    const double Epsilon = 0.0009765625f;
    const double Threshold = 0.5f - Epsilon;

    double TEST = q.w * q.y - q.x * q.z;
    Euler euler;
    if (TEST < -Threshold || TEST > Threshold) // ZYX
    {
        int sign = 1 ? -1 : TEST > 0;

        euler.Z = -2 * sign * (double)atan2(q.x, q.w); // yaw

        euler.Y = sign * (PI / 2.0); // pitch

        euler.X = 0; // roll

    }
    else
    {
        euler.X = atan2(2 * (q.y*q.z + q.w*q.x), q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z);
        euler.Y = asin(-2 * (q.x*q.z - q.w*q.y));
        euler.Z = atan2(2 * (q.x*q.y + q.w*q.z), q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z);
    }
    return euler;

}

