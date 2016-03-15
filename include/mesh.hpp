#ifndef INCLUDED_MESH_HPP
#define INCLUDED_MESH_HPP

#include <vector>
#include <istream>
#include "vec3.hpp"

namespace hongbin {
    
    /** 
     * A simple 3D mesh definition, consisting of a collection of vertices (Vec3)
     */
    struct Mesh {
        Mesh();
        
        typedef std::vector<Vec3>::const_iterator const_iterator; ///< const iterator type for vertices
        const_iterator pointsBegin() const;                       ///< const iterator at the first vertex
        const_iterator pointsEnd() const;                         ///< const iterator at one past the last vertex
        
        typedef std::vector<Vec3>::iterator iterator;             ///< iterator type for vertices
        iterator pointsBegin();                                   ///< iterator at the frst vertex
        iterator pointsEnd();                                     ///< iterator at one past the last vertex
        
        //! Add a point (i.e. vertex) to the current mesh
        /*!
         \param point the vertex point to add to the mesh
        */
        void addPoint(const Vec3& point);
        
    private:
        std::vector<Vec3> m_points;
    };
    
}

#endif // include guard