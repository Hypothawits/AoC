function main()
  %clear;
  fid = fopen ("input.txt");
  % save full lines into a new file if only chars inside


  % Read in data (line by line)
  i = 1;
  lineRead = true;
  while (lineRead)
    newLine = fgetl (fid);
    
    if (newLine == -1)
      lineRead = false;
    else
      txtread{i} = newLine;
      i = i+1;
    end
  end
  fclose (fid);

  contains = @(str, pattern) ~cellfun('isempty', strfind(str, pattern));

  
  %for i = 1:numel(txtread)
  %mapChar = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
  for i = 1:numel(txtread)
    lengths = [];
    
    [input] = strsplit (txtread{i}, ' | ');
    code = strsplit (input{2}, ' ');
    input = strsplit (input{1}, ' ');
    
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    lengths;
   
    % Find the easy ones
    [OneSymbol,  input, lengths] = findOne(input, lengths);
    [FourSymbol,  input, lengths] = findFour(input, lengths);
    [SevenSymbol,  input, lengths] = findSeven(input, lengths);
    [EightSymbol,  input, lengths] = findEight(input, lengths);
        
    %Order must be 906352
    %Find 9 symbol
    [NineSymbol,  input] = findNine(input, SevenSymbol, FourSymbol);
    %Find 0 symbol
    [ZeroSymbol,  input] = findZero(input, SevenSymbol, FourSymbol);
    %Find 6 symbol
    [SixSymbol,  input, lengths] = findSix(input);
    %find 3 symbol
    [ThreeSymbol,  input] = findThree(input, SevenSymbol, FourSymbol);
    %find 5 symbol
    [FiveSymbol,  input] = findFive(input, FourSymbol);
    %find 2 symbol
    [TwoSymbol,  input] = findTwo(input);
    
    symbolList = {OneSymbol, TwoSymbol, ThreeSymbol, FourSymbol, FiveSymbol, SixSymbol, SevenSymbol, EightSymbol, NineSymbol, ZeroSymbol };
    
    %Decode the codes...
    code_string = "";
    for c = 1:numel(code)
      [one]   = symbolMatch(code{c}, OneSymbol);
      [two]   = symbolMatch(code{c}, TwoSymbol);
      [three] = symbolMatch(code{c}, ThreeSymbol);
      [four]  = symbolMatch(code{c}, FourSymbol);
      [five]  = symbolMatch(code{c}, FiveSymbol);
      [six]   = symbolMatch(code{c}, SixSymbol);
      [seven] = symbolMatch(code{c}, SevenSymbol);
      [eight] = symbolMatch(code{c}, EightSymbol);
      [nine]  = symbolMatch(code{c}, NineSymbol);
      [zero]  = symbolMatch(code{c}, ZeroSymbol);
    
##    printValue(one, two, three, four, five, six, seven, eight, nine, zero);
      if one
        code_string = [code_string '1'];
      endif
      if two
       code_string = [code_string '2'];
      endif
      if three
        code_string = [code_string '3'];
      endif
      if four
        code_string = [code_string '4'];
      endif
      if five
        code_string = [code_string '5'];
      endif
      if six
        code_string = [code_string '6'];
      endif
      if seven
        code_string = [code_string '7'];
      endif
      if eight
        code_string = [code_string '8'];
      endif
      if nine
        code_string = [code_string '9'];
      endif
      if zero
        code_string = [code_string '0'];
      end
    
    endfor
    code_int = str2double(code_string);
    %disp (code_int);
    results(i) = code_int;

  end

  disp(results);
  disp("SUM");
  disp(sum(results));
end


function [out] = symbolMatch(input, symbol)
  if ( ~(length(input) == length(symbol)) )
    out = false;
    return;
  end
  
  out = true;
  for i = 1:length(symbol)
    if( ~any(input == symbol(i)) )
      out = false;
      return;
    endif
  endfor
  return;
end

function [out,  input, lengths] = findEight (input, lengths)
    EightSymbol = input{lengths == 7};
    input(lengths == 7) = [];
    lengths = [];
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    out = EightSymbol;
end

function [out,  input, lengths] = findSeven(input, lengths)
    SevenSymbol = input{lengths == 3};
    input(lengths == 3) = [];
    lengths = [];
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    out = SevenSymbol;
end
  

function [out,  input, lengths] = findFour(input, lengths)
    FourSymbol  = input{lengths == 4};
    input(lengths == 4) = [];
    lengths = [];
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    out = FourSymbol;
end

function [out,  input, lengths] = findOne(input, lengths)
    OneSymbol   = input{lengths == 2};
    input(lengths == 2) = [];
    lengths = [];
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    out = OneSymbol;
end
    
function [out,  input] = findNine(input, SevenSymbol, FourSymbol)
    for j = 1:numel(input)
      hasSeven = checkSeven(input, j, SevenSymbol);
      hasFour = checkFour(input, j, FourSymbol);
      isNine = hasSeven & hasFour;
      if(isNine && length(input{j}) == 6 )
        NineSymbol = input{j};
        indexNine = j;
        
      end
    end
    input(indexNine) = [];
    out = NineSymbol;
end

function [out,  input] = findZero(input, SevenSymbol, FourSymbol)
  for j = 1:numel(input)
      hasSeven = checkSeven(input, j, SevenSymbol);
      notFour = ~( checkFour(input, j, FourSymbol));
      isZero = hasSeven & notFour;
      if(isZero && length(input{j}) == 6 )
        ZeroSymbol = input{j};
        indexZero = j;
      end
    end
    input(indexZero) = [];
    out = ZeroSymbol;
end

function [out,  input, lengths] = findSix(input)
    lengths = [];
    for j = 1:numel(input)
      lengths(j) = length(input{j});
    end
    
    sixSymbol = input{lengths == 6};
    input(lengths == 6) = [];
    out = sixSymbol;
end

function [out,  input] = findThree(input, SevenSymbol, FourSymbol)
%find 3 symbol
    for j = 1:numel(input)
      hasSeven = checkSeven(input, j, SevenSymbol);
      isThree = hasSeven;
      if(isThree && length(input{j}) == 5 )
        threeSymbol = input{j};
        indexThree = j;
      end
    end
    input(indexThree) = [];
    out = threeSymbol;
end

function [out,  input] = findFive(input, FourSymbol)
  %find 5 symbol
    for j = 1:numel(input)
      hasFour = checkAmountOfFour(input, j, FourSymbol, 3);
      isFive = hasFour;
      if(isFive && length(input{j}) == 5 )
        fiveSymbol = input{j};
        indexFive = j;
      end
    end
    input(indexFive) = [];
    out = fiveSymbol;
end

function [out,  input] = findTwo(input)
  %find 2 symbol
    twoSymbol = input{1};
    out = twoSymbol;
end


function out = checkSeven(input, j, SevenSymbol)
  out = any(input{j} == SevenSymbol(1)) & any(input{j} == SevenSymbol(2)) & any(input{j} == SevenSymbol(3));
end

function out = checkFour(input, j, FourSymbol)
  out = any(input{j} == FourSymbol(1)) & any(input{j} == FourSymbol(2)) & any(input{j} == FourSymbol(3)) & any(input{j} == FourSymbol(4));
end

function out = checkAmountOfFour(input, j, FourSymbol, amount)
  out = (any(input{j} == FourSymbol(1)) + any(input{j} == FourSymbol(2)) + any(input{j} == FourSymbol(3)) + any(input{j} == FourSymbol(4)) ) == amount;
end


