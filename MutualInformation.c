/*******************************************************************************
** MutualInformation.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the mutual information of 
** two variables X and Y, I(X;Y), to calculate the joint mutual information
** of two variables X & Z on the variable Y, I(XZ;Y), and the conditional
** mutual information I(x;Y|Z)
** 
** Author: Adam Pocock
** Created 19/2/2010
** Updated - 22/02/2014 - Added checking on calloc.
**
** Copyright 2010-2014 Adam Pocock, The University Of Manchester
** www.cs.manchester.ac.uk
**
** This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#include "MIToolbox.h"
#include "ArrayOperations.h"
#include "CalculateProbability.h"
#include "Entropy.h"
#include "MutualInformation.h"

double calculateMutualInformation(double *dataVector, double *targetVector, int vectorLength)
{
  double mutualInformation = 0.0;
  int firstIndex,secondIndex;
  int i;
  JointProbabilityState state = calculateJointProbability(dataVector,targetVector,vectorLength);
    
  /*
  ** I(X;Y) = sum sum p(xy) * log (p(xy)/p(x)p(y))
  */
  for (i = 0; i < state.numJointStates; i++)
  {
    firstIndex = i % state.numFirstStates;
    secondIndex = i / state.numFirstStates;
    
    if ((state.jointProbabilityVector[i] > 0) && (state.firstProbabilityVector[firstIndex] > 0) && (state.secondProbabilityVector[secondIndex] > 0))
    {
      /*double division is probably more stable than multiplying two small numbers together
      ** mutualInformation += state.jointProbabilityVector[i] * log(state.jointProbabilityVector[i] / (state.firstProbabilityVector[firstIndex] * state.secondProbabilityVector[secondIndex]));
      */
      mutualInformation += state.jointProbabilityVector[i] * log(state.jointProbabilityVector[i] / state.firstProbabilityVector[firstIndex] / state.secondProbabilityVector[secondIndex]);
    }
  }
  
  mutualInformation /= log(2.0);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return mutualInformation;
}/*calculateMutualInformation(double *,double *,int)*/

double calculateConditionalMutualInformation(double *dataVector, double *targetVector, double *conditionVector, int vectorLength)
{
  double mutualInformation = 0.0;
  double firstCondition, secondCondition;
  double *mergedVector = (double *) checkedCalloc(vectorLength,sizeof(double));
  
  mergeArrays(targetVector,conditionVector,mergedVector,vectorLength);
  
  /* I(X;Y|Z) = H(X|Z) - H(X|YZ) */
  /* double calculateConditionalEntropy(double *dataVector, double *conditionVector, int vectorLength); */
  firstCondition = calculateConditionalEntropy(dataVector,conditionVector,vectorLength);
  secondCondition = calculateConditionalEntropy(dataVector,mergedVector,vectorLength);
  
  mutualInformation = firstCondition - secondCondition;
  
  FREE_FUNC(mergedVector);
  mergedVector = NULL;
  
  return mutualInformation;
}/*calculateConditionalMutualInformation(double *,double *,double *,int)*/

