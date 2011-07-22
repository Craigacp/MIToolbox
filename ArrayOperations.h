/*******************************************************************************
** ArrayOperations.h
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

#ifndef __ArrayOperations_H
#define __ArrayOperations_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** Simple print function for debugging
*******************************************************************************/
void printDoubleVector(double *vector, int vectorLength);

void printIntVector(int *vector, int vectorLength);

/*******************************************************************************
** numberOfUniqueValues finds the number of unique values in an array by 
** repeatedly iterating through the array and checking if a value has been 
** seen previously
*******************************************************************************/
int numberOfUniqueValues(double *featureVector, int vectorLength);

/******************************************************************************* 
** normaliseArray takes an input vector and writes an output vector
** which is a normalised version of the input, and returns the number of states
** A normalised array has min value = 0, max value = number of states
** and all values are integers
**
** length(inputVector) == length(outputVector) == vectorLength otherwise there
** is a memory leak
*******************************************************************************/
int normaliseArray(double *inputVector, int *outputVector, int vectorLength);

/*******************************************************************************
** mergeArrays takes in two arrays and writes the joint state of those arrays
** to the output vector
**
** the length of the vectors must be the same and equal to vectorLength
*******************************************************************************/
int mergeArrays(double *firstVector, double *secondVector, double *outputVector, int vectorLength);
int mergeArraysArities(double *firstVector, int numFirstStates, double *secondVector, int numSecondStates, double *outputVector, int vectorLength);

/*******************************************************************************
** mergeMultipleArrays takes in a matrix and repeatedly merges the matrix using 
** merge arrays and writes the joint state of that matrix
** to the output vector
**
** the length of the vectors must be the same and equal to vectorLength
** matrixWidth = the number of columns in the matrix
*******************************************************************************/
int mergeMultipleArrays(double *inputMatrix, double *outputVector, int matrixWidth, int vectorLength);
int mergeMultipleArraysArities(double *inputMatrix, double *outputVector, int matrixWidth, int *arities, int vectorLength);

#ifdef __cplusplus
}
#endif

#endif

