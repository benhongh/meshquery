#include <iostream>
#include <functional>

#include "mesh.hpp"
#include "query.hpp"
#include "line-parser.hpp"

int main(int argc, char* argv[]){
    using namespace hongbin;
    Mesh mesh{};
    mesh.addVertex(-1, -1, 0);
    mesh.addVertex(1, -1, 0);
    mesh.addVertex(0, 1, 0);
    mesh.addFace(0, 1, 2);
    
    ClosestPointQuery query{mesh};
    auto result = query(Eigen::Vector3d{1, 0, 1}, 2);
    if (result != boost::none) {
        std::cout << result.value() << std::endl;
    }
    return 0;
}