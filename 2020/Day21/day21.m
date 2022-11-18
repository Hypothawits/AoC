clear;
filename = "input.txt";
inputLines = splitlines(fileread(filename));

input_data = {};

for line_num=1:length(inputLines)
    line = inputLines{line_num};
    mask = line == ')' | line == '(';
    line = line(~mask);
    
    %disp(line) 
    
    ingreds_allos = split(line,'contains');
    ingreds = ingreds_allos{1};
    allos = ingreds_allos{2};
    
    mask = allos == ' ';
    allos = allos(~mask);
    
    ingreds = split(ingreds,' ');
    allos = split(allos,',');
    
    input_data{line_num} = {ingreds(1:length(ingreds)-1), allos};
end

%create list_of_allos
allo_list =[" ", " "];
i = 1;
for line_num=1:length(input_data)
    % input_data{line num}{ingred or allo}{ingred/allow num}
    for allo_num=1:length(input_data{line_num}{2})
        in = input_data{line_num}{2}{allo_num};
    
        allo_list{i} = in;
        i = i+1;
    end
end
allo_list = unique(allo_list);

%create list_of_ingreds
ingreds_list =[" ", " "];
i = 1;
for line_num=1:length(input_data)
    % input_data{line num}{ingred or allo}{ingred/allow num}
    for ingreds_num=1:length(input_data{line_num}{1})
        in = input_data{line_num}{1}{ingreds_num};
    
        ingreds_list{i} = in;
        i = i+1;
    end
end
ingreds_list = unique(ingreds_list);


col = length(ingreds_list);
row = length(inputLines);

% matrix of ingredient data
ingred_matrix = zeros(row, col);

% matrix of allogens data
col = length(allo_list);
allo_matrix = zeros(row, col);


%create enum

ingr_map=containers.Map;
i = 1;
for ingre=ingreds_list
    
    ingr_map(ingre) = i;
    i = i+1;
end

allo_map=containers.Map;
i = 1;
for allo=allo_list
    
    allo_map(allo) = i;
    i = i+1;
end



% fill the matrix
for line_num=1:length(input_data)
    for ingreds_num=1:length(input_data{line_num}{1})
        % input_data{line num}{ingred or allo}{ingred/allow num}
        in = input_data{line_num}{1}{ingreds_num};
        x = ingr_map(in);
        ingred_matrix(line_num, x) = 1;
    end
end

for line_num=1:length(input_data)
    for ingreds_num=1:length(input_data{line_num}{2})
        % input_data{line num}{ingred or allo}{ingred/allow num}
        in = input_data{line_num}{2}{ingreds_num};
        x = allo_map(in);
        allo_matrix(line_num, x) = 1;
    end
end


foundPairs = cell(1, length(allo_list));
foundCount = 1;
col_found  = zeros(1, length(ingreds_list)) == 1;
allo_found = zeros(1, length(allo_list)) == 1;

while foundCount <= length(allo_list)
	for allo_index = 1:length(allo_list)
        if ~allo_found(allo_index)
            select = (allo_matrix(:,allo_index) == 1);   % convert allo value to logic mask
            extract = ingred_matrix(select, :);     % extract just the rows that contain allo "select"

            prod = cumprod(extract, 1, 'reverse');  % bit & columns together
            prod = prod(1,:);                       % take final result (the first row)    

            % add logic here to set-zero columns that have been found already!
            prod = logical( prod .* ~col_found);

            check = sum(prod);
            if(check == 1)
                % found only 1! therefore allo select must equal index of this
                ingreds_index_found = find(prod);
                col_found(ingreds_index_found)  = 1;
                allo_found(allo_index)          = 1;
                foundPairs{foundCount} = {allo_list(allo_index), ingreds_list(ingreds_index_found)};
                foundCount = foundCount +1;
            elseif (check > 1)
                % cant find this one yet!
            else
                disp("error: no result found?")
            end
        end
	end 
end



% create list of ingredients that contain allergens
allo_ingredient_list = [" " " "];
for i = 1:length(foundPairs)
    item = foundPairs{i}{2};
    allo_ingredient_list(i) = item;
end

non_allo_ingredient_list = ingreds_list;
for i = allo_ingredient_list
    non_allo_ingredient_list = non_allo_ingredient_list(non_allo_ingredient_list ~= i);
end

disp("found this many non-allergen ingredients")
disp( length(non_allo_ingredient_list) );

% count how many times they appear in the stuff

% count how many times everything appears
count = zeros(1, length(ingreds_list) );
for line_num=1:length(input_data)
    for ingreds_num=1:length(input_data{line_num}{1})
        % input_data{line num}{ingred or allo}{ingred/allow num}
        in = input_data{line_num}{1}{ingreds_num};
        x = ingr_map(in);
        count(x) = count(x) +1;
    end
end

% sum the ones we care about
sum = 0;
for ingre=non_allo_ingredient_list
    ingre_index = ingr_map(ingre);
    sum = sum + count(ingre_index);
end

disp("final result")
disp(sum)
% part 2



