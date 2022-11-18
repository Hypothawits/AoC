function [winner, p1_deck_out, p2_deck_out] = part2(p1_deck, p2_deck, top)

recordOfPastDecks = {{}};
SeenDecks=containers.Map;


while ( ~(isempty(p1_deck) || isempty(p2_deck)) )
    
    % check if played before
    DeckName=cat(2,char(p1_deck),':',char(p2_deck));
    if isKey(SeenDecks,DeckName)
       playedBefore = true;
    else
        SeenDecks(DeckName)=true;
        playedBefore = false;
    end
    
    if playedBefore
        p2_deck = [];
        break;
    end
    
    % get current top cards from deck
    %  and remove card from deck
    p1_card = p1_deck(1); p1_deck(1) = [];
    p2_card = p2_deck(1); p2_deck(1) = [];
        
    if length(p1_deck) >= p1_card && length(p2_deck) >= p2_card
        %make new decks
        p1_newDeck = p1_deck(1:p1_card);
        p2_newDeck = p2_deck(1:p2_card);
        
        % call recursion
        %disp("Enter Recursion")
        [winner, ~, ~] = part2(p1_newDeck, p2_newDeck, false);
        %disp("Exit Recursion")
    else
        %play normal game
        
        if(p1_card > p2_card)
            winner = "P1";
        else
            winner = "P2";
        end
        %winner = playNormalGame(p1_card, p2_card);
    end
    
    % give winner the cards
    if winner == "P1"
        p1_deck = [p1_deck, p1_card, p2_card];
    else
        p2_deck = [p2_deck, p2_card, p1_card];
    end
end % end while


if isempty(p2_deck)
    winner = "P1";
    p1_deck_out = p1_deck;
    p2_deck_out = p2_deck;
else
    winner = "P2";
    p1_deck_out = p1_deck;
    p2_deck_out = p2_deck;
end

        


end % end Function

function [playedBefore, recordOfPastDecks] = haveBeenPlayedBefore(p1_deck,p2_deck, recordOfPastDecks)

test_case = {p1_deck p2_deck};

if( ~isempty(recordOfPastDecks{1}) )
    for i = 1:length(recordOfPastDecks)
        length_p1_pastDeck = length(recordOfPastDecks{i}{1});
        length_p2_pastDeck = length(recordOfPastDecks{i}{2});
        
        length_p1_testcase = length(test_case{1});
        length_p2_testcase = length(test_case{2});
        
        
        if (length_p1_pastDeck == length_p1_testcase) && (length_p2_pastDeck == length_p2_testcase) 
            p1_match = all ( recordOfPastDecks{i}{1} == test_case{1} );
            p2_match = all ( recordOfPastDecks{i}{2} == test_case{2} );

            match = p1_match && p2_match;
        else
            match = false;
        end

        if match
            playedBefore = true;
            return
        end
    end
    
    recordOfPastDecks{length(recordOfPastDecks)+1} = test_case;

    playedBefore = false;
else
    recordOfPastDecks{1} = test_case;
    playedBefore = false;
end



end

function [doRecursion] = checkNumCardsRemaining(p1_deck,p2_deck, p1_card, p2_card)
    doRecursion = (length(p1_deck) > p1_card) && (length(p2_deck) > p2_card);
    % reddit does '>' rather than '>='
end

function [winner] = playNormalGame(p1_card, p2_card)
    winner = "P2";
    if(p1_card > p2_card)
        winner = "P1";
    end
end
