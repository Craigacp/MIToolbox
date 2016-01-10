/*******************************************************************************
** Entropy.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the entropy of a single variable H(X), 
** the joint entropy of two variables H(X,Y), and the conditional entropy
** H(X|Y)
** 
** Author: Adam Pocock
** Created 19/2/2010
**
** Copyright 2010 Adam Pocock, The University Of Manchester
** www.cs.manchester.ac.uk
**
** This file is part of MIToolbox.
**
** This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#include "MIToolbox.h"
#include "CalculateProbability.h"
#include "Entropy.h"

double calculateEntropy(double *dataVector, int vectorLength)
{
  double entropy = 0.0;
  double tempValue = 0.0;
  int i;
  ProbabilityState state = calculateProbability(dataVector,vectorLength);
  
  /*H(X) = - sum p(x) log p(x)*/
  for (i = 0; i < state.numStates; i++)
  {
    tempValue = state.probabilityVector[i];
    
    if (tempValue > 0)
    {
      entropy -= tempValue * log(tempValue);
    }
  }
  
  entropy /= log(2.0);
  
  FREE_FUNC(state.probabilityVector);
  state.probabilityVector = NULL;
  
  return entropy;
}/*calculateEntropy(double *,int)*/

double calculateJointEntropy(double *firstVector, double *secondVector, int vectorLength)
{
  double jointEntropy = 0.0;  
  double tempValue = 0.0;
  int i;
  JointProbabilityState state = calculateJointProbability(firstVector,secondVector,vectorLength);
  
  /*H(XY) = - sumx sumy p(xy) log p(xy)*/
  for (i = 0; i < state.numJointStates; i++)
  {
    tempValue = state.jointProbabilityVector[i];
    if (tempValue > 0)
    {
      jointEntropy -= tempValue * log(tempValue);
    }
  }
  
  jointEntropy /= log(2.0);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return jointEntropy;
}/*calculateJointEntropy(double *, double *, int)*/

double calculateConditionalEntropy(double *dataVector, double *conditionVector, int vectorLength)
{
  /*
  ** Conditional entropy
  ** H(X|Y) = - sumx sumy p(xy) log p(xy)/p(y)
  */
  
  double condEntropy = 0.0;  
  double jointValue = 0.0;
  double condValue = 0.0;
  int i;
  JointProbabilityState state = calculateJointProbability(dataVector,conditionVector,vectorLength);
  
  /*H(X|Y) = - sumx sumy p(xy) log p(xy)/p(y)*/
  /* to index by numFirstStates use modulus of i
  ** to index by numSecondStates use integer division of i by numFirstStates
  */
  for (i = 0; i < state.numJointStates; i++)
  {
    jointValue = state.jointProbabilityVector[i];
    condValue = state.secondProbabilityVector[i / state.numFirstStates];
    if ((jointValue > 0) && (condValue > 0))
    {
      condEntropy -= jointValue * log(jointValue / condValue);
    }
  }
  
  condEntropy /= log(2.0);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return condEntropy;

}/*calculateConditionalEntropy(double *, double *, int)*/

