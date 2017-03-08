/*
 * Copyright 2015, LAAS-CNRS
 * Author: Andrea Del Prete
 */

#ifndef CENTROIDAL_DYNAMICS_LIB_SOLVER_QPOASES_HH
#define CENTROIDAL_DYNAMICS_LIB_SOLVER_QPOASES_HH

#include <centroidal-dynamics-lib/config.hh>
#include <centroidal-dynamics-lib/util.hh>
#include <centroidal-dynamics-lib/solver_LP_abstract.hh>
#include <qpOASES.hpp>

namespace robust_equilibrium
{

class CENTROIDAL_DYNAMICS_DLLAPI Solver_LP_qpoases: public Solver_LP_abstract
{
private:
  qpOASES::Options    m_options;  // solver options
  qpOASES::SQProblem  m_solver;   // qpoases solver

  MatrixXX              m_H;              // Hessian matrix
  bool                  m_init_succeeded; // true if solver has been successfully initialized
  qpOASES::returnValue  m_status;         // status code returned by the solver

public:

  Solver_LP_qpoases();

  /** Solve the linear program
   *  minimize    c' x
   *  subject to  Alb <= A x <= Aub
   *              lb <= x <= ub
   */
  LP_status solve(Cref_vectorX c, Cref_vectorX lb, Cref_vectorX ub,
                  Cref_matrixXX A, Cref_vectorX Alb, Cref_vectorX Aub,
                  Ref_vectorX sol);

  /** Get the status of the solver. */
  virtual LP_status getStatus();

  /** Get the objective value of the last solved problem. */
  virtual double getObjectiveValue(){ return m_solver.getObjVal(); }

  virtual void getDualSolution(Ref_vectorX res){ m_solver.getDualSolution(res.data()); }

};

} // end namespace robust_equilibrium

#endif //CENTROIDAL_DYNAMICS_LIB_SOLVER_QPOASES_HH