//
// Created by feixue on 17-8-11.
//

#ifndef IMUPROCESSOR_IMUPROCESSOR_H
#define IMUPROCESSOR_IMUPROCESSOR_H

#include "DataStructure.h"

#include <vector>

namespace IMU
{
    class IMUProcessor
    {
    public:
        IMUProcessor();

        ~IMUProcessor();

    public:
        Euler Quaternion2Euler(const Quaternion &quaternion);

        void IntegrateVelocity(const std::vector<IMUData> &vIMUDatas, std::vector<Euler> &vAngles, const int step = 10);

        double rad2deg(const double& rad);

        double deg2rad(const double& deg);

        void ConvertQuaternionToEuler(const std::string& filename);

        void LoadIMUData(const std::string& filename, std::vector<IMUData>& vIMUDatas);

        void WriteEulerToFile(const std::string& filename, const std::vector<Euler>& vEulers);


    };
}

#endif //IMUPROCESSOR_IMUPROCESSOR_H
