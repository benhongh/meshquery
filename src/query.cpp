#include <cmath>
#include "query.hpp"

namespace hongbin {
    
    namespace {
        inline double squareOf(double x) {
            return x * x;
        }
    }
    
    ClosestPointQuery::ClosestPointQuery(const Mesh& mesh):
        m_mesh(mesh){}
        
    Mesh::const_iterator ClosestPointQuery::operator()(const Vec3& queryPoint, double maxDistance) {
        auto maxDistanceSqr = maxDistance * maxDistance;
        auto minDistanceSqr = 2 * maxDistanceSqr;
        
        auto result = m_mesh.pointsEnd();
        
        for (auto pPoint = m_mesh.pointsBegin(); pPoint != m_mesh.pointsEnd(); ++pPoint) {
            auto point = *pPoint;
            auto diff = point - queryPoint;
            if (std::abs(diff.x()) <= maxDistance &&
                std::abs(diff.y()) <= maxDistance &&
                std::abs(diff.z()) <= maxDistance ) {
                 
                 auto distanceSqr = squareOf(diff.x()) + squareOf(diff.y()) + squareOf(diff.z());
                 if (distanceSqr <= minDistanceSqr) {
                     minDistanceSqr = distanceSqr;
                     result = pPoint;
                 }
            }
        }
        
        return result;
    }
    
}