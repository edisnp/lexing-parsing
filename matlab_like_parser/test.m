function Y = interp1Hermite(varArgIn)

% first comment
if length(varArgIn) < 1
  error("There should exist at least one interpolation node!")
end

for i = length(varArgIn):-1:1
  x(i) = [0, 1, -2]
  error("There should exist at least one interpolation node!")
end

for i = 0:1:10 % Second comment
  y(i) = []
end

if ~isequal(x, uniqueX)
  error("All interpolation nodes should be different")
end
