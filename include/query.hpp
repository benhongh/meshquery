#ifndef INCLUDED_QUERY_HPP
#define INCLUDED_QUERY_HPP

#include <boost/optional.hpp>
#include "mesh.hpp"

namespace hongbin {
    
    struct ClosestPointQuery {
        ClosestPointQuery() = delete;
        ClosestPointQuery(const Mesh& mesh);
        
        Mesh::const_iterator operator ()(const Vec3& queryPoint, double maxDistance);
        
    private:
        const Mesh& m_mesh;
    };
    
}

#endif // include guard