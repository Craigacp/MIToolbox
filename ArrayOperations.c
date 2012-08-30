/*******************************************************************************
** ArrayOperations.cpp
** Part of the mutual information toolbox
**
** Contains functions to floor arrays, and to merge arrays into a joint
** state.
** 
** Author: Adam Pocock
** Created 17/2/2010
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

void printDoubleVector(double *vector, int vectorLength)
{
  int i;
  for (i = 0; i < vectorLength; i++)
  {
    if (vector[i] > 0)
      printf("Val at i=%d, is %f\n",i,vector[i]);
  }/*for number of items in vector*/
}/*printDoubleVector(double*,int)*/

void printIntVector(int *vector, int vectorLength)
{
  int i;
  for (i = 0; i < vectorLength; i++)
  {
    printf("Val at i=%d, is %d\n",i,vector[i]);
  }/*for number of items in vector*/
}/*printIntVector(int*,int)*/

int numberOfUniqueValues(double *featureVector, int vectorLength)
{
  int uniqueValues = 0;
  double *valuesArray = (double *) CALLOC_FUNC(vectorLength,sizeof(double));
  
  int found = 0;
  int j = 0;
  int i;
    
  for (i = 0; i < vectorLength; i++)
  {
    found = 0;
    j = 0;
    while ((j < uniqueValues) && (found == 0))
    {
      if (valuesArray[j] == featureVector[i])
      {
        found = 1;
        featureVector[i] = (double) (j+1);
      }
      j++;
    }
    if (!found)
    {
      valuesArray[uniqueValues] = featureVector[i];
      uniqueValues++;
      featureVector[i] = (double) uniqueValues;
    }
  }/*for vectorlength*/
  
  FREE_FUNC(valuesArray);
  valuesArray = NULL;
  
  return uniqueValues;
}/*numberOfUniqueValues(double*,int)*/

/******************************************************************************* 
** normaliseArray takes an input vector and writes an output vector
** which is a normalised version of the input, and returns the number of states
** A normalised array has min value = 0, max value = number of states
** and all values are integers
**
** length(inputVector) == length(outputVector) == vectorLength otherwise there
** is a memory leak
*******************************************************************************/
int normaliseArray(double *inputVector, int *outputVector, int vectorLength)
{
  int minVal = 0;
  int maxVal = 0;
  int currentValue;
  int i;
  
  if (vectorLength > 0)
  {
    minVal = (int) floor(inputVector[0]);
    maxVal = (int) floor(inputVector[0]);
  
    for (i = 0; i < vectorLength; i++)
    {
      currentValue = (int) floor(inputVector[i]);
      outputVector[i] = currentValue;
      
      if (currentValue < minVal)
      {
        minVal = currentValue;
      }
      else if (currentValue > maxVal)
      {
        maxVal = currentValue;
      }
    }/*for loop over vector*/
    
    for (i = 0; i < vectorLength; i++)
    {
      outputVector[i] = outputVector[i] - minVal;
    }

    maxVal = (maxVal - minVal) + 1;
  }
  
  return maxVal;
}/*normaliseArray(double*,double*,int)*/


/*******************************************************************************
** mergeArrays takes in two arrays and writes the joint state of those arrays
** to the output vector, returning the number of joint states
**
** the length of the vectors must be the same and equal to vectorLength
** outputVector must be malloc'd before calling this function
*******************************************************************************/
int mergeArrays(double *firstVector, double *secondVector, double *outputVector, int vectorLength)
{
  int *firstNormalisedVector;
  int *secondNormalisedVector;
  int firstNumStates;
  int secondNumStates;
  int i;
  int *stateMap;
  int stateCount;
  int curIndex;
  
  firstNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  secondNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));

  firstNumStates = normaliseArray(firstVector,firstNormalisedVector,vectorLength);
  secondNumStates = normaliseArray(secondVector,secondNormalisedVector,vectorLength);
  
  /*
  ** printVector(firstNormalisedVector,vectorLength);
  ** printVector(secondNormalisedVector,vectorLength);
  */
  stateMap = (int *) CALLOC_FUNC(firstNumStates*secondNumStates,sizeof(int));
  stateCount = 1;
  for (i = 0; i < vectorLength; i++)
  {
    curIndex = firstNormalisedVector[i] + (secondNormalisedVector[i] * firstNumStates);
    if (stateMap[curIndex] == 0)
    {
      stateMap[curIndex] = stateCount;
      stateCount++;
    }
    outputVector[i] = stateMap[curIndex];
  }
    
  FREE_FUNC(firstNormalisedVector);
  FREE_FUNC(secondNormalisedVector);
  FREE_FUNC(stateMap);
  
  firstNormalisedVector = NULL;
  secondNormalisedVector = NULL;
  stateMap = NULL;
  
  /*printVector(outputVector,vectorLength);*/
  return stateCount;
}/*mergeArrays(double *,double *,double *, int, bool)*/

