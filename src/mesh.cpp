#include <string>
#include <sstream>
#include <regex>
#include "mesh.hpp"

namespace hongbin {
    
    Mesh::Mesh() {}
    
    Mesh::const_iterator Mesh::pointsBegin() const {
        return m_points.begin();
    }
    
    Mesh::const_iterator Mesh::pointsEnd() const {
        return m_points.end();
    }
    
    Mesh::iterator Mesh::pointsBegin() {
        return m_points.begin();
    }
    
    Mesh::iterator Mesh::pointsEnd() {
        return m_points.end();
    }
    
    void Mesh::addPoint(const Vec3& point) {
        m_points.push_back(point);
    }
}