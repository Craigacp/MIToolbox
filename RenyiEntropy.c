/*******************************************************************************
** RenyiEntropy.cpp
** Part of the mutual information toolbox
**
** Contains functions to calculate the Renyi alpha entropy of a single variable 
** H_\alpha(X), the Renyi joint entropy of two variables H_\alpha(X,Y), and the 
** conditional Renyi entropy H_\alpha(X|Y)
** 
** Author: Adam Pocock
** Created 26/3/2010
**
**  Copyright 2010 Adam Pocock, The University Of Manchester
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
#include "Entropy.h"

double calculateRenyiEntropy(double alpha, double *dataVector, int vectorLength)
{
  double entropy = 0.0;
  double tempValue = 0.0;
  int i;
  ProbabilityState state = calculateProbability(dataVector,vectorLength);
  
  /*H_\alpha(X) = 1/(1-alpha) * log(2)(sum p(x)^alpha)*/
  for (i = 0; i < state.numStates; i++)
  {
    tempValue = state.probabilityVector[i];
    
    if (tempValue > 0)
    {
      entropy += pow(tempValue,alpha);
      /*printf("Entropy = %f, i = %d\n", entropy,i);*/
    }
  }
  
  /*printf("Entropy = %f\n", entropy);*/
  
  entropy = log(entropy);

  entropy /= log(2.0);
  
  entropy /= (1.0-alpha);
  
  /*printf("Entropy = %f\n", entropy);*/
  FREE_FUNC(state.probabilityVector);
  state.probabilityVector = NULL;
  
  return entropy;
}/*calculateRenyiEntropy(double,double*,int)*/

double calculateJointRenyiEntropy(double alpha, double *firstVector, double *secondVector, int vectorLength)
{
  double jointEntropy = 0.0;  
  double tempValue = 0.0;
  int i;
  JointProbabilityState state = calculateJointProbability(firstVector,secondVector,vectorLength);
  
  /*H_\alpha(XY) = 1/(1-alpha) * log(2)(sum p(xy)^alpha)*/
  for (i = 0; i < state.numJointStates; i++)
  {
    tempValue = state.jointProbabilityVector[i];
    if (tempValue > 0)
    {
      jointEntropy += pow(tempValue,alpha);
    }
  }
  
  jointEntropy = log(jointEntropy);
  
  jointEntropy /= log(2.0);
  
  jointEntropy /= (1.0-alpha);
  
  FREE_FUNC(state.firstProbabilityVector);
  state.firstProbabilityVector = NULL;
  FREE_FUNC(state.secondProbabilityVector);
  state.secondProbabilityVector = NULL;
  FREE_FUNC(state.jointProbabilityVector);
  state.jointProbabilityVector = NULL;
  
  return jointEntropy;
}/*calculateJointRenyiEntropy(double,double*,double*,int)*/

double calcCondRenyiEnt(double alpha, double *dataVector, double *conditionVector, int uniqueInCondVector, int vectorLength)
{
  /*uniqueInCondVector = is the number of unique values in the cond vector.*/
  
  /*condEntropy = sum p(y) * sum p(x|y)^alpha(*/
  
  /*
  ** first generate the seperate variables
  */
  
  double *seperateVectors = (double *) CALLOC_FUNC(uniqueInCondVector*vectorLength,sizeof(double));
  int *seperateVectorCount = (int *) CALLOC_FUNC(uniqueInCondVector,sizeof(int));
  double seperateVectorProb = 0.0;
  int i,j;
  double entropy = 0.0;
  double tempValue = 0.0;
  int currentValue;
  double tempEntropy;
  ProbabilityState state;
  
  double **seperateVectors2D = (double **) CALLOC_FUNC(uniqueInCondVector,sizeof(double*));
  for(j=0; j < uniqueInCondVector; j++)
    seperateVectors2D[j] = seperateVectors + (int)j*vectorLength;
  
  for (i = 0; i < vectorLength; i++)
  {
    currentValue = (int) (conditionVector[i] - 1.0);
    /*printf("CurrentValue = %d\n",currentValue);*/
    seperateVectors2D[currentValue][seperateVectorCount[currentValue]] = dataVector[i];
    seperateVectorCount[currentValue]++;
  }
  
  
  
  for (j = 0; j < uniqueInCondVector; j++)
  {
    tempEntropy = 0.0;
    seperateVectorProb = ((double)seperateVectorCount[j]) / vectorLength;
    state = calculateProbability(seperateVectors2D[j],seperateVectorCount[j]);
    
    /*H_\alpha(X) = 1/(1-alpha) * log(2)(sum p(x)^alpha)*/
    for (i = 0; i < state.numStates; i++)
    {
      tempValue = state.probabilityVector[i];
      
      if (tempValue > 0)
      {
        tempEntropy += pow(tempValue,alpha);
        /*printf("Entropy = %f, i = %d\n", entropy,i);*/
      }
    }
    
    /*printf("Entropy = %f\n", entropy);*/
    
    tempEntropy = log(tempEntropy);

    tempEntropy /= log(2.0);
    
    tempEntropy /= (1.0-alpha);
    
    entropy += tempEntropy;
    
    FREE_FUNC(state.probabilityVector);    
  }

  FREE_FUNC(seperateVectors2D);
  seperateVectors2D = NULL;

  FREE_FUNC(seperateVectors);
  FREE_FUNC(seperateVectorCount);
  
  seperateVectors = NULL;
  seperateVectorCount = NULL;

  return entropy;
}/*calcCondRenyiEnt(double *,double *,int)*/

double calculateConditionalRenyiEntropy(double alpha, double *dataVector, double *conditionVector, int vectorLength)
{
  /*calls this:
  **double calculateConditionalRenyiEntropy(double alpha, double *firstVector, double *condVector, int uniqueInCondVector, int vectorLength) 
  **after determining uniqueInCondVector
  */
  int numUnique = numberOfUniqueValues(conditionVector, vectorLength);
  
  return calcCondRenyiEnt(alpha, dataVector, conditionVector, numUnique, vectorLength);
}/*calculateConditionalRenyiEntropy(double,double*,double*,int)*/

