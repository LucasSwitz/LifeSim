
let rec sum n i v =
  if i = 0 then 0 
  else if (n mod i) = 0 then
     v + i + (sum n (i-1) v)
  else
    0 + (sum n (i-1) v)
    
let perfect n = 
  if (sum n (n-1) 0 = n) then 
    true
  else
    false