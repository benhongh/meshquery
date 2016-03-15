#ifndef INCLUDED_MESH_HPP
#define INCLUDED_MESH_HPP

#include <vector>
#include <istream>
#include "vec3.hpp"

namespace hongbin {
    
    /** 
     * A simple 3D mesh definition, consisting of a collection of points (Vec3)
     */
    struct Mesh {
        Mesh();
        
        typedef std::vector<Vec3>::const_iterator const_iterator;
        const_iterator pointsBegin() const;
        const_iterator pointsEnd() const;
        
        typedef std::vector<Vec3>::iterator iterator;
        iterator pointsBegin();
        iterator pointsEnd();
        
        void addPoint(const Vec3& point);
        
    private:
        std::vector<Vec3> m_points;
    };
    
}

#endif // include guard