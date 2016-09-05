/*******************************************************************************
** RenyiEntropy.c
** Part of the mutual information toolbox
**
** Contains functions to calculate the Renyi alpha entropy of a single variable 
** H_\alpha(X), the Renyi joint entropy of two variables H_\alpha(X,Y), and the 
** conditional Renyi entropy H_\alpha(X|Y)
** 
** Author: Adam Pocock
** Created 26/3/2010
** Updated - 22/02/2014 - Added checking on calloc.
**
** Copyright 2010-2014 Adam Pocock, The University Of Manchester
** www.cs.manchester.ac.uk
**
** This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#include "MIToolbox/MIToolbox.h"
#include "MIToolbox/ArrayOperations.h"
#include "MIToolbox/CalculateProbability.h"
#include "MIToolbox/Entropy.h"

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
  
  double *seperateVectors = (double *) checkedCalloc(uniqueInCondVector*vectorLength,sizeof(double));
  int *seperateVectorCount = (int *) checkedCalloc(uniqueInCondVector,sizeof(int));
  int i,j;
  double entropy = 0.0;
  double tempValue = 0.0;
  int currentValue;
  double tempEntropy;
  ProbabilityState state;
  
  double **seperateVectors2D = (double **) checkedCalloc(uniqueInCondVector,sizeof(double*));
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

