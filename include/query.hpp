#ifndef INCLUDED_QUERY_HPP
#define INCLUDED_QUERY_HPP

#include <boost/optional.hpp>
#include <eigen3/Eigen/Dense>
#include "mesh.hpp"

namespace hongbin {
    
    /**
     * A query to locate the closest vertex of a mesh in relation to any given point in space
     */
    struct ClosestPointQuery {
        ClosestPointQuery() = delete;
        ClosestPointQuery(const Mesh& mesh);   //! constructor a ClosestPointQuery based on a mesh
        
        boost::optional<Eigen::Vector3d> operator()(const Eigen::Vector3d referencePoint, double maxDistance);
        
    private:
        const Mesh& m_mesh;
    };
    
}

#endif // include guard