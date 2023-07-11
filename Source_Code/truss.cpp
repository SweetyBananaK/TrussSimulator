#include "truss.hpp"
#include "joint.hpp"
#include "edge.hpp"
#include "force.hpp"
#include "trusswidget.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include <QDebug>

#define DCO_NO_INTERMEDIATES

//TODOOOOOOooooo beim loeschen von Joints muessen alle DARAUFFOLGENDEN locator um 1 verringert werden

//Konstruktor fuer neues Truss
Truss::Truss()
{
    v_joint_ptr.reserve(default_reserved_joints);
    v_edge_ptr.reserve(default_reserved_edges);
    v_force_ptr.reserve(default_reserved_forces);
    my_parser = new Parser_wrapper;
}

//Konstruktor fuer vorhandenes Truss aus Datei
Truss::Truss(std::string file_name)
{
    v_joint_ptr.reserve(default_reserved_joints);
    v_edge_ptr.reserve(default_reserved_edges);
    v_force_ptr.reserve(default_reserved_forces);
    my_parser = new Parser_wrapper;

    load_truss(file_name);
}

Truss::~Truss(){

    int n_joints = v_joint_ptr.size(), n_edges = v_edge_ptr.size(), n_forces = v_force_ptr.size();

    for(int i = 0; i < n_edges;i++){
        delete v_edge_ptr[i];
    }

    for(int i = 0; i < n_forces ; i++){
        delete v_force_ptr[i];
    }


    for(int i = 0; i < n_joints;i++){
          delete v_joint_ptr[i];
    }

    delete my_parser;

}

    //Prueft ob auf Knoten mit KnotenNr. = locator eine Kraft wirkt.
bool Truss::hasForce(int locator){
    int n_forces = v_force_ptr.size();

    for(int i = 0; i < n_forces; i++){
        if(locator == v_force_ptr[i]->get_joint_ptr()->get_locator()){
            return true;
        }
    }
    return false;

}

    //Konstruktor zum erzeugen eines Tragwerks mit Verschiebungsvektor u
Truss::Truss(Truss* old_truss, Eigen::Matrix<double,Utils::Dynamic,1> u)
{
    int n_joints = old_truss->v_joint_ptr.size();
    int n_edges = old_truss->v_edge_ptr.size();
    v_joint_ptr.reserve(n_joints);
    v_edge_ptr.reserve(n_edges);
    my_parser = new Parser_wrapper;

    //Erstellung der Knoten aus old_truss mit Verschiebung u
    for(int i = 0; i < n_joints;i++){
        double x, y, support;
        x = old_truss->v_joint_ptr[i]->x() + u(2*i);
        y = old_truss->v_joint_ptr[i]->y() + u(2*i + 1);
        support = old_truss->v_joint_ptr[i]->get_support();
        Joint * new_joint = new Joint(i, x, y, support);
       v_joint_ptr.push_back(new_joint);
    }

    //Kanten werden von old_truss uebernommen und neu ausgerichtet
    for(int i = 0; i < n_edges;i++){
        int joint_index1 = old_truss->v_edge_ptr[i]->get_joint_ptr1()->get_locator();
        int joint_index2 = old_truss->v_edge_ptr[i]->get_joint_ptr2()->get_locator();
        double edge_thickness = old_truss->v_edge_ptr[i]->get_thickness();
        Edge* new_edge = new Edge(v_joint_ptr[joint_index1], v_joint_ptr[joint_index2], edge_thickness);
        v_edge_ptr.push_back(new_edge);
    }
}

    //Knoten ,Kanten und Kraefte aus file_name laden
void Truss::load_truss(std::string file_name){

    ifstream load_stream;
    load_stream.open(file_name); //hier HOME andert //"/home/stce/Software/truss-simulator-qt-creator/" +

    //Liest: #Knoten #Kannten #Kraefte
    int n_joints, n_edges, n_forces;
    load_stream >> n_joints >> n_edges >> n_forces;
    v_joint_ptr.clear();
    v_edge_ptr.clear();
    v_force_ptr.clear();

    //Liest #Knoten mal: "x-Koordinate" "y-Koordinate" "Gelenktyp"
    for(int i = 0; i < n_joints;i++){
         double x, y, support;
         load_stream >> x >> y >> support;
        Joint * new_joint = new Joint(i, x, y, support);
        v_joint_ptr.push_back(new_joint); //v_joint_ptr.push_back(new_joint) v_joint_ptr[i] = new_joint
     }

    //Liest #Kanten mal: "KnotenNr.1" "KnotenNr.2" "Kantendicke"
    int joint_index1, joint_index2;
    double edge_thickness;
    for(int i = 0; i < n_edges;i++){
        load_stream >> joint_index1 >> joint_index2 >> edge_thickness;
        Edge* new_edge = new Edge(v_joint_ptr[joint_index1], v_joint_ptr[joint_index2], edge_thickness);
        v_edge_ptr.push_back(new_edge); //v_edge_ptr.push_back(new_edge) v_edge_ptr[i] = new_edge
     }

    //Liest #Kraefte mal: "KnotenNr." "x-Kraft" "y-Kraft"
    int joint_index;
    double xforce, yforce;
    for(int i = 0; i < n_forces;i++){
        load_stream >> joint_index >> xforce >> yforce;
        Force* new_force = new Force(v_joint_ptr[joint_index],xforce,yforce);
        v_force_ptr.push_back(new_force); //v_force_ptr.push_back(new_force);v_force_ptr[i] = new_force
    }

    load_stream.close();
}

    //Knoten ,Kanten und Kraefte in file_neme speichern
void Truss::save_truss(std::string file_name){

    ofstream save_stream;
    save_stream.open(file_name); //getenv(“HOME”)  "/home/stce/Software/truss-simulator-qt-creator/" +

    //Schreibt: "#Knoten" "#Kanten" "#Kraefte" \n
    int n_joints = v_joint_ptr.size(), n_edges = v_edge_ptr.size(), n_forces = v_force_ptr.size();
    save_stream << n_joints << " " << n_edges << " " << n_forces << "\n";

    //Schreibt fuer jeden Knoten: "x_Koordinate" "y_Koordinate" "Gelenktyp"\n
    for(int i = 0; i < n_joints;i++){
        save_stream << v_joint_ptr[i]->x() << " " << v_joint_ptr[i]->y() << " " << v_joint_ptr[i]->get_support() << "\n";
    }

    //Schreibt fuer jede Kante: "KnotenNr.1" "KnotenNr.2" "Dicke"\n
    for(int i = 0; i < n_edges;i++){
        int joint_index1 = v_edge_ptr[i]->get_joint_ptr1()->get_locator();
        int joint_index2 = v_edge_ptr[i]->get_joint_ptr2()->get_locator();
        double edge_thickness = v_edge_ptr[i]->get_thickness();
        save_stream << joint_index1 << " " << joint_index2 << " " << edge_thickness << "\n";
    }

    //Schreibt fuer jede Kraft: "KnotenNr." "x-Kraft" "y-Kraft"\n
    for(int i = 0; i < n_forces ; i++){
        int joint_index = v_force_ptr[i]->get_joint_ptr()->get_locator();
        double xforce  = v_force_ptr[i]->get_xforce();
        double yforce  = v_force_ptr[i]->get_yforce();
        save_stream << joint_index << " " << xforce << " " << yforce << "\n";
    }

    save_stream.close();
}

    //Fuegt v_joint_ptr ein neuen Knoten mit KnotenNr. = #Knoten+1 hinzu
int Truss::addJoint(double px, double py, double psupport) {

    int position = v_joint_ptr.size();

    Joint * new_joint = new Joint(position, px, py, psupport);
    v_joint_ptr.push_back(new_joint);
    return position;
}

    //Loescht Knoten mit KnotenNr. = position aus v_joint_ptr. Alle KnotenNr. > position => KnotenNr. = KnotenNr. -1 (ruecken auf)
void Truss::deleteJoint(int position) {

    delete v_joint_ptr[position];
    v_joint_ptr.erase(v_joint_ptr.begin()+position);
    int n_joints = v_joint_ptr.size();
    for(int i = position; i < n_joints; i++){
        v_joint_ptr[i]->set_locator(i);
        v_joint_ptr[i]->update();
    }
}

    //ruft entweder solve_linear(lineares System) oder solve_Newton(nichtlineares System) auf. Verschiebungsvektor u wird zurueckgegeben
Eigen::Matrix<double,Utils::Dynamic,1> Truss::calc_u(bool non_linear){

    Eigen::Matrix<double,Utils::Dynamic,1> u(v_joint_ptr.size()*2);

    if(non_linear){
        solve_Newton(u);
    }
    else{solve_linear(u);
    }
    std::cout << u << std::endl;
    return u;
}

    //Fuegt v_edge_ptr eine neue Kante hinzu
void Truss::addEdge(int locator1,int locator2,double thickness) {

    Edge* new_edge = new Edge(v_joint_ptr[locator1], v_joint_ptr[locator2], thickness);
    v_edge_ptr.push_back(new_edge);
}

    /*
    DDV:    Dynamic DCO Vektor
    DDM:    Dynamic DCO Matrix
    DV:     Dynamic Vektor  (lineares System)
    DM:     Dynamic Matrix  (lineares System)
    R:      Residuum
    JR:     Jacobimatrix von R
    K:      Steifigkeitsmatrix
    u:      Verschiebungsvektor
    F:      Kraefte
    */
    //Berechnet das Residuum R und die dazugehörige Jacobimatrix JR
void Truss::calc_aR( DV& V_R, DM& JR, const DV& V_u){

    int v_size = V_u.size();
    DDM K = DDM::Zero(v_size,v_size);
    DDV F = DDV::Zero(v_size,1);
    DDV u = DDM::Zero(v_size,1);
    DDV R = DDM::Zero(v_size,1);

    DM test_k = DM::Zero(v_size,v_size);

    for(int i=0;i<v_size;i++){
      dco::value(u(i)) = V_u(i);
      }


    for(int i = 0; i < v_size; i++)
      {

        dco::derivative(u(i)) = 1.0;
        assemble<dco::gt1s<double>::type >(K,u,F);
        R = K*u-F;

        //Eine Spalte in der Jacobimatrix
        for(int j=0; j < v_size; j++){
            JR(j,i) = dco::derivative(R(j));
          }

        dco::derivative(u(i)) = 0;

        for(int m=0;m<v_size;m++){
            for(int n=0;n<v_size;n++){
              test_k(m,n) = dco::value(K(m,n)) ;
              }
          }
        //if(i==1){std::cout << "This is nonlinear K: \n" << test_k << std::endl;}

        K = DDM::Zero(v_size,v_size);
      }

    //Update R
    for(int i=0;i<v_size;i++){
      V_R(i) = dco::value(R(i));
      }
    //std::cout << "This is JR: \n" << JR << std::endl;

}

    //Newton-Verfahren
void Truss::solve_Newton(Eigen::Matrix<double,Utils::Dynamic,1>& u){

  int v_size = u.size();
  u = DM::Zero(v_size,1);
  DV delta_u = DV::Zero(v_size,1);
  DV R= DV::Zero(v_size,1);
  DM JR= DM::Zero(v_size,v_size);
  double norm = 0;

  do{
      calc_aR(R,JR,u);

      delta_u = JR.householderQr().solve(-R);
      norm = delta_u.norm();
      u += delta_u;

      std::cout << norm << std::endl;
  } while(norm > Utils::newton_tol);
      std::cout << "CONVERGED" << std::endl;
}

void Truss::solve_linear(Eigen::Matrix<double,Utils::Dynamic,1>& u){

    int n_joints = v_joint_ptr.size();

    DM K = DM::Zero(2*n_joints,2*n_joints);
    u = DV::Zero(2*n_joints,1);
    DV F = DV::Zero(2*n_joints,1);

    assemble<double>(K,u,F);
    std::cout << K << std::endl;
    u = K.llt().solve(F);
    //std::cout << "solution: " << u << std::endl;
}

