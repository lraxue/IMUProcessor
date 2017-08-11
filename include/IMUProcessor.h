//
// Created by feixue on 17-8-11.
//

#ifndef IMUPROCESSOR_IMUPROCESSOR_H
#define IMUPROCESSOR_IMUPROCESSOR_H

#include "DataStructure.h"

#include <vector>

class IMUProcessor
{
public:
    IMUProcessor();
    ~IMUProcessor();

public:
    Euler Quaternion2Euler(const Quaternion& quaternion);
};

#endif //IMUPROCESSOR_IMUPROCESSOR_H
