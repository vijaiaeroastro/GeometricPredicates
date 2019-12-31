#ifndef MESH_HPP
#define MESH_HPP
#include <iostream>
#include "GenericTypes.hpp"
#include "point.hpp"
#include "edge.hpp"
#include "plane.hpp"
#include "triangle.hpp"

namespace GeometricPredicates
{
    class Mesh
    {
        public:
            Mesh(const std::string _input_mesh_name);
            Mesh(Mesh &input_mesh);
            ~Mesh(){};

        public:
            enum MESH_FORMAT
            {
                STL = 100,
                OFF = 101,
                PLY = 102,
                SURF = 103,
                HSURF = 104,
                VOL = 105,
                HVOL = 106,
                CGNS = 107
            };

        public:
            void readMesh();

        private:
            void readSTL();
            void readOFF();
            void readPLY();
            void readSURF();
            void readHSURF();
            void readVOL();
            void readHVOL();
            void readCGNS();

        public:
            void writeMesh(const std::string _output_mesh_name);

        private:
            void writeSTL();
            void writeOFF();
            void writePLY();
            void writeSURF();
            void writeHSURF();
            void writeVOL();
            void writeHVOL();
            void writeCGNS();

        private:
            MESH_FORMAT determineFileFormat(const std::string file_name);

        private:
            std::string input_mesh_name, output_mesh_name;
            std::vector< Triangle > all_triangles;
    };
}

#endif