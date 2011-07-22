function output = h(X)
%function output = h(X)
%X can be a matrix which is converted into a joint variable before calculation
%expects variables to be column-wise
%
%returns the entropy of X, H(X)

if (size(X,2)>1)
	mergedVector = MIToolboxMex(3,X);
else
	mergedVector = X;
end
[output] = MIToolboxMex(4,mergedVector);
