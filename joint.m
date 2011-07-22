function output = joint(X,arities)
%function output = joint(X,arities)
%returns the joint random variable of the matrix X
%assuming the variables are in columns
%
%if passed a vector of the arities then it produces a correct
%joint variable, otherwise it may not include all states
%
%if the joint variable is only compared with variables using the same samples,
%then arity information is not required

if (nargin == 2)
  [output] = MIToolboxMex(3,X,arities);
else
  [output] = MIToolboxMex(3,X);
end
