#ifndef KINDR_MIN_COMMON_GTSAM_INL_H_
#define KINDR_MIN_COMMON_GTSAM_INL_H_

#include <kindr/minimal/common-gtsam.h>

namespace kindr {
namespace minimal {

template <int N>
Eigen::Matrix<double, N, 1> vectorScalingImplementation(const Eigen::Matrix<double, N, 1> & v, double alpha,
                                                        gtsam::OptionalJacobian<N, N> H1,
                                                        gtsam::OptionalJacobian<N, 1> H2) {
  if (H1) {
    *H1 = gtsam::OptionalJacobian<N,N>::Jacobian::Identity()*alpha;
  }
  if (H2) {
    *H2 = v;
  }
  return v*alpha;
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > vectorScaling(const gtsam::Expression<Eigen::Matrix<double, N, 1> >& v, double alpha) {
  return gtsam::Expression<Eigen::Matrix<double, N, 1> >(boost::bind(&vectorScalingImplementation<N>, _1, alpha, _2, boost::none), v);
}

template <int N>
Eigen::Matrix<double, N, 1> vectorSumImplementation(const Eigen::Matrix<double, N, 1> & v1, const Eigen::Matrix<double, N, 1> & v2,
                                                    gtsam::OptionalJacobian<N, N> H1, gtsam::OptionalJacobian<N, N> H2) {
  if (H1) {
    H1->setIdentity();
  }
  if (H2) {
    H2->setIdentity();
  }
  return v1+v2;
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > vectorSum(const gtsam::Expression<Eigen::Matrix<double, N, 1> >& v1,
                                                          const gtsam::Expression<Eigen::Matrix<double, N, 1> >& v2) {
  return gtsam::Expression<Eigen::Matrix<double, N, 1> >(vectorSumImplementation<N>, v1, v2);
}

template <int N>
Eigen::Matrix<double, N, 1> vectorDifferenceImplementation(const Eigen::Matrix<double, N, 1> & v1,
                                                           const Eigen::Matrix<double, N, 1> & v2,
                                                           gtsam::OptionalJacobian<N, N> H1, gtsam::OptionalJacobian<N, N> H2) {
  if (H1) {
    H1->setIdentity();
  }
  if (H2) {
    H2->setIdentity();
    *H2 = -*H2;
  }
  return v1-v2;
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > vectorDifference(const gtsam::Expression<Eigen::Matrix<double, N, 1> >& v1,
                                                                 const gtsam::Expression<Eigen::Matrix<double, N, 1> >& v2) {
  return gtsam::Expression<Eigen::Matrix<double, N, 1> >(vectorDifferenceImplementation<N>, v1, v2);
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > operator*(const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v, double alpha) {
  return vectorScaling(v, alpha);
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > operator/(const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v, double alpha) {
  return vectorScaling(v, 1.0/alpha);
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > operator-(const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v) {
  return vectorScaling(v, -1.0);
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > operator+(const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v1,
                                                          const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v2) {
  return vectorSum(v1, v2);
}

template <int N>
gtsam::Expression<Eigen::Matrix<double, N, 1> > operator-(const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v1,
                                                          const gtsam::Expression<Eigen::Matrix<double, N, 1> >&v2) {
  return vectorDifference(v1, v2);
}

}
}
#endif  // KINDR_MIN_ROTATION_ANGLE_AXIS_INL_H_
