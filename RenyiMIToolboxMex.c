/*******************************************************************************
**
**  RenyiMIToolboxMex.cpp
**  is the MATLAB entry point for the Renyi Entropy and MI MIToolbox functions 
**  when called from a MATLAB/OCTAVE script.
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
#include "RenyiEntropy.h"
#include "RenyiMutualInformation.h"

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
  ** this function takes a flag and 2 or 3 other arguments
  ** the first is a scalar alpha value, and the remainder are
  ** arrays. It returns a Renyi entropy or mutual information using the
  ** alpha divergence.
  *****************************************************************************/
  
  int flag, numberOfSamples, checkSamples, numberOfFeatures, checkFeatures;
  double alpha;
  double *dataVector, *firstVector, *secondVector, *output;
  
  /*if (nlhs != 1)
  {
    printf("Incorrect number of output arguments\n");
  }//if not 1 output
  */
  switch (nrhs)
  {
    case 3:
    {
        /*printf("Must be H_\alpha(X)\n");*/
        break;
    }
    case 4:
    {
        /*printf("Must be H_\alpha(XY), I_\alpha(X;Y)\n");*/
        break;
    }
    default:
    {
        printf("Incorrect number of arguments, format is RenyiMIToolbox(\"FLAG\",varargin)\n");
        break;
    }
  }
  
  /* number to function map
  ** 1 = H(X)
  ** 2 = H(XY)
  ** 3 = I(X;Y)
  */
  
  flag = *mxGetPr(prhs[0]);
  
  switch (flag)
  {
    case 1:
    {
      /*
      **H_{\alpha}(X)
      */
      alpha = mxGetScalar(prhs[1]);
      numberOfSamples = mxGetM(prhs[2]);
      numberOfFeatures = mxGetN(prhs[2]);
      dataVector = (double *) mxGetPr(prhs[2]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *) mxGetPr(plhs[0]);

      if (numberOfFeatures == 1)
      {
        /*double calculateRenyiEntropy(double alpha, double *dataVector, long vectorLength);*/
        *output = calculateRenyiEntropy(alpha,dataVector,numberOfSamples);
      }
      else
      {
        printf("No columns in input\n");
        *output = -1.0;
      }
      break;
    }/*case 1 - H_{\alpha}(X)*/
    case 2:
    {
      /*
      **H_{\alpha}(XY)
      */
      alpha = mxGetScalar(prhs[1]);
      
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);

      firstVector = mxGetPr(prhs[2]);
      secondVector = mxGetPr(prhs[3]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (checkFeatures == 1))
      {
        if ((numberOfSamples == 0) || (checkSamples == 0))
        {
          *output = 0.0;
        }
        else if (numberOfSamples == checkSamples)
        {
          /*double calculateJointRenyiEntropy(double alpha, double *firstVector, double *secondVector, long vectorLength);*/
          *output = calculateJointRenyiEntropy(alpha,firstVector,secondVector,numberOfSamples);
        }
        else
        {
          printf("Vector lengths do not match, they must be the same length");
          *output = -1.0;
        }
      }
      else
      {
        printf("No columns in input\n");
        *output = -1.0;
      }
      break;
    }/*case 2 - H_{\alpha}(XY)*/
    case 3:
    {
      /*
      **I_{\alpha}(X;Y)
      */
      alpha = mxGetScalar(prhs[1]);
      
      numberOfSamples = mxGetM(prhs[2]);
      checkSamples = mxGetM(prhs[3]);
      
      numberOfFeatures = mxGetN(prhs[2]);
      checkFeatures = mxGetN(prhs[3]);

      firstVector = mxGetPr(prhs[2]);
      secondVector = mxGetPr(prhs[3]);

      plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
      output = (double *)mxGetPr(plhs[0]);

      if ((numberOfFeatures == 1) && (checkFeatures == 1))
      {
        if ((numberOfSamples == 0) || (checkSamples == 0))
        {
          *output = 0.0;
        }
        else if (numberOfSamples == checkSamples)
        {
          /*double calculateRenyiMIDivergence(double alpha, double *dataVector, double *targetVector, long vectorLength);*/
          *output = calculateRenyiMIDivergence(alpha,firstVector,secondVector,numberOfSamples);
        }
        else
        {
          printf("Vector lengths do not match, they must be the same length");
          *output = -1.0;
        }
      }
      else
      {
        printf("No columns in input\n");
        *output = -1.0;
      }
      break;
    }/*case 3 - I_{\alpha}(X;Y)*/
    default:
    {
      printf("Unrecognised flag\n");
      break;
    }/*default*/
  }/*switch(flag)*/
  
  return;
}/*mexFunction()*/
