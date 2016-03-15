#ifndef INCLUDED_VEC3_HPP
#define INCLUDED_VEC3_HPP

#include <iostream>

namespace hongbin {

    
    struct Vec3 {
        Vec3() = delete;
        Vec3(double x, double y, double z);
        Vec3(const Vec3& v);
        
        Vec3& operator=(const Vec3& v) = delete;
        
        double x() const;
        double y() const;
        double z() const;
        
    private:
        const double m_x;
        const double m_y;
        const double m_z;
    };

    Vec3 operator+ (const Vec3& left, const Vec3& right);
    Vec3 operator- (const Vec3& left, const Vec3& right);
    Vec3 operator- (const Vec3& v);
}

#endif // include guard