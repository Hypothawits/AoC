function out = getLocalNetwork (gridData)
  gridData(y, x)
  
  a = [gridData(y, x+1) gridData(y-1, x+1) gridData(y-2, x+1)]
  b = [gridData(y, x+1) gridData(y-1, x+1) gridData(y-1, x+2)]
  c = [gridData(y, x+1) gridData(y  , x+2) gridData(y-1, x+2)]
  d = [gridData(y, x+1) gridData(y  , x+2) gridData(y-1, x+2)]
  e = [gridData(y, x+1) gridData(y  , x+2) gridData(y  , x+3)]
  f = [gridData(y, x+1) gridData(y  , x+2) gridData(y+1, x+2)]
  g = [gridData(y, x+1) gridData(y  , x+2) gridData(y+1, x+2)]
  h = [gridData(y, x+1) gridData(y-1, x+1) gridData(y+1, x+2)]
  i = [gridData(y, x+1) gridData(y-1, x+1) gridData(y+2, x+1)]

  j = [gridData(y, x-1) gridData(y+1, x-1) gridData(y+2, x-1)]
  k = [gridData(y, x-1) gridData(y+1, x-1) gridData(y+1, x-2)]
  l = [gridData(y, x-1) gridData(y  , x-2) gridData(y+1, x-2)]
  m = [gridData(y, x-1) gridData(y  , x-2) gridData(y+1, x-2)]
  n = [gridData(y, x-1) gridData(y  , x-2) gridData(y  , x-3)]
  o = [gridData(y, x-1) gridData(y  , x-2) gridData(y-1, x-2)]
  p = [gridData(y, x-1) gridData(y  , x-2) gridData(y-1, x-2)]
  q = [gridData(y, x-1) gridData(y+1, x-1) gridData(y-1, x-2)]
  r = [gridData(y, x-1) gridData(y+1, x-1) gridData(y-2, x-1)]


  s = [gridData(y+1, x) gridData(y+1, x-1) gridData(y+1, x-2)]
  t = [gridData(y+1, x) gridData(y+1, x-1) gridData(y+2, x-1)]
  u = [gridData(y+1, x) gridData(y+2, x  ) gridData(y+2, x-1)]
  v = [gridData(y+1, x) gridData(y+2, x  ) gridData(y+2, x-1)]
  w = [gridData(y+1, x) gridData(y+2, x  ) gridData(y+3, x  )]
  xx = [gridData(y+1, x) gridData(y+2, x  ) gridData(y+2, x+1)]
  yy = [gridData(y+1, x) gridData(y+2, x  ) gridData(y+2, x+1)]
  z = [gridData(y+1, x) gridData(y+1, x-1) gridData(y+2, x+1)]
  zz = [gridData(y+1, x) gridData(y+1, x-1) gridData(y+1, x+2)]

  za = [gridData(y-1, x) gridData(y-1, x+1) gridData(y-1, x+2)]
  zb = [gridData(y-1, x) gridData(y-1, x+1) gridData(y-2, x+1)]
  zc = [gridData(y-1, x) gridData(y-2, x  ) gridData(y-2, x+1)]
  zd = [gridData(y-1, x) gridData(y-2, x  ) gridData(y-2, x+1)]
  ze = [gridData(y-1, x) gridData(y-2, x  ) gridData(y-3, x  )]
  zf = [gridData(y-1, x) gridData(y-2, x  ) gridData(y-2, x-1)]
  zg = [gridData(y-1, x) gridData(y-2, x  ) gridData(y-2, x-1)]
  zh = [gridData(y-1, x) gridData(y-1, x+1) gridData(y-2, x-1)]
  zi = [gridData(y-1, x) gridData(y-1, x+1) gridData(y-1, x-2)]

  possible_paths = [a  ; b  ; c  ; d  ; e  ; f  ; g  ; h  ; i  ; j  ; k  ; l  ; m  ; n  ; o  ; p  ; q  ; r  ; s  ; t  ; u  ; v  ; w  ; xx ; yy ; z  ; zz ; za ; zb ; zc ; zd ; ze ; zf ; zg ; zh ; zi]
  temp = sum(possible_paths, 2)
  min(temp)
endfunction
