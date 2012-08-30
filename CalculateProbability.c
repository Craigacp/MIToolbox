/*******************************************************************************
** CalculateProbability.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the probability of each state in the array
** and to calculate the probability of the joint state of two arrays
** 
** Author: Adam Pocock
** Created: 17/02/2010
** Modified: 04/07/2011 - added weighted probability functions
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

JointProbabilityState calculateJointProbability(double *firstVector, double *secondVector, int vectorLength)
{
  int *firstNormalisedVector;
  int *secondNormalisedVector;
  int *firstStateCounts;
  int *secondStateCounts;
  int *jointStateCounts;
  double *firstStateProbs;
  double *secondStateProbs;
  double *jointStateProbs;
  int firstNumStates;
  int secondNumStates;
  int jointNumStates;
  int i;
  double length = vectorLength;
  JointProbabilityState state;

  firstNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  secondNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  
  firstNumStates = normaliseArray(firstVector,firstNormalisedVector,vectorLength);
  secondNumStates = normaliseArray(secondVector,secondNormalisedVector,vectorLength);
  jointNumStates = firstNumStates * secondNumStates;
  
  firstStateCounts = (int *) CALLOC_FUNC(firstNumStates,sizeof(int));
  secondStateCounts = (int *) CALLOC_FUNC(secondNumStates,sizeof(int));
  jointStateCounts = (int *) CALLOC_FUNC(jointNumStates,sizeof(int));
  
  firstStateProbs = (double *) CALLOC_FUNC(firstNumStates,sizeof(double));
  secondStateProbs = (double *) CALLOC_FUNC(secondNumStates,sizeof(double));
  jointStateProbs = (double *) CALLOC_FUNC(jointNumStates,sizeof(double));
    
  /* optimised version, less numerically stable
  double fractionalState = 1.0 / vectorLength;
  
  for (i = 0; i < vectorLength; i++)
  {
    firstStateProbs[firstNormalisedVector[i]] += fractionalState;
    secondStateProbs[secondNormalisedVector[i]] += fractionalState;
    jointStateProbs[secondNormalisedVector[i] * firstNumStates + firstNormalisedVector[i]] += fractionalState;
  }
  */
  
  /* Optimised for number of FP operations now O(states) instead of O(vectorLength) */
  for (i = 0; i < vectorLength; i++)
  {
    firstStateCounts[firstNormalisedVector[i]] += 1;
    secondStateCounts[secondNormalisedVector[i]] += 1;
    jointStateCounts[secondNormalisedVector[i] * firstNumStates + firstNormalisedVector[i]] += 1;
  }
  
  for (i = 0; i < firstNumStates; i++)
  {
    firstStateProbs[i] = firstStateCounts[i] / length;
  }
  
  for (i = 0; i < secondNumStates; i++)
  {
    secondStateProbs[i] = secondStateCounts[i] / length;
  }
  
  for (i = 0; i < jointNumStates; i++)
  {
    jointStateProbs[i] = jointStateCounts[i] / length;
  }

  FREE_FUNC(firstNormalisedVector);
  FREE_FUNC(secondNormalisedVector);
  FREE_FUNC(firstStateCounts);
  FREE_FUNC(secondStateCounts);
  FREE_FUNC(jointStateCounts);
    
  firstNormalisedVector = NULL;
  secondNormalisedVector = NULL;
  firstStateCounts = NULL;
  secondStateCounts = NULL;
  jointStateCounts = NULL;
  
  /*
  **typedef struct 
  **{
  **  double *jointProbabilityVector;
  **  int numJointStates;
  **  double *firstProbabilityVector;
  **  int numFirstStates;
  **  double *secondProbabilityVector;
  **  int numSecondStates;
  **} JointProbabilityState;
  */
  
  state.jointProbabilityVector = jointStateProbs;
  state.numJointStates = jointNumStates;
  state.firstProbabilityVector = firstStateProbs;
  state.numFirstStates = firstNumStates;
  state.secondProbabilityVector = secondStateProbs;
  state.numSecondStates = secondNumStates;

  return state;
}/*calculateJointProbability(double *,double *, int)*/

