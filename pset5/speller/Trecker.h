//
// Created by oleg on 27.03.17.
//

#ifndef SPELLER_TRECKER_H
#define SPELLER_TRECKER_H

#include <sys/resource.h>
#include <sys/time.h>

#undef calculate
#undef getrusage


#include <cstdio>

class Trecker {
public:
    struct rusage before, after;

    double calculate(const struct rusage *b, const struct rusage *a)
    {
        if (b == NULL || a == NULL)
        {
            return 0.0;
        }
        else
        {
            return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                      (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                     ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                      (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                    / 1000000.0);
        }
    }
};


#endif //SPELLER_TRECKER_H
