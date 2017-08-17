#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

#include "IMUProcessor.h"


using namespace std;
using namespace IMU;



int main()
{
    IMUProcessor processor;
//    Quaternion q1(-0.005260, -0.005053, 0.002638, 0.999970);
//    Quaternion q2(-0.004518, -0.004733, 0.035584, 0.999345);
//
//
//
//    Euler euler1 = processor.Quaternion2Euler(q1);
//    Euler euler2 = processor.Quaternion2Euler(q2);
//
//    cout << euler1.X << " " << euler1.Y << " " << euler1.Z << endl;
//    cout << euler2.X << " " << euler2.Y << " " << euler2.Z << endl;
//
//    const std::string strQuaternionFile = "imu.txt";
//    processor.ConvertQuaternionToEuler(strQuaternionFile);

    const std::string strIMUData = "../data/t_v_a_auto_2016.txt";
    const std::string strEuler = "../data/euler_auto_2016.txt";
    std::vector<IMUData> mvIMUDatas;
    std::vector<Euler> mvEulers;

    processor.LoadIMUData(strIMUData, mvIMUDatas);
    processor.IntegrateVelocity(mvIMUDatas, mvEulers, 1);
    processor.WriteEulerToFile(strEuler, mvEulers);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}