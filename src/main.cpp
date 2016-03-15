#include <iostream>
#include <functional>

#include "mesh.hpp"
#include "query.hpp"
#include "line-parser.hpp"

int main(int argc, char* argv[]){
    using namespace hongbin;
    std::cout << "Enter one vertice per line, or # to finish" << std::endl;
    
    Mesh mesh{};
    parseLines(std::cin, [&](double x, double y, double z){
        mesh.addPoint(Vec3{x, y, z}); 
    });
    
    std::cout << "Enter one query point per line, or # to finish" << std::endl;
    auto query = ClosestPointQuery{mesh};
    parseLines(std::cin, [&](double x, double y, double z, double maxDistance){
        auto queryPoint = Vec3{x, y, z};
        auto closestPoint = query(queryPoint, maxDistance);
        
        if (closestPoint == mesh.pointsEnd()) {
            std::cout << "no closest point within max distance found" << std::endl;
        }
        else {
            const Vec3& result = *closestPoint;
            std::cout << result.x() << " " << result.y() << " " << result.z() << std::endl;
        }
    });
    return 0;
}