#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

#define bound 1.0e5 //boundary value for variables which need bound
#define pi 3.1415926;
#define ref_v 80;


class MPC {
 public:
  MPC();

  virtual ~MPC();
  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
