#include <cmath>
#include "Vec3.hpp"

namespace hongbin {
    Vec3::Vec3(double x, double y, double z):
        m_x(x), m_y(y), m_z(z) {}
        
    Vec3::Vec3(const Vec3& v):
        m_x(v.x()), m_y(v.y()), m_z(v.z()) {}
        
    double Vec3::x() const {
        return m_x;
    }

    double Vec3::y() const {
        return m_y;
    }

    double Vec3::z() const {
        return m_z;
    }

    Vec3 operator+ (const Vec3& left, const Vec3& right) {
        return Vec3{
            left.x() + right.x(),
            left.y() + right.y(),
            left.z() + right.z()
        };
    }

    Vec3 operator- (const Vec3& left, const Vec3& right) {
        return Vec3 {
            left.x() - right.x(),
            left.y() - right.y(),
            left.z() - right.z()  
        };
    }
    
    Vec3 operator-(const Vec3& v) {
        return Vec3{
            -v.x(),
            -v.y(),
            -v.z()
        };
    }
}
