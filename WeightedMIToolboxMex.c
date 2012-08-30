/*******************************************************************************
**
**  WeightedMIToolboxMex.cpp
**  is the MATLAB entry point for the WeightedMIToolbox functions when called 
**  from a MATLAB/OCTAVE script.
**
**  Copyright 2011 Adam Pocock, The University Of Manchester
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

/*******************************************************************************
**entry point for the mex call
**nlhs - number of outputs
**plhs - pointer to array of outputs
**nrhs - number of inputs
**prhs - pointer to array of inputs
*******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /*****************************************************************************
  ** this function takes a flag and a variable number of arguments
  ** depending on the value of the flag and returns either a construct 
  ** containing probability estimates, a merged vector or a double value 
  ** representing an entropy or mutual information
  *****************************************************************************/
  
  int flag, numberOfSamples, checkSamples, thirdCheckSamples, numberOfFeatures, checkFeatures, thirdCheckFeatures;
  int vectorMismatch, columnMismatch, weightLength, weightWidth;
  double *dataVector, *condVector, *targetVector, *firstVector, *secondVector, *output, *weightVector;
  double *weightOutput, *jointWeight, *firstWeight, *secondWeight, *jointOutput, *firstOutput, *secondOutput;
  double *numStates, *numJointStates, *numFirstStates, *numSecondStates;
  WeightedProbState state;
  WeightedJointProbState jointState;
  int i;

  switch (nrhs)
  {
    case 3:
    {
        /*printf("Must be H_w(X)\n");*/
        break;
    }
    case 4:
    {
        /*printf("Must be H_w(XY), H_w(X|Y), I_w(X;Y)\n");*/
        break;
    }
    case 5:
    {
        /*printf("Must be I_w(X;Y|Z)\n");*/
        break;
    }
    default:
    {
        printf("Incorrect number of arguments, format is WeightedMIToolbox(\"FLAG\",varargin)\n");
        break;
    }
  }
  
  vectorMismatch = 0;
  columnMismatch = 0;

  /* number to function map
  ** 1 = H(X)
  ** 2 = H(XY)
  ** 3 = H(X|Y)
  ** 4 = I(X;Y)
  ** 5 = I(X;Y|Z)
  ** 6 = calculateWeightedProbability
  ** 7 = calculateWeightedJointProbability
  */
  
  flag = *mxGetPr(prhs[0]);
  weightLength = mxGetM(prhs[1]);
  weightWidth = mxGetN(prhs[1]);
  weightVector = (double *) mxGetPr(prhs[1]);
  
  switch (flag)
  {
    case 1:
    {
      /*
      **H(X)
      */
      numberOfSamples = mxGetM(prhs[2]);
      numberOfFeatures = mxGetN(prhs[2]);
      dataVector = (double *) mxGetPr(prhs[2]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (weightWidth == 1))
      {
        if (numberOfSamples == weightLength)
        {
          /*double calculateWeightedEntropy(double *dataVector, double *weightVector, int vectorLength);*/
          *output = calculateWeightedEntropy(dataVector,weightVector,numberOfSamples);
        }
        else
        {
          vectorMismatch = 1;
        }
      }
      else
      {
        columnMismatch = 1;
      }
      
      break;
    }/*case 1 - H(X)*/
    case 2:
    {
      /*
      **H(XY)
      */
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);

      firstVector = mxGetPr(prhs[2]);
      secondVector = mxGetPr(prhs[3]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (checkFeatures == 1) && (weightWidth == 1))
      {
        if ((numberOfSamples == 0) && (checkSamples == 0) && (weightLength == 0))
        {
          *output = 0.0;
        }
        else if ((numberOfSamples == 0) && (weightLength == checkSamples))
        {
          *output = calculateWeightedEntropy(secondVector,weightVector,numberOfSamples);
        }
        else if ((checkSamples == 0) && (weightLength == numberOfSamples))
        {
          *output = calculateWeightedEntropy(firstVector,weightVector,numberOfSamples);
        }
        else if ((numberOfSamples == checkSamples) && (numberOfSamples == weightLength))
        {
          /*double calculateWeightedJointEntropy(double *firstVector, double *secondVector, double *weightVector, int vectorLength);*/
          *output = calculateWeightedJointEntropy(firstVector,secondVector,weightVector,numberOfSamples);
        }
        else
        {
          vectorMismatch = 1;
        }
      }
      else
      {
        columnMismatch = 1;
      }
      
      break;
    }/*case 2 - H(XY)*/
    case 3:
    {
      /*
      **H(X|Y)
      */
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);

      dataVector = mxGetPr(prhs[2]);
      condVector = mxGetPr(prhs[3]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (checkFeatures == 1) && (weightWidth == 1))
      {
        if (numberOfSamples == 0)
        {
          *output = 0.0;
        }
        else if ((checkSamples == 0) && (weightLength == numberOfSamples))
        {
          *output = calculateWeightedEntropy(dataVector,weightVector,numberOfSamples);
        }
        else if ((numberOfSamples == checkSamples) && (numberOfSamples == weightLength))
        {
          /*double calculateWeightedConditionalEntropy(double *dataVector, double *condVector, double *weightVector, int vectorLength);*/
          *output = calculateWeightedConditionalEntropy(dataVector,condVector,weightVector,numberOfSamples);
        }
        else
        {
          vectorMismatch = 1;
        }
      }
      else
      {
        columnMismatch = 1;
      }
      break;
    }/*case 3 - H(X|Y)*/
    case 4:
    {
      /*
      **I(X;Y)
      */
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);

      firstVector = mxGetPr(prhs[2]);
      secondVector = mxGetPr(prhs[3]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (checkFeatures == 1) && (weightWidth == 1))
      {
        if ((numberOfSamples == 0) || (checkSamples == 0))
        {
          *output = 0.0;
        }
        else if ((numberOfSamples == checkSamples) && (numberOfSamples == weightLength))
        {
          /*double calculateWeightedMutualInformation(double *firstVector, double *secondVector, double *weightVector, int vectorLength);*/
          *output = calculateWeightedMutualInformation(firstVector,secondVector,weightVector,numberOfSamples);
        }
        else
        {
          vectorMismatch = 1;
        }
      }
      else
      {
        columnMismatch = 1;
      }
      break;
    }/*case 4 - I(X;Y)*/
    case 5:
    {
      /*
      **I(X;Y|Z)
      */
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      thirdCheckSamples = mxGetM(prhs[4]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);
      thirdCheckFeatures = mxGetN(prhs[4]);

      firstVector = mxGetPr(prhs[2]);
      targetVector = mxGetPr(prhs[3]);
      condVector = mxGetPr(prhs[4]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);
      
      if ((numberOfFeatures == 1) && (checkFeatures == 1) && (weightWidth == 1))
      {
        if ((numberOfSamples == 0) || (checkSamples == 0))
        {
          *output = 0.0;
        }
        else if ((numberOfSamples == checkSamples) && (numberOfSamples == weightLength))
        {
          if ((thirdCheckSamples == 0) || (thirdCheckFeatures != 1))
          {
            *output = calculateWeightedMutualInformation(firstVector,targetVector,weightVector,numberOfSamples);
          }
          else if (numberOfSamples == thirdCheckSamples)
          {
            /*double calculateWeightedConditionalMutualInformation(double *firstVector, double *targetVector, double *condVector, double *weightVector, int vectorLength);*/
            *output = calculateWeightedConditionalMutualInformation(firstVector,targetVector,condVector,weightVector,numberOfSamples);
          }
          else
          {
            vectorMismatch = 1;
          }
        }
        else
        {
          vectorMismatch = 1;
        }
      }
      else
      {
        columnMismatch = 1;
      }
      break;
    }/*case 5 - I(X;Y|Z)*/
    case 6:
    {
      /*
      **calculateWeightedProbability
      */
      numberOfSamples = mxGetM(prhs[2]);
      dataVector = (double *) mxGetPr(prhs[2]);

      /*WeightedProbabilityState calculateWeightedProbability(double *dataVector, double *weightVector, int vectorLength);*/
      state = calculateWeightedProbability(dataVector,weightVector,numberOfSamples);
      
      plhs[0] = mxCreateDoubleMatrix(state.numStates,1,mxREAL);
      plhs[1] = mxCreateDoubleMatrix(state.numStates,1,mxREAL);
      plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);
      weightOutput = (double *)mxGetPr(plhs[1]);
      numStates = (double *) mxGetPr(plhs[2]);
      
      *numStates = state.numStates;
      
      for (i = 0; i < state.numStates; i++)
      {
        output[i] = state.probabilityVector[i];
        weightOutput[i] = state.stateWeightVector[i];
      }
      
      break;
    }/*case 6 - calculateWeightedProbability*/
    case 7:
    {
      /*
      **calculateWeightedJointProbability
      */
      numberOfSamples = mxGetM(prhs[2]);
      firstVector = (double *) mxGetPr(prhs[2]);
      secondVector = (double *) mxGetPr(prhs[3]);

      /*JointProbabilityState calculateJointProbability(double *firstVector, double *secondVector, double *weightVector, int vectorLength);*/
      jointState = calculateWeightedJointProbability(firstVector,secondVector,weightVector,numberOfSamples);
      
      plhs[0] = mxCreateDoubleMatrix(jointState.numJointStates,1,mxREAL);
      plhs[1] = mxCreateDoubleMatrix(jointState.numJointStates,1,mxREAL);
      plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
      plhs[3] = mxCreateDoubleMatrix(jointState.numFirstStates,1,mxREAL);
      plhs[4] = mxCreateDoubleMatrix(jointState.numFirstStates,1,mxREAL);
      plhs[5] = mxCreateDoubleMatrix(1,1,mxREAL);
      plhs[6] = mxCreateDoubleMatrix(jointState.numSecondStates,1,mxREAL);
      plhs[7] = mxCreateDoubleMatrix(jointState.numSecondStates,1,mxREAL);
      plhs[8] = mxCreateDoubleMatrix(1,1,mxREAL);

      jointOutput = (double *)mxGetPr(plhs[0]);
      jointWeight = (double *)mxGetPr(plhs[1]);
      numJointStates = (double *) mxGetPr(plhs[2]);
      firstOutput = (double *)mxGetPr(plhs[3]);
      firstWeight = (double *)mxGetPr(plhs[4]);
      numFirstStates = (double *) mxGetPr(plhs[5]);
      secondOutput = (double *)mxGetPr(plhs[6]);
      secondWeight = (double *)mxGetPr(plhs[7]);
      numSecondStates = (double *) mxGetPr(plhs[8]);
      
      *numJointStates = jointState.numJointStates;
      *numFirstStates = jointState.numFirstStates;
      *numSecondStates = jointState.numSecondStates;
      
      for (i = 0; i < jointState.numJointStates; i++)
      {
        jointOutput[i] = jointState.jointProbabilityVector[i];
        jointWeight[i] = jointState.jointWeightVector[i];
      }
      for (i = 0; i < jointState.numFirstStates; i++)
      {
        firstOutput[i] = jointState.firstProbabilityVector[i];
        firstWeight[i] = jointState.firstWeightVector[i];
      }
      for (i = 0; i < jointState.numSecondStates; i++)
      {
        secondOutput[i] = jointState.secondProbabilityVector[i];
        secondWeight[i] = jointState.secondWeightVector[i];
      }
      
      break;
    }/*case 7 - calculateWeightedJointProbability */
    default:
    {
      printf("Unrecognised flag\n");
      break;
    }/*default*/
  }/*switch(flag)*/
 
  if (columnMismatch)
  {
    printf("No columns in one or more inputs\n");
    *output = -1.0;
  }
  else if (vectorMismatch)
  {
    printf("Vector lengths do not match, they must all be the same length\n");
    *output = -1.0;
  }

  return;
}/*mexFunction()*/
