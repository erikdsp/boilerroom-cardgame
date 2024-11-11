# Boiler Room - Simple Card Game

The focus of this project is to build a program using basic OOP, to split the program into several files and use UML to visualize the development. Use agile methods to complete the project. 

Description: A card game with basic rules, like Blackjack, where players try to reach a target score without going over

This Boiler Room is part of the Software Development education at Chas Academy.

Participants: *Erik Dahl, Jennifer Gott, Johan Modin, Sabina Stawbrink, Oscar Asserlund*


Classes:
Deck.cpp, innehåller även Card klassen
GameRules.cpp   innehåller Dealer, funktioner för input
Player.cpp  vector<Cards>, purse
Table.cpp   funktioner för output

GameRules class constructor, input int numberOfPlayers
    create Dealer, Players

En giv har en pott (som man tar ur börsen)
Man spelar given tills man antingen vinner eller förlorar given. 
Då får man en ny fråga.

Ett spel är tills börsen är slut eller spelaren är nöjd. Betyder att loop för flera spel ligger i GameRules och inte i main.

Link to |Blackjack rules] (https://bicyclecards.com/how-to-play/blackjack)


