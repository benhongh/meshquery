#ifndef INCLUDED_VEC3_HPP
#define INCLUDED_VEC3_HPP

#include <iostream>

namespace hongbin {

    /**
     * A simple 3D vector
     */
    struct Vec3 {
        Vec3() = delete;
        Vec3(double x, double y, double z);
        Vec3(const Vec3& v);
        
        Vec3& operator=(const Vec3& v) = delete;
        
        double x() const;  //! get the x component of the vector
        double y() const;  //! get the y component of the vector
        double z() const;  //! get the z component of the vector
        
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