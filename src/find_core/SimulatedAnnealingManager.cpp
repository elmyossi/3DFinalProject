//
// Created by Yossi Elman on 2018-12-22.
//

#include "SimulatedAnnealingManager.h"
#include <float.h>
#include <cmath>
#include <random>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "../utils/Utils.h"
#include <igl/point_mesh_squared_distance.h>

/*
auto ef = [](RowVector3 x, Eigen::MatrixXd V, Eigen::MatrixXi F){
    Eigen::VectorXd sqrD;
    Eigen::VectorXi I;
    Eigen::MatrixXd C;
    igl::point_mesh_squared_distance((Eigen::PlainObjectBase<RowVector3>) &x,V,F,sqrD,I,C);
    return std::abs( (x - 10)*(x + 20)*(x - 30) );
};

auto tf = [](long double k){
    return std::exp( -20 * k );
};

template<typename generator>
RowVector3 nf(RowVector3 x, generator& g){
    return 0;
    //std::normal_distribution<decltype(x)> d(0, 1);
    //return x + d(g);
}

// To find a RowVector3 with lower energy according to the given condition
template<typename status, typename numOfIterations, typename cost_function , typename temperature_function, typename next_function, typename v_mat, typename f_mat>
RowVector3 simulated_annealing(status&& i_old, numOfIterations&& c, cost_function&& ef , temperature_function&& tf, next_function&& nf, Eigen::MatrixXd V, Eigen::MatrixXi F)
{
    std::mt19937_64 g(std::random_device());
    auto   e_old  = ef(i_old);

    RowVector3 i_best = i_old;
    auto   e_best = e_old;

    std::uniform_real_distribution<decltype(e_old)> rf(0, 1);

    for(; c > 0; --c){
        RowVector3 i_new = nf(i_old, g);
        auto   e_new = ef(i_new, V, F);

        if(e_new < e_best){
            i_best =           i_new ;
            e_best =           e_new ;
            i_old  = std::move(i_new);
            e_old  = std::move(e_new);
            continue;
        }

        auto t = tf(c);
        auto delta_e = e_new - e_old;

        if( delta_e > 10.0 * t) continue;  //as std::exp(-10.0) is a very small number

        if( delta_e <= 0.0 || std::exp( - delta_e / t ) > rf(g) ){
            i_old  = std::move(i_new);
            e_old  = std::move(e_new);
        }
    }
    return(i_best);
}


RowVector3 getOptimalCorePosition(Eigen::MatrixXd V, Eigen::MatrixXi F)
{
    std::random_device rd;
    std::mt19937_64 g(rd());

    RowVector3 root   = Utils::calculateCenterOfMass(V, F);
    std::size_t numOfIterations  = 100;

    root = simulated_annealing(root, numOfIterations, ef, tf, nf, V, F);

    std::cout << "Result:  X= " << root[0] << " Y = " << root[1] << " Z = " << root[2] << std::endl;
    return root;
}
*/