template<typename T>
void Truss::assemble(
    Eigen::Matrix<T, Utils::Dynamic, Utils::Dynamic>& K,
    Eigen::Matrix<T, Utils::Dynamic, 1>& u,
    Eigen::Matrix<T, Utils::Dynamic, 1>& F)
{
    using DM = Eigen::Matrix<T, Utils::Dynamic, Utils::Dynamic>; // dynamic matrix
    using DV = Eigen::Matrix<T, Utils::Dynamic, 1>; // dynamic vector

    int n_joints = v_joint_ptr.size();
    int n_edges = v_edge_ptr.size();
    int n_forces = v_force_ptr.size();

    //System-Matrix ohne Kraefte und Lager
    for(int i=0;i<n_edges;i++){
        Eigen::Matrix<T,2,2> partial_K = calc_partial_K(v_edge_ptr[i],u);
        int index1 = v_edge_ptr[i]->get_joint_ptr1()->get_locator();
        int index2 = v_edge_ptr[i]->get_joint_ptr2()->get_locator();
        K.block(2*index1,2*index1,2,2) += partial_K;
        K.block(2*index1,2*index2,2,2) -= partial_K;
        K.block(2*index2,2*index1,2,2) -= partial_K;
        K.block(2*index2,2*index2,2,2) += partial_K;
    }

    //Kraefte (muessen vor Lagern kommen)
    for(int i = 0; i < n_forces;i++){
            int joint_index = v_force_ptr[i]->get_joint_ptr()->get_locator();
            F(2*joint_index)   = v_force_ptr[i]->get_xforce();
            F(2*joint_index+1) = v_force_ptr[i]->get_yforce();
    }

    //Lager (Kein Lager: support=-1, Festes Lager: support=-2, Loses Lager: support=Winkel des Lagers))
    for(int i=0;i<n_joints;i++){
        double support = v_joint_ptr[i]->get_support();

        if(support != -1){
            if(support == -2){
                K.block(2*i,2*i,2,2) = Eigen::Matrix<T,2,2>::Identity();
                K.block(0,2*i,2*i,2) = DM::Zero(2*i,2);
                K.block(2*(i+1),2*i,2*(n_joints-i-1),2) = DM::Zero(2*(n_joints-i-1),2);
                K.block(2*i,0,2,2*i) = DM::Zero(2,2*i);
                K.block(2*i,2*(i+1),2,2*(n_joints-i-1)) = DM::Zero(2,2*(n_joints-i-1));

                F(2*i) = 0.0;
                F(2*i+1) = 0.0;
            }
        }
    }
}


Eigen::Matrix<double,2,2> Truss::calc_partial_K(Edge* edge_ptr, Eigen::Matrix<double,Utils::Dynamic,1>& u){
    double x1,x2,y1,y2,L,b,h,A,E,coeff; //l=kantenlaenge, b=breite, h=hoehe
    x1 = edge_ptr->get_joint_ptr1()->x();
    x2 = edge_ptr->get_joint_ptr2()->x();
    y1 = edge_ptr->get_joint_ptr1()->y();
    y2 = edge_ptr->get_joint_ptr2()->y();
    A  = edge_ptr->get_thickness();

    L = sqrt( pow(x1-x2,2) + pow(y1-y2,2));
    b = (x2-x1)/L;
    h = (y2-y1)/L;

    coeff = (linear_emodule*A)/L;

    Eigen::Matrix<double,2,2> partial_K;
    partial_K(0,0) = pow(b,2);
    partial_K(1,0) = b*h;
    partial_K(0,1) = b*h;
    partial_K(1,1) = pow(h,2);
    std::cout << "\n";
    return partial_K*coeff;

}

Eigen::Matrix<dco::gt1s<double>::type,2,2> Truss::calc_partial_K(Edge* edge_ptr, Eigen::Matrix<dco::gt1s<double>::type,Utils::Dynamic,1>& u){
  using T = dco::gt1s<double>::type;
  T x1,nx1,x2,nx2,y1,ny1,y2,ny2,delta_L,old_L,new_L,b,h,A,E,coeff; //l=kantenlaenge, b=breite, h=hoehe

    x1 = edge_ptr->get_joint_ptr1()->x();
    x2 = edge_ptr->get_joint_ptr2()->x();
    y1 = edge_ptr->get_joint_ptr1()->y();
    y2 = edge_ptr->get_joint_ptr2()->y();
    A  = edge_ptr->get_thickness();


    int ind1 = edge_ptr->get_joint_ptr1()->get_locator();
    int ind2 = edge_ptr->get_joint_ptr2()->get_locator();

    nx1 = u(2*ind1) + x1;
    nx2 = u(2*ind2) + x2;
    ny1 = u(2*ind1+1) + y1;
    ny2 = u(2*ind2+1) + y2;

    old_L = sqrt( pow(x1-x2,2) + pow(y1-y2,2));
    new_L = sqrt( pow(nx1-nx2,2) + pow(ny1-ny2,2));

    delta_L = new_L - old_L;
    b = (x2-x1)/old_L;
    h = (y2-y1)/old_L;

    double E_val,E_A,delta_L_value,fool;
    delta_L_value = value(delta_L);

    my_parser->custom_function(delta_L_value,E_val,E_A);

    E = delta_L*E_A;
    fool = delta_L_value*E_A;
    E  += E_val - fool;

    coeff = (E*A)/old_L;

    Eigen::Matrix<T,2,2> partial_K;
    partial_K(0,0) = pow(b,2);
    partial_K(1,0) = b*h;
    partial_K(0,1) = b*h;
    partial_K(1,1) = pow(h,2);
    return partial_K*coeff;
}

    //Sucht Kante zwischen 2 KnotenNr. gibt zurueck: Keine Kante gefunden -> -1 / Kante gefunden -> KantenNr.
int Truss::isEdge(int locator1,int locator2){

    vector<Edge*> v_edges1 = v_joint_ptr[locator1]->get_edges();

    int edge_location=-1;
    for(int i = 0; i < v_edges1.size(); i++){
        if(v_edges1[i]->get_joint_ptr1()->get_locator() == locator2){
          edge_location = i;
          break;
        }
        if(v_edges1[i]->get_joint_ptr2()->get_locator() == locator2){
          edge_location = i;
          break;
        }
  }

  if(edge_location != -1){
      for(int i=0; i<v_edge_ptr.size();i++){
            if(v_edge_ptr[i] == v_edges1[edge_location]){
              edge_location = i;
              break;
            }
        }
    }


  return edge_location;
}

    //Loescht Kante die KnotenNr. = locator1 und KnotenNr. = locator2 verbindet
int Truss::deleteEdge(int locator1,int locator2) {

    vector<Edge*> v_edges1 = v_joint_ptr[locator1]->get_edges();
    int edge_location=-1;

    //Sucht Kantenindex in v_edges
    for(int i = 0; i < v_edges1.size(); i++){
        if(v_edges1[i]->get_joint_ptr1()->get_locator() == locator2){
            edge_location = i;
            break;
        }
        if(v_edges1[i]->get_joint_ptr2()->get_locator() == locator2){
            edge_location = i;
            break;
        }
    }
    Edge* edge_ptr = v_edges1[edge_location];
    v_joint_ptr[locator1]->remove_edge(edge_ptr);
    v_joint_ptr[locator2]->remove_edge(edge_ptr);

    for(int i=0; i< v_edge_ptr.size(); i++){
        if(v_edge_ptr[i] == edge_ptr){
          delete v_edge_ptr[i];
          v_edge_ptr.erase(v_edge_ptr.begin()+i);
          return i;
        }
     }
}

    //Prueft ob Konten mit KnotenNr. = locator in v_joint_ptr vorhanden ist
bool Truss::isJoint(int locator){
    if((locator < 0) || (locator >= v_joint_ptr.size())){return false;}
    return true;
}

    //Fuegt v_force_ptr eine Kraft hinzu
void Truss::addForce(double fx,double fy, int loc){
     Force* temp_force = new Force(v_joint_ptr[loc],fx,fy);
     v_force_ptr.push_back(temp_force);
}

    //Loescht eine Kraft aus v_force_ptr mit KraftNr. = position
void Truss::deleteForce(int position){
     delete v_force_ptr[position];
     v_force_ptr.erase(v_force_ptr.begin() + position);
}

void Truss::set_emodule(double e){
  linear_emodule = e;
}

