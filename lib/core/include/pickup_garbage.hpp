#pragma once

#include "config.hpp"
#include "claw.hpp"
#include "elbow.hpp"
#include "shoulder.hpp"
#include "base.hpp"

namespace oswaldo
{
    class pickup_garbage
    {
    public:
        pickup_garbage(shoulder sho, elbow elb, base bas, claw clw);

        void run();

    private:
        shoulder sho;
        elbow elb;
        base bas;
        claw clw;

        static void task_pickup_garbage(void *params);
    };
} // namespace oswaldo
