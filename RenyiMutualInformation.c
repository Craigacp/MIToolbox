/*******************************************************************************
** RenyiMutualInformation.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the Renyi mutual information of 
** two variables X and Y, I_\alpha(X;Y), using the Renyi alpha divergence and 
** the joint entropy difference
** 
** Author: Adam Pocock
** Created 26/3/2010
**
** Copyright 2010 Adam Pocock, The University Of Manchester
** www.cs.manchester.ac.uk
**
** This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#include "MIToolbox.h"
#include "ArrayOperations.h"
#include "CalculateProbability.h"
#include "RenyiEntropy.h"
#include "RenyiMutualInformation.h"

double calculateRenyiMIDivergence(double alpha, double *dataVector, double *targetVector, int vectorLength)
{
  double mutualInformation = 0.0;
  int firstIndex,secondIndex;
  int i;
  double jointTemp = 0.0;
  double seperateTemp = 0.0;
  double invAlpha = 1.0 - alpha;
  JointProbabilityState state = calculateJointProbability(dataVector,targetVector,vectorLength);
    
  /* standard MI is D_KL(p(x,y)||p(x)p(y))
  ** which expands to
  ** D_KL(p(x,y)||p(x)p(y)) = sum(p(x,y) * log(p(x,y)/(p(x)p(y))))
  **
  ** Renyi alpha divergence D_alpha(p(x,y)||p(x)p(y))
  ** expands to
  ** D_alpha(p(x,y)||p(x)p(y)) = 1/(alpha-1) * log(sum((p(x,y)^alpha)*((p(x)p(y))^(1-alpha))))
  */
  
  for (i = 0; i < state.numJointStates; i++)
  {
    firstIndex = i % state.numFirstStates;
    secondIndex = i / state.numFirstStates;
    
    if ((state.jointProbabilityVector[i] > 0) && (state.firstProbabilityVector[firstIndex] > 0) && (state.secondProbabilityVector[secondIndex] > 0))
    {      
      jointTemp = pow(state.jointProbabilityVector[i],alpha);
      seperateTemp = state.firstProbabilityVector[firstIndex] * state.secondProbabilityVector[secondIndex];
      seperateTemp = pow(seperateTemp,invAlpha);
      mutualInformation += (jointTemp * seperateTemp);
    }
  }

  mutualInformation = log(mutualInformation);
  mutualInformation /= log(2.0);  
  mutualInformation /= (alpha-1.0);  
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return mutualInformation;
}/*calculateRenyiMIDivergence(double, double *, double *, int)*/

double calculateRenyiMIJoint(double alpha, double *dataVector, double *targetVector, int vectorLength)
{
  double hY = calculateRenyiEntropy(alpha, targetVector, vectorLength);
  double hX = calculateRenyiEntropy(alpha, dataVector, vectorLength);
  
  double hXY = calculateJointRenyiEntropy(alpha, dataVector, targetVector, vectorLength);
  
  double answer = hX + hY - hXY;
  
  return answer;
}/*calculateRenyiMIJoint(double, double*, double*, int)*/

