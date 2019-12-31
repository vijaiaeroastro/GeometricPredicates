#include "mesh.hpp"

namespace GeometricPredicates
{
    Mesh::Mesh(const std::string _input_mesh_name)
    {
        input_mesh_name = input_mesh_name;
    }

    Mesh::Mesh(GeometricPredicates::Mesh &input_mesh)
    {
        *this = input_mesh;
    }

    void Mesh::readMesh()
    {

    }

    void Mesh::writeMesh(const std::string _output_mesh_name)
    {
        output_mesh_name = _output_mesh_name;
    }

    void Mesh::readSTL()
    {

    }

    void Mesh::readOFF()
    {

    }

    void Mesh::readPLY()
    {

    }

    void Mesh::readSURF()
    {

    }

    void Mesh::readHSURF()
    {

    }

    void Mesh::readVOL()
    {

    }

    void Mesh::readHVOL()
    {

    }

    void Mesh::readCGNS()
    {

    }

    void Mesh::writeSTL()
    {

    }

    void Mesh::writeOFF()
    {

    }

    void Mesh::writePLY()
    {

    }

    void Mesh::writeSURF()
    {

    }

    void Mesh::writeHSURF()
    {

    }

    void Mesh::writeVOL()
    {

    }

    void Mesh::writeHVOL()
    {

    }

    void Mesh::writeCGNS()
    {

    }
}