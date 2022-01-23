#include <iostream>
#include <ctime>
#include <limits>
#include "help_files.h"

int main()
 {
    const unsigned current_max=100;
    char new_word[100],dummy;
    unsigned short state=0,attempts=5,min_let=4,max_let=5;
    char dictionary[current_max][100]={"abyss","bubbly","buzz","fluff","fluffy","fizz","lucky","puffy","puzzle","shabby","zippy","antidisestablishmentarianism","chutzpah","diphthong","kitschy","larynx","naphtha","rhythmic","synthetic","zwieback"};

    while(state!=3)
     {
        std::cout<<"Start a new game![enter 1]\nSettings[enter 2]\nExit[enter 3]\n";
        std::cin>>state;
        Check_invalid_input(std::cin.fail(),state) ;
        system("CLS") ;
        switch(state)
         {
            case 1: Game(dictionary,attempts,current_max,min_let,max_let,current_max);break;
            case 2: switch(Settings() )
             {
            case 1:
                 {
                    system("CLS") ;
                    do {
                        std::cout<<"Please type your valid word...\n";
                        std::cin>>new_word;
                     }while(!Is_valid(new_word) ) ;
                    Add_word_in_dictionary(new_word,dictionary,current_max) ;
                    system("CLS") ;
                    break;
                 }
            case 2:
                 {
                    system("CLS") ;
                    std::cout<<"Current max attempts are: "<<attempts<<"\n Set max: ";
                    std::cin>>attempts;
                    while(attempts<1)
                     {
                        std::cout<<"Set max: ";
                        std::cin>>attempts;
                        Check_invalid_input(std::cin.fail(),state) ;
                     }
                    system("CLS") ;
                    break;
                 }
            case 3:
                 {
                    system("CLS") ;
                    std::cout<<"Current min length is: "<<min_let<<"\n Current max length is: "<<max_let<<"\n Set min length: ";
                    std::cin>>min_let;
                    Check_invalid_input(std::cin.fail(),min_let) ;
                    while(!Is_there_word(dictionary,min_let) )
                     {
                        std::cout<<"Sorry there was no such word , please choose a lower one\n";
                        std::cin>>min_let;
                        Check_invalid_input(std::cin.fail(),state) ;
                     }

                    std::cout<<"Set max length: ";
                    std::cin>>max_let;
                    Check_invalid_input(std::cin.fail(),max_let) ;
                    while(max_let<=min_let)
                     {
                        std::cout<<"Sorry such bounds for min and max simultaneously are not allowed\n Set min length: ";
                        std::cin>>min_let;
                        Check_invalid_input(std::cin.fail(),min_let) ;
                        std::cout<<"Set max length: ";
                        std::cin>>max_let;
                        Check_invalid_input(std::cin.fail(),max_let) ;
                     }
                    system("CLS") ;
                    break ;

                 }
            case 4:
                 {
                    system("CLS") ;
                    std::cout<<"All the words in the dictionary are: \n";
                    Dictionary_show(dictionary,current_max) ;
                    std::cout<<"Press any key and enter to continue...";
                    std::cin>>dummy;
                    system("CLS") ;

                 }
             }

         }
     }
    std::cout<<"It has been a pleasure!";

    return 0;
 }