int mergeArraysArities(double *firstVector, int numFirstStates, double *secondVector, int numSecondStates, double *outputVector, int vectorLength)
{
  int *firstNormalisedVector;
  int *secondNormalisedVector;
  int i;
  int totalStates;
  int firstStateCheck, secondStateCheck;
  
  firstNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
  secondNormalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));

  firstStateCheck = normaliseArray(firstVector,firstNormalisedVector,vectorLength);
  secondStateCheck = normaliseArray(secondVector,secondNormalisedVector,vectorLength);
  
  if ((firstStateCheck <= numFirstStates) && (secondStateCheck <= numSecondStates))
  {
    for (i = 0; i < vectorLength; i++)
    {
      outputVector[i] = firstNormalisedVector[i] + (secondNormalisedVector[i] * numFirstStates) + 1;
    }
    totalStates = numFirstStates * numSecondStates;
  }
  else
  {
    totalStates = -1;
  }

  FREE_FUNC(firstNormalisedVector);
  FREE_FUNC(secondNormalisedVector);
  
  firstNormalisedVector = NULL;
  secondNormalisedVector = NULL;
  
  return totalStates;
}/*mergeArraysArities(double *,int,double *,int,double *,int)*/

int mergeMultipleArrays(double *inputMatrix, double *outputVector, int matrixWidth, int vectorLength)
{
  int i = 0;
  int currentIndex;
  int currentNumStates;
  int *normalisedVector;
  
  if (matrixWidth > 1)
  {
  	currentNumStates = mergeArrays(inputMatrix, (inputMatrix + vectorLength), outputVector,vectorLength);
  	for (i = 2; i < matrixWidth; i++)
  	{
    	currentIndex = i * vectorLength;
    	currentNumStates = mergeArrays(outputVector,(inputMatrix + currentIndex),outputVector,vectorLength);
  	}
  }
  else
  {
    normalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
    currentNumStates = normaliseArray(inputMatrix,normalisedVector,vectorLength);
  	for (i = 0; i < vectorLength; i++)
  	{
  		outputVector[i] = inputMatrix[i];
  	}
  }
  
  return currentNumStates;
}/*mergeMultipleArrays(double *, double *, int, int, bool)*/


int mergeMultipleArraysArities(double *inputMatrix, double *outputVector, int matrixWidth, int *arities, int vectorLength)
{
  int i = 0;
  int currentIndex;
  int currentNumStates;
  int *normalisedVector;
  
  if (matrixWidth > 1)
  {
  	currentNumStates = mergeArraysArities(inputMatrix, arities[0], (inputMatrix + vectorLength), arities[1], outputVector,vectorLength);
  	for (i = 2; i < matrixWidth; i++)
  	{
    	currentIndex = i * vectorLength;
    	currentNumStates = mergeArraysArities(outputVector,currentNumStates,(inputMatrix + currentIndex),arities[i],outputVector,vectorLength);
    	if (currentNumStates == -1)
    	  break;
  	}
  }
  else
  { 
    normalisedVector = (int *) CALLOC_FUNC(vectorLength,sizeof(int));
    currentNumStates = normaliseArray(inputMatrix,normalisedVector,vectorLength);
  	for (i = 0; i < vectorLength; i++)
  	{
  		outputVector[i] = inputMatrix[i];
  	}
  }
  
  return currentNumStates;
}/*mergeMultipleArraysArities(double *, double *, int, int, bool)*/


