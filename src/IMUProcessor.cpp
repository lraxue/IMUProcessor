//
// Created by feixue on 17-8-11.
//

#include <cmath>
#include <sstream>
#include <fstream>
#include "glog/logging.h"
#include "IMUProcessor.h"

using namespace std;
namespace IMU
{
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

            euler.Z = -2 * sign * (double) atan2(q.x, q.w); // yaw

            euler.Y = sign * (PI / 2.0); // pitch

            euler.X = 0; // roll

        } else
        {
            euler.X = atan2(2 * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
            euler.Y = asin(-2 * (q.x * q.z - q.w * q.y));
            euler.Z = atan2(2 * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z);
        }
        return euler;

    }

    void IMUProcessor::IntegrateVelocity(const std::vector<IMUData> &vIMUDatas, std::vector<Euler> &vAngles, const int step)
    {
        Euler Eulerprev = Euler(deg2rad(-0.424016), deg2rad(1.37811), deg2rad(-23.8609));
        vAngles.push_back(Eulerprev);

        IMUData IMUprev = vIMUDatas[0];

        for (int i = step, iend = vIMUDatas.size(); i < iend; ++i)
        {
            IMUData IMUcurr = vIMUDatas[i];
            const double dt =  IMUcurr.t - vIMUDatas[i - step].t;

            double meanvx = 0;
            double meanvy = 0;
            double meanvz = 0;

            for (int j = i - step; j < i; ++j)
            {
                meanvx += vIMUDatas[j].vx;
                meanvy += vIMUDatas[j].vy;
                meanvz += vIMUDatas[j].vz;
            }

            meanvx /= step;
            meanvy /= step;
            meanvz /= step;

            double dx = meanvx * dt;
            double dy = meanvy * dt;
            double dz = meanvz * dt;

            Euler Eulercurr(Eulerprev.X + dx, Eulerprev.Y + dy, Eulerprev.Z + dz);
            vAngles.push_back(Eulercurr);

            Eulerprev = Eulercurr;
            IMUprev = IMUcurr;
        }
    }

    double IMUProcessor::rad2deg(const double& rad)
    {
        return rad*180.0/M_PI;
    }

    double IMUProcessor::deg2rad(const double &deg)
    {
        return deg * M_PI / 180.0;
    }

    void IMUProcessor::ConvertQuaternionToEuler(const std::string& filename)
    {
        fstream file(filename.c_str());
        if (!file.is_open())
        {
            cout << "Open file " << filename << " error." << endl;
            return;
        }

        std::vector<Euler> vEulers;

        while (!file.eof())
        {
            string line;
            getline(file, line);

            stringstream ss;
            ss << line;

            float t, w, x, y, z;
            ss >> t >> w >> x >> y >> z;
            Quaternion quaternion(x, y, z, w);
            Euler euler = IMUProcessor::Quaternion2Euler(quaternion);

           LOG(INFO) << rad2deg(euler.X) << " " << rad2deg(euler.Y) << " " << rad2deg(euler.Z);

            vEulers.push_back(euler);
        }

        file.close();

        fstream fout("euler.txt", ios::out);
        for (auto& euler : vEulers)
        {
            fout << rad2deg(euler.X) << " " << rad2deg(euler.Y) << " " << rad2deg(euler.Z) << endl;
        }

        fout.close();

    }

    void IMUProcessor::LoadIMUData(const string& filename, std::vector<IMUData>& vIMUDatas)
    {
        fstream file(filename.c_str());
        if (!file.is_open())
        {
            cout << "Open file " << filename << " error." << endl;
            return;
        }

        vIMUDatas.clear();

        while (!file.eof())
        {
            string line;
            getline(file, line);

            stringstream ss;
            ss << line;

            double t, vx, vy, vz, ax, ay, az;
            ss >> t >> vx >> vy >> vz >> ax >> ay >> az;

            LOG(INFO) << "t: " << t << " vx: " << vx << " vy: " << vy << " vz: " << vz
                      << " ax: " << ax << " ay: " << ay << " az: " << az;

            IMUData data(t, vx, vy, vz, ax, ay, az);
            vIMUDatas.push_back(data);
        }

        file.close();
    }

    void IMUProcessor::WriteEulerToFile(const std::string &filename, const std::vector<Euler> &vEulers)
    {
        fstream file(filename.c_str(), ios::out);
        if (!file.is_open())
        {
            std::cout << "Open file " << filename << " error." << std::endl;
        }

        for (auto& euler : vEulers)
        {
            file << rad2deg(euler.X) << " " << rad2deg(euler.Y) << " " << rad2deg(euler.Z) << endl;

            LOG(INFO) << euler.X << " " << euler.Y << " " << euler.Z;
        }

        file.close();
    }
}



