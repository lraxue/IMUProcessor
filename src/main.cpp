#include <iostream>
#include <cmath>

#include "IMUProcessor.h"

using std::cout;
using std::endl;

double rad2deg(const double& rad)
{
    return rad*180.0/M_PI;
}

int main()
{
    IMUProcessor processor;
    Quaternion q1(-0.005260, -0.005053, 0.002638, 0.999970);
    Quaternion q2(-0.004518, -0.004733, 0.035584, 0.999345);

    Euler euler1 = processor.Quaternion2Euler(q1);
    Euler euler2 = processor.Quaternion2Euler(q2);

    cout << euler1.X << " " << euler1.Y << " " << euler1.Z << endl;
    cout << euler2.X << " " << euler2.Y << " " << euler2.Z << endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}