WeightedJointProbState calculateWeightedJointProbability(double *firstVector, double *secondVector, double *weightVector, int vectorLength)
{
  int *firstNormalisedVector;
  int *secondNormalisedVector;
  int *firstStateCounts;
  int *secondStateCounts;
  int *jointStateCounts;
  double *firstStateProbs;
  double *secondStateProbs;
  double *jointStateProbs;
  double *firstWeightVec;
  double *secondWeightVec;
  double *jointWeightVec;
  int firstNumStates;
  int secondNumStates;
  int jointNumStates;
  int i;
  double length = vectorLength;
  WeightedJointProbState state;

  firstNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  secondNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  
  firstNumStates = normaliseArray(firstVector,firstNormalisedVector,vectorLength);
  secondNumStates = normaliseArray(secondVector,secondNormalisedVector,vectorLength);
  jointNumStates = firstNumStates * secondNumStates;
  
  firstStateCounts = (int *) CALLOC_FUNC(firstNumStates,sizeof(int));
  secondStateCounts = (int *) CALLOC_FUNC(secondNumStates,sizeof(int));
  jointStateCounts = (int *) CALLOC_FUNC(jointNumStates,sizeof(int));
  
  firstStateProbs = (double *) CALLOC_FUNC(firstNumStates,sizeof(double));
  secondStateProbs = (double *) CALLOC_FUNC(secondNumStates,sizeof(double));
  jointStateProbs = (double *) CALLOC_FUNC(jointNumStates,sizeof(double));
    
  firstWeightVec = (double *) CALLOC_FUNC(firstNumStates,sizeof(double));
  secondWeightVec = (double *) CALLOC_FUNC(secondNumStates,sizeof(double));
  jointWeightVec = (double *) CALLOC_FUNC(jointNumStates,sizeof(double));
    
  for (i = 0; i < vectorLength; i++)
  {
    firstStateCounts[firstNormalisedVector[i]] += 1;
    secondStateCounts[secondNormalisedVector[i]] += 1;
    jointStateCounts[secondNormalisedVector[i] * firstNumStates + firstNormalisedVector[i]] += 1;

    firstWeightVec[firstNormalisedVector[i]] += weightVector[i];
    secondWeightVec[secondNormalisedVector[i]] += weightVector[i];
    jointWeightVec[secondNormalisedVector[i] * firstNumStates + firstNormalisedVector[i]] += weightVector[i];
  }
  
  for (i = 0; i < firstNumStates; i++)
  {
    if (firstStateCounts[i])
    {
      firstStateProbs[i] = firstStateCounts[i] / length;
      firstWeightVec[i] /= firstStateCounts[i];
    }
  }
  
  for (i = 0; i < secondNumStates; i++)
  {
    if (secondStateCounts[i])
    {
      secondStateProbs[i] = secondStateCounts[i] / length;
      secondWeightVec[i] /= secondStateCounts[i];
    }
  }
  
  for (i = 0; i < jointNumStates; i++)
  {
    if (jointStateCounts[i])
    {
      jointStateProbs[i] = jointStateCounts[i] / length;
      jointWeightVec[i] /= jointStateCounts[i];
    }
  }

  FREE_FUNC(firstNormalisedVector);
  FREE_FUNC(secondNormalisedVector);
  FREE_FUNC(firstStateCounts);
  FREE_FUNC(secondStateCounts);
  FREE_FUNC(jointStateCounts);
    
  firstNormalisedVector = NULL;
  secondNormalisedVector = NULL;
  firstStateCounts = NULL;
  secondStateCounts = NULL;
  jointStateCounts = NULL;
  
  /*
  **typedef struct 
  **{
  **  double *jointProbabilityVector;
  **  double *jointWeightVector;
  **  int numJointStates;
  **  double *firstProbabilityVector;
  **  double *firstWeightVector;
  **  int numFirstStates;
  **  double *secondProbabilityVector;
  **  double *secondWeightVector;
  **  int numSecondStates;
  **} WeightedJointProbState;
  */
  
  state.jointProbabilityVector = jointStateProbs;
  state.jointWeightVector = jointWeightVec;
  state.numJointStates = jointNumStates;
  state.firstProbabilityVector = firstStateProbs;
  state.firstWeightVector = firstWeightVec;
  state.numFirstStates = firstNumStates;
  state.secondProbabilityVector = secondStateProbs;
  state.secondWeightVector = secondWeightVec;
  state.numSecondStates = secondNumStates;

  return state;
}/*calculateJointProbability(double *,double *, int)*/

ProbabilityState calculateProbability(double *dataVector, int vectorLength)
{
  int *normalisedVector;
  int *stateCounts;
  double *stateProbs;
  int numStates;
  /*double fractionalState;*/
  ProbabilityState state;
  int i;
  double length = vectorLength;

  normalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  
  numStates = normaliseArray(dataVector,normalisedVector,vectorLength);
  
  stateCounts = (int *) CALLOC_FUNC(numStates,sizeof(int));
  stateProbs = (double *) CALLOC_FUNC(numStates,sizeof(double));
  
  /* optimised version, may have floating point problems 
  fractionalState = 1.0 / vectorLength;
  
  for (i = 0; i < vectorLength; i++)
  {
    stateProbs[normalisedVector[i]] += fractionalState;
  }
  */
  
  /* Optimised for number of FP operations now O(states) instead of O(vectorLength) */
  for (i = 0; i < vectorLength; i++)
  {
    stateCounts[normalisedVector[i]] += 1;
  }
  
  for (i = 0; i < numStates; i++)
  {
    stateProbs[i] = stateCounts[i] / length;
  }
  
  FREE_FUNC(stateCounts);
  FREE_FUNC(normalisedVector);
  
  stateCounts = NULL;
  normalisedVector = NULL;
  
  state.probabilityVector = stateProbs;
  state.numStates = numStates;

  return state;
}/*calculateProbability(double *,int)*/


WeightedProbState calculateWeightedProbability(double *dataVector, double *exampleWeightVector, int vectorLength)
{
  int *normalisedVector;
  int *stateCounts;
  double *stateProbs;
  double *stateWeights;
  int numStates;
  WeightedProbState state;
  int i;
  double length = vectorLength;

  normalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  
  numStates = normaliseArray(dataVector,normalisedVector,vectorLength);
  
  stateCounts = (int *) CALLOC_FUNC(numStates,sizeof(int));
  stateProbs = (double *) CALLOC_FUNC(numStates,sizeof(double));
  stateWeights = (double *) CALLOC_FUNC(numStates,sizeof(double));

  for (i = 0; i < vectorLength; i++)
  {
    stateCounts[normalisedVector[i]] += 1;
    stateWeights[normalisedVector[i]] += exampleWeightVector[i];
  }
  
  for (i = 0; i < numStates; i++)
  {
    stateProbs[i] = stateCounts[i] / length;
    stateWeights[i] /= stateCounts[i];
  }
  
  FREE_FUNC(stateCounts);
  FREE_FUNC(normalisedVector);
  
  stateCounts = NULL;
  normalisedVector = NULL;
  
  state.probabilityVector = stateProbs;
  state.stateWeightVector = stateWeights;
  state.numStates = numStates;

  return state;
}/*calculateProbability(double *,int)*/
