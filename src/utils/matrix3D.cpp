//
// Created by xerious on 10/10/17.
//

#include "matrix3D.h"

matrix3D::matrix3D(const Vector3D &col_p, const Vector3D &col_q, const Vector3D &col_r) : col_p(col_p), col_q(col_q),
                                                                                          col_r(col_r) {

}


double matrix3D::getDeterminant()
{

    double det =
            col_p.X()*( col_q.Y()*col_r.Z()  -  col_q.Z()*col_r.Y() )
            - ( col_q.X()*( col_p.Y() * col_r.Z() -  col_p.Z() * col_r.Y())  )
            + col_r.X()*(col_p.Y() * col_q.Z() - col_p.Z() * col_q.Y() );

    return det;
}