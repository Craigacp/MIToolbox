/*******************************************************************************
** CalculateProbability.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the probability of each state in the array
** and to calculate the probability of the joint state of two arrays
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

#ifndef __CalculateProbability_H
#define __CalculateProbability_H

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct jpState
{
  double *jointProbabilityVector;
  int numJointStates;
  double *firstProbabilityVector;
  int numFirstStates;
  double *secondProbabilityVector;
  int numSecondStates;
} JointProbabilityState;

typedef struct pState
{
  double *probabilityVector;
  int numStates;
} ProbabilityState;

typedef struct wjpState
{
  double *jointProbabilityVector;
  double *jointWeightVector;
  int numJointStates;
  double *firstProbabilityVector;
  double *firstWeightVector;
  int numFirstStates;
  double *secondProbabilityVector;
  double *secondWeightVector;
  int numSecondStates;
} WeightedJointProbState;

typedef struct wpState
{
  double *probabilityVector;
  double *stateWeightVector;
  int numStates;
} WeightedProbState;

/*******************************************************************************
** calculateJointProbability returns the joint probability vector of two vectors
** and the marginal probability vectors in a struct.
** It is the base operation for all information theory calculations involving 
** two or more variables.
**
** length(firstVector) == length(secondVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
JointProbabilityState calculateJointProbability(double *firstVector, double *secondVector, int vectorLength);

/*******************************************************************************
** calculateWeightedJointProbability returns the same joint state object
** as calculateJointProbability, with additional weightVectors giving the 
** weight assigned to each state.
*******************************************************************************/
WeightedJointProbState calculateWeightedJointProbability(double *firstVector, double *secondVector, double *exampleWeightVector, int vectorLength);

/*******************************************************************************
** calculateProbability returns the probability vector from one vector.
** It is the base operation for all information theory calculations involving 
** one variable
**
** length(dataVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
ProbabilityState calculateProbability(double *dataVector, int vectorLength);

/*******************************************************************************
** calculateWeightedProbability returns the same state object
** as calculateProbability, with an additional weightVector giving the 
** weight assigned to each state.
*******************************************************************************/
WeightedProbState calculateWeightedProbability(double *dataVector, double *exampleWeightVector, int vectorLength);

#ifdef __cplusplus
}
#endif

#endif

