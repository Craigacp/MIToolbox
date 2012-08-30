/*******************************************************************************
** WeightedMutualInformation.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the mutual information of 
** two variables X and Y, I(X;Y), to calculate the joint mutual information
** of two variables X & Z on the variable Y, I(XZ;Y), and the conditional
** mutual information I(X;Y|Z), while using a weight vector to modify the
** calculation.
** 
** Author: Adam Pocock
** Created: 20/06/2011
**
**  Copyright 2010/2011 Adam Pocock, The University Of Manchester
**  www.cs.manchester.ac.uk
**
**  This file is part of MIToolbox.
**
**  MIToolbox is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  MIToolbox is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with MIToolbox.  If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#include "MIToolbox.h"
#include "ArrayOperations.h"
#include "CalculateProbability.h"
#include "WeightedEntropy.h"
#include "WeightedMutualInformation.h"

double calculateWeightedMutualInformation(double *dataVector, double *targetVector, double *weightVector, int vectorLength)
{
  double mutualInformation = 0.0;
  int firstIndex,secondIndex;
  int i;
  WeightedJointProbState state = calculateWeightedJointProbability(dataVector,targetVector,weightVector,vectorLength);
    
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
      mutualInformation += state.jointWeightVector[i] * state.jointProbabilityVector[i] * log(state.jointProbabilityVector[i] / state.firstProbabilityVector[firstIndex] / state.secondProbabilityVector[secondIndex]);
    }
  }
  
  mutualInformation /= log(LOG_BASE);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return mutualInformation;
}/*calculateWeightedMutualInformation(double *,double *,double *,int)*/

double calculateWeightedConditionalMutualInformation(double *dataVector, double *targetVector, double *conditionVector, double *weightVector, int vectorLength)
{
  double mutualInformation = 0.0;
  double firstCondition, secondCondition;
  double *mergedVector = (double *) CALLOC_FUNC(vectorLength,sizeof(double));
  
  mergeArrays(targetVector,conditionVector,mergedVector,vectorLength);
  
  /* I(X;Y|Z) = H(X|Z) - H(X|YZ) */
  /* double calculateWeightedConditionalEntropy(double *dataVector, double *conditionVector, double *weightVector, int vectorLength); */
  firstCondition = calculateWeightedConditionalEntropy(dataVector,conditionVector,weightVector,vectorLength);
  secondCondition = calculateWeightedConditionalEntropy(dataVector,mergedVector,weightVector,vectorLength);
  
  mutualInformation = firstCondition - secondCondition;
  
  FREE_FUNC(mergedVector);
  mergedVector = NULL;
  
  return mutualInformation;
}/*calculateWeightedConditionalMutualInformation(double *,double *,double *,double *,int)*/

