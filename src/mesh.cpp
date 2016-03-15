#include <string>
#include <sstream>
#include <regex>
#include "mesh.hpp"

namespace hongbin {
    using namespace Eigen;
    
    Mesh::Mesh() {}
    
    int Mesh::addVertex(const Vector3d& vertex) {
        int index = m_vertices.size();
        m_vertices.push_back(vertex);
        
        return index;
    }
    
    int Mesh::addVertex(double x, double y, double z) {
        return addVertex(Vector3d{x, y, z});
    }
    
    int Mesh::addFace(int v1_index, int v2_index, int v3_index) {
        int index = m_faces.size();
        m_faces.push_back(std::make_tuple(v1_index, v2_index, v3_index));
        
        return index;
    }
    
    const Vector3d& Mesh::getVertex(int vertexId) const {
        return m_vertices[vertexId];
    }
    
    std::tuple<int, int, int> Mesh::getFaceVertices(int faceId) const {
        return m_faces[faceId];
    }
    
    int Mesh::iterateVertices(std::function<void(const Vector3d&, int)> vertexProc) const {
        int count = 0;
        int index = 0;
        for (auto vertex: m_vertices) {
            ++count;
            vertexProc(vertex, index);
            ++index;
        }
        
        return count;
    }
    
    int Mesh::iterateFaces(int sharedVertex, std::function<void(const std::tuple<int, int, int>&, int)> faceProc) const {
        using std::get;
        
        int count = 0;
        int index = 0;
        for (auto face: m_faces) {
            if (get<0>(face) == sharedVertex || get<1>(face) == sharedVertex || get<2>(face) == sharedVertex) {
                ++count;
                faceProc(face, index);
            }
            
            ++index;
        }
        
        return count;
    } 
}