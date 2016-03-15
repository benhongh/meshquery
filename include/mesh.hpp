#ifndef INCLUDED_MESH_HPP
#define INCLUDED_MESH_HPP

#include <vector>
#include <istream>
#include <tuple>
#include <functional>
#include <boost/optional.hpp>
#include <eigen3/Eigen/Dense>

namespace hongbin {
    
    /** 
     * A simple 3D mesh definition, consisting of a collection of vertices (Vec3)
     */
    struct Mesh {
        Mesh();
        
        int addVertex(const Eigen::Vector3d& vertex);
        int addVertex(double x, double y, double z);
        int addFace(int v1_index, int v2_index, int v3_index);
        
        const Eigen::Vector3d& getVertex(int vertexId) const;
        std::tuple<int, int, int> getFaceVertices(int faceId) const;
        
        int iterateVertices(std::function<void(const Eigen::Vector3d&, int)> vertexProc) const;
        int iterateFaces(int sharedVertex, std::function<void(const std::tuple<int, int, int>&, int)> faceProc) const;
        
    private:
        std::vector<Eigen::Vector3d> m_vertices;
        std::vector<std::tuple<int, int, int>> m_faces;
    };
}

#endif // include guard