#include <iostream>
#include <functional>
#include <regex>

#include "mesh.hpp"
#include "query.hpp"

int main(int argc, char* argv[]){
    using namespace hongbin;
    Mesh mesh{};
    ClosestPointQuery query{mesh};
    
    std::regex vertexPattern {R"(^V[\s]+([-]?[0-9]+(\.[0-9]+)?)[\s]+([-]?[0-9]+(\.[0-9]+)?)[\s]+([-]?[0-9]+(\.[0-9]+)?)([\s]*\#[\.]*)?$)"};
    std::regex facePattern   {R"(^F[\s]+([0-9]+)[\s]+([0-9]+)[\s]+([0-9]+)([\s]*\#[\.]*)?$)"};
    std::regex queryPattern  {R"(^Q[\s]+([-]?[0-9]+(\.[0-9]+)?)[\s]+([-]?[0-9]+(\.[0-9]+)?)[\s]+([-]?[0-9]+(\.[0-9]+)?)[\s]+([-]?[0-9]+(\.[0-9]+)?)([\s]*\#[\.]*)?$)"};

    while (std::cin){
        std::string line{};
        getline(std::cin, line);
        
        if (line == "END")
            break;
            
        std::smatch match;
        if (std::regex_match(line, match, vertexPattern)) {
            double x = std::stod(match[1]);
            double y = std::stod(match[3]);
            double z = std::stod(match[5]);
            mesh.addVertex(x, y, z);
        }
        else if (std::regex_match(line, match, facePattern)) {
            int v1 = std::stoi(match[1]);
            int v2 = std::stoi(match[2]);
            int v3 = std::stoi(match[3]);
            mesh.addFace(v1, v2, v3);
        }
        else if (std::regex_match(line, match, queryPattern)) {
            double x = std::stod(match[1]);
            double y = std::stod(match[3]);
            double z = std::stod(match[5]);
            double maxDistance = std::stod(match[7]);
            
            Eigen::Vector3d referencePoint{x, y, z};
            auto result = query(referencePoint, maxDistance);
            if (result == boost::none) {
                std::cout << "none" << std::endl;
            }
            else {
                auto closestPoint = result.value();
                std::cout << "(" << closestPoint[0] << "," << closestPoint[1] << "," << closestPoint[2] << ")" << std::endl;
            }
        }
        else if (line.size() > 0 && line[0] == '!') {
            std::cout << line << std::endl << std::endl;
        }
    }

    return 0;
}