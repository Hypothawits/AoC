clear;

% Reddit solution
% [part1,part2]=reddit("input.txt");
% disp(part2)
% [32162 32534]

clear;
use_test_data = false;
[p1_input_data, p2_input_data] = inputData(use_test_data);
p1_deck = p1_input_data;
p2_deck = p2_input_data;

[winner, p1_deck_out, p2_deck_out ] = part2(p1_deck, p2_deck, true);
% [P1 32042] too low


%calc score
if winner == "P1"
    mult = length(p1_deck_out):-1:1;
    score = sum(p1_deck_out .* mult);
else
    mult = length(p2_deck_out):-1:1;
    score = sum(p2_deck_out .* mult);
end

disp("winner:")
disp(winner)
disp("Score:")
disp(score)