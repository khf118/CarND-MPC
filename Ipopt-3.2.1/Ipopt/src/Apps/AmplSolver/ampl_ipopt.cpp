// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Common Public License.
//
// $Id: ampl_ipopt.cpp 759 2006-07-07 03:07:08Z andreasw $
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

#include "AmplTNLP.hpp"
#include "IpIpoptApplication.hpp"

int main(int argv, char**argc)
{
  using namespace Ipopt;

  SmartPtr<IpoptApplication> app = new IpoptApplication();

  // Call Initialize the first time to create a journalist, but ignore
  // any options file
  app->Initialize("");

  // Add the suffix handler for scaling
  SmartPtr<AmplSuffixHandler> suffix_handler = new AmplSuffixHandler();
  suffix_handler->AddAvailableSuffix("scaling_factor", AmplSuffixHandler::Variable_Source, AmplSuffixHandler::Number_Type);
  suffix_handler->AddAvailableSuffix("scaling_factor", AmplSuffixHandler::Constraint_Source, AmplSuffixHandler::Number_Type);
  suffix_handler->AddAvailableSuffix("scaling_factor", AmplSuffixHandler::Objective_Source, AmplSuffixHandler::Number_Type);

  SmartPtr<TNLP> ampl_tnlp = new AmplTNLP(ConstPtr(app->Jnlst()),
                                          app->Options(),
                                          argc, suffix_handler);

  // Call Initialize again to process output related options
  app->Initialize();

  ApplicationReturnStatus retval;
  const int n_loops = 1; // make larger for profiling
  for (Index i=0; i<n_loops; i++) {
    retval = app->OptimizeTNLP(ampl_tnlp);
  }

  // finalize_solution method in AmplTNLP writes the solution file

  return 0;
}


