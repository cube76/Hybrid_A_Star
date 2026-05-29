// src/pybind_wrapper.cpp
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "hybrid_a_star/hybrid_a_star.h"

namespace py = pybind11;

PYBIND11_MODULE(hybrid_a_star_py, m) {
    m.doc() = "Python wrapper for Hybrid A* Planner";

    py::class_<HybridAStar>(m, "HybridAStar")
        // Bind the constructor
        .def(py::init<double, int, double, int, double, double, double, double, double, int>(),
             py::arg("steering_angle"), py::arg("steering_angle_discrete_num"),
             py::arg("segment_length"), py::arg("segment_length_discrete_num"),
             py::arg("wheel_base"), py::arg("steering_penalty"),
             py::arg("reversing_penalty"), py::arg("steering_change_penalty"),
             py::arg("shot_distance"), py::arg("grid_size_phi") = 72)
        
        // Bind core methods
        .def("Init", &HybridAStar::Init,
             py::arg("x_lower"), py::arg("x_upper"), py::arg("y_lower"), py::arg("y_upper"),
             py::arg("state_grid_resolution"), py::arg("map_grid_resolution") = 0.1)
        .def("Search", &HybridAStar::Search, 
             py::arg("start_state"), py::arg("goal_state"))
        .def("GetSearchedTree", &HybridAStar::GetSearchedTree)
        .def("GetPath", &HybridAStar::GetPath)
        .def("GetVisitedNodesNumber", &HybridAStar::GetVisitedNodesNumber)
        .def("GetPathLength", &HybridAStar::GetPathLength)
        
        // Bind overloaded SetObstacle methods using static_cast for C++11 compatibility
        .def("SetObstacle", 
             static_cast<void (HybridAStar::*)(double, double)>(&HybridAStar::SetObstacle),
             py::arg("pt_x"), py::arg("pt_y"))
        .def("SetObstacleGrid", 
             static_cast<void (HybridAStar::*)(unsigned int, unsigned int)>(&HybridAStar::SetObstacle),
             py::arg("x"), py::arg("y"))
             
        // Bind vehicle shape and reset
        .def("SetVehicleShape", &HybridAStar::SetVehicleShape,
             py::arg("length"), py::arg("width"), py::arg("rear_axle_dist"))
        .def("Reset", &HybridAStar::Reset);
}