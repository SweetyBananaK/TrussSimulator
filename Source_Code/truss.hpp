#pragma once

#include <vector>
#include <Eigen/Dense>
#include <dco.hpp>
#include <string>


#include "utils.hpp"

class Joint;
class Edge;
class Force;
class TrussWidget;
class Parser_wrapper;

using DDM = Eigen::Matrix<dco::gt1s<double>::type, Utils::Dynamic, Utils::Dynamic>; // dynamic dco matrix
using DDV = Eigen::Matrix<dco::gt1s<double>::type, Utils::Dynamic, 1>; // dynamic dco vector
using DM = Eigen::Matrix<double, Utils::Dynamic, Utils::Dynamic>; // dynamic matrix
using DV = Eigen::Matrix<double, Utils::Dynamic, 1>; // dynamic vector

class Truss{

    public:
    Truss();
    Truss(std::string file_name);
    Truss(Truss* old_truss, Eigen::Matrix<double,Utils::Dynamic,1>);
    ~Truss();
    Parser_wrapper* my_parser;

    void save_truss(std::string file_name);
    void load_truss(std::string file_name);

    int addJoint(double px, double py, double psupport);
    void deleteJoint(int position);

    void addEdge(int locator1,int locator2,double thickness);

    int deleteEdge(int locator1,int locator2);

    int isEdge(int locator1, int locator2);
    bool isJoint(int locator1);


    void set_emodule(double e);

    bool hasForce(int locator);
    void addForce(double fx, double fy, int loc);
    void deleteForce(int position);

    void simulieren();

    Eigen::Matrix<double,Utils::Dynamic,1> calc_u(bool non_linear);

    std::vector<Joint* > v_joint_ptr;
    std::vector<Edge* > v_edge_ptr;
    std::vector<Force* > v_force_ptr;



    private:
    template<typename T>
    void assemble(Eigen::Matrix<T, Utils::Dynamic, Utils::Dynamic>& K,
                  Eigen::Matrix<T, Utils::Dynamic, 1>& u,
                  Eigen::Matrix<T, Utils::Dynamic, 1>& F);

    void solve_Newton(Eigen::Matrix<double,Utils::Dynamic,1>& u);
    void solve_linear(Eigen::Matrix<double,Utils::Dynamic,1>& u);

    Eigen::Matrix<double,2,2> calc_partial_K(Edge* edge_ptr, Eigen::Matrix<double,Utils::Dynamic,1>& u);

    Eigen::Matrix<dco::gt1s<double>::type,2,2> calc_partial_K(Edge* edge_ptr, Eigen::Matrix<dco::gt1s<double>::type,Utils::Dynamic,1>& u);


    void calc_aR(DV& R, DM& JR,const DV& u);

    double linear_emodule = 3000;

    const int default_reserved_joints = 100;
    const int default_reserved_edges = 500;
    const int default_reserved_forces = 40;
};
