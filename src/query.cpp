#include <cmath>
#include <vector>
#include <iostream>
#include "query.hpp"

namespace hongbin {
    using namespace Eigen;
    
    ClosestPointQuery::ClosestPointQuery(const Mesh& mesh):
        m_mesh(mesh){}
        
    boost::optional<int> findClosestVertex(const Mesh& mesh, const Vector3d& referencePoint, double maxDistance) {
        boost::optional<int> closestVertex = boost::none;
        double minSquaredNorm = 4 * maxDistance * maxDistance;
        
        mesh.iterateVertices([&](const Vector3d& vertex, int index){
             Vector3d diff = vertex - referencePoint;
             if (std::abs(diff[0]) <= maxDistance && std::abs(diff[1]) <= maxDistance && std::abs(diff[2]) <= maxDistance) {
                 double snorm = diff.squaredNorm();
                 if (snorm < minSquaredNorm) {
                     minSquaredNorm = snorm;
                     closestVertex = index;
                 }
             }
        });
        
        return closestVertex;
    }
    
    Vector3d unit(const Vector3d& v) {
        return v / v.norm();
    }
    
    boost::optional<Vector3d> getEdgeProjection(const Vector3d& referencePoint, const Vector3d& v1, const Vector3d& v2) {
        auto edgeUnit = unit(v2 - v1);
        auto projection = (referencePoint - v1).dot(edgeUnit);  // projection of RP along v1->v2
        auto edgeLength = (v2 - v1).norm();
        if (projection >= 0 && projection <= edgeLength) {
            Vector3d projectionPoint = v1 + projection * edgeUnit;
            return projectionPoint;
        }
        else {
            return boost::none;
        }
    }
    
    boost::optional<Vector3d> findClosestPointInFace(
        const Vector3d& referencePoint,
        const Vector3d& closestVertex,
        const Vector3d& v1, const Vector3d& v2, const Vector3d& v3) {
        
        auto edge12 = getEdgeProjection(referencePoint, v1, v2);
        auto edge23 = getEdgeProjection(referencePoint, v2, v3);
        auto edge31 = getEdgeProjection(referencePoint, v3, v1);
        
        // check for face projection
        if (edge12 != boost::none && edge23 != boost::none && edge31 != boost::none) {
            Vector3d normal     = unit((v2 - v1).cross(v3 - v1));
            double projection   = (referencePoint - v1).dot(normal);
            Vector3d projectionPoint = referencePoint - projection * normal;
            
            return projectionPoint;
        }
        
        // find best edge projection
        boost::optional<Vector3d> edges[3] = {edge12, edge23, edge31};
        double minSquaredDistance = (closestVertex - referencePoint).squaredNorm();
        boost::optional<Vector3d> closestPoint = boost::none;
        
        for (int i = 0; i < 3; ++i) {
            if (edges[i] != boost::none) {
                double squaredDistance = (edges[i].value() - referencePoint).squaredNorm();
                if (squaredDistance < minSquaredDistance) {
                    minSquaredDistance = squaredDistance;
                    closestPoint = edges[i];
                }
            }
        }
        
        if (closestPoint == boost::none) {
            return closestVertex;
        }
        else {
            return closestPoint;
        }
    }
        
    boost::optional<Vector3d> ClosestPointQuery::operator()(const Vector3d referencePoint, double maxDistance) {    
        auto closestVertexIndex = findClosestVertex(m_mesh, referencePoint, maxDistance);
        if (closestVertexIndex == boost::none) {
            return boost::none;
        }
        
        auto closestVertex = m_mesh.getVertex(closestVertexIndex.value());
        std::cout << "closest vertex " << closestVertex[0] << ", " << closestVertex[1] << ", " << closestVertex[2] << std::endl;
        
        boost::optional<Vector3d> closestPoint = boost::none;
        double minSquaredDistance = maxDistance * maxDistance;
        m_mesh.iterateFaces(closestVertexIndex.value(), [&](std::tuple<int, int, int> face, int faceIndex){
            auto v1 = m_mesh.getVertex(std::get<0>(face));
            auto v2 = m_mesh.getVertex(std::get<1>(face));
            auto v3 = m_mesh.getVertex(std::get<2>(face));
            
            auto test = findClosestPointInFace(referencePoint, closestVertex, v1, v2, v3);
            if (test != boost::none) {
                auto squaredDistance = (test.value() - referencePoint).squaredNorm();
                if (squaredDistance < minSquaredDistance){
                    minSquaredDistance = squaredDistance;
                    closestPoint = test;
                }
            } 
        });
        
        return closestPoint;
    }
}