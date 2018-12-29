//
// Created by michaelo on 12/28/18.
//

#ifndef INC_3DFINALPROJECRT_JAPSPHERE_H
#define INC_3DFINALPROJECRT_JAPSPHERE_H

#include "../utils/Utils.h"
#include <cmath>

class jaapSphere {

public:
    static RowVector3 calculateCenterOfSphere(Eigen::MatrixXd meshPointsS, Eigen::MatrixXd meshPointsInnerS, int numberOfRowsInner);

private:
    static double getMinOutOfMesh(Eigen::MatrixXd meshPointsS, RowVector3 p);

    static double calcDistance(RowVector3 q, RowVector3 p);

};


#endif //INC_3DFINALPROJECRT_JAPSPHERE_H
