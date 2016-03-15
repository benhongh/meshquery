#ifndef INCLUDED_QUERY_HPP
#define INCLUDED_QUERY_HPP

#include <boost/optional.hpp>
#include "mesh.hpp"

namespace hongbin {
    
    /**
     * A query to locate the closest vertex of a mesh in relation to any given point in space
     */
    struct ClosestPointQuery {
        ClosestPointQuery() = delete;
        ClosestPointQuery(const Mesh& mesh);   //! constructor a ClosestPointQuery based on a mesh
        
        //! invoke the ClosestPointQuery providing a reference point and a max distance
        /*!
            \param queryPoint the reference point
            \param maxDistance maximum search distance. Any vertex further than the max distance given from the reference point
                               is not considered in the query.
        */
        Mesh::const_iterator operator ()(const Vec3& queryPoint, double maxDistance);
        
    private:
        const Mesh& m_mesh;
    };
    
}

#endif // include guard