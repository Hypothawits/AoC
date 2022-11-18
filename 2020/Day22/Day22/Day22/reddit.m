function [part1,part2]=reddit(filename)
    inputLines=splitlines(fileread(filename));
    Decks=cell(2);
    Player=1;
    for i=1:(length(inputLines)-2)
        if isempty(inputLines{i+Player})
            Player=2;
        else
            Decks{Player,1}=cat(2,Decks{Player,1},str2double(inputLines{i+Player}));
        end
    end
    Decks(:,2)=Decks(:,1);
    while ~(isempty(Decks{1,2})||isempty(Decks{2,2}))
        if Decks{1,2}(1)>Decks{2,2}(1)
            Decks{1,2}=cat(2,Decks{1,2}(2:end),Decks{1,2}(1),Decks{2,2}(1));
            Decks{2,2}=Decks{2,2}(2:end);
        else
            Decks{2,2}=cat(2,Decks{2,2}(2:end),Decks{2,2}(1),Decks{1,2}(1));
            Decks{1,2}=Decks{1,2}(2:end);
        end
    end
    if isempty(Decks{1,2})
        WinningDeck=Decks{2,2};
    else
        WinningDeck=Decks{1,2};
    end
    part1=sum((length(WinningDeck):-1:1).*WinningDeck);
    part2=Day22P2Recursive(Decks{1,1},Decks{2,1},true);
end

function out=Day22P2Recursive(in1,in2,top)
    Deck1=in1;
    Deck2=in2;
    SeenDecks=containers.Map;
    while ~(isempty(Deck1)||isempty(Deck2))
        DeckName=cat(2,char(Deck1),':',char(Deck2));
        if isKey(SeenDecks,DeckName)
            Deck2=[];break;
        end
        SeenDecks(DeckName)=true;
       
        if length(Deck1)>Deck1(1)&&length(Deck2)>Deck2(1)
            P1WinsRound=Day22P2Recursive(Deck1(2:(Deck1(1)+1)),Deck2(2:(Deck2(1)+1)),false);
        else
            P1WinsRound=Deck1(1)>Deck2(1);
        end
        
        if P1WinsRound
            Deck1=cat(2,Deck1(2:end),Deck1(1),Deck2(1));
            Deck2=Deck2(2:end);
        else
            Deck2=cat(2,Deck2(2:end),Deck2(1),Deck1(1));
            Deck1=Deck1(2:end);
        end
    end % end while
    
    
    
    if ~top
        out=isempty(Deck2);
    elseif isempty(Deck2)
        out=sum((length(Deck1):-1:1).*Deck1);
    else
        out=sum((length(Deck2):-1:1).*Deck2);
    end
end

