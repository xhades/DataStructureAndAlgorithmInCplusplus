#ifndef __ACCELERATEDADD_HPP__
#define __ACCELERATEDADD_HPP__

int AcceleratedAdd(const int a, const int b) {
    return (a^b) + ((a&b) << 1);
}

#endif  /* __ACCELERATEDADD_HPP__ */

