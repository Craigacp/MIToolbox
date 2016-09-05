/*******************************************************************************
** WeightedEntropy.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the entropy of a single variable H(X), 
** the joint entropy of two variables H(X,Y), and the conditional entropy
** H(X|Y), while using a weight vector to modify the calculation.
** 
** Author: Adam Pocock
** Created: 20/06/2011
**
** Copyright 2010/2011 Adam Pocock, The University Of Manchester
** www.cs.manchester.ac.uk
**
** This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#include "MIToolbox/MIToolbox.h"
#include "MIToolbox/CalculateProbability.h"
#include "MIToolbox/WeightedEntropy.h"

double calculateWeightedEntropy(double *dataVector, double *weightVector, int vectorLength)
{
  double entropy = 0.0;
  double tempValue = 0.0;
  int i;
  WeightedProbState state = calculateWeightedProbability(dataVector,weightVector,vectorLength);
  
  /*H(X) = - sum p(x) log p(x)*/
  for (i = 0; i < state.numStates; i++)
  {
    tempValue = state.probabilityVector[i];
    
    if (tempValue > 0)
    {
      entropy -= state.stateWeightVector[i] * tempValue * log(tempValue);
    }
  }
  
  entropy /= log(LOG_BASE);
  
  FREE_FUNC(state.probabilityVector);
  state.probabilityVector = NULL;
  FREE_FUNC(state.stateWeightVector);
  state.stateWeightVector = NULL;
  
  return entropy;
}/*calculateWeightedEntropy(double *,double *,int)*/

double calculateWeightedJointEntropy(double *firstVector, double *secondVector, double *weightVector, int vectorLength)
{
  double jointEntropy = 0.0;  
  double tempValue = 0.0;
  int i;
  WeightedJointProbState state = calculateWeightedJointProbability(firstVector,secondVector,weightVector,vectorLength);
  
  /*H(XY) = - sumx sumy p(xy) log p(xy)*/
  for (i = 0; i < state.numJointStates; i++)
  {
    tempValue = state.jointProbabilityVector[i];
    if (tempValue > 0)
    {
      jointEntropy -= state.jointWeightVector[i] * tempValue * log(tempValue);
    }
  }
  
  jointEntropy /= log(LOG_BASE);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  FREE_FUNC(state.firstWeightVector);
  state.firstWeightVector = NULL;
  FREE_FUNC(state.secondWeightVector);
  state.secondWeightVector = NULL;
  FREE_FUNC(state.jointWeightVector);
  state.jointWeightVector = NULL;
  
  return jointEntropy;
}/*calculateWeightedJointEntropy(double *,double *,double *,int)*/

double calculateWeightedConditionalEntropy(double *dataVector, double *conditionVector, double *weightVector, int vectorLength)
{
  /*
  ** Conditional entropy
  ** H(X|Y) = - sumx sumy p(xy) log p(xy)/p(y)
  */
  
  double condEntropy = 0.0;  
  double jointValue = 0.0;
  double condValue = 0.0;
  int i;
  WeightedJointProbState state = calculateWeightedJointProbability(dataVector,conditionVector,weightVector,vectorLength);
  
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
      condEntropy -= state.jointWeightVector[i] * jointValue * log(jointValue / condValue);
    }
  }
  
  condEntropy /= log(LOG_BASE);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  FREE_FUNC(state.firstWeightVector);
  state.firstWeightVector = NULL;
  FREE_FUNC(state.secondWeightVector);
  state.secondWeightVector = NULL;
  FREE_FUNC(state.jointWeightVector);
  state.jointWeightVector = NULL;
  
  return condEntropy;

}/*calculateWeightedConditionalEntropy(double *,double *,double *,int)*/

