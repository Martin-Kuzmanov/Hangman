#ifndef HELP_FILES_H_INCLUDED
#define HELP_FILES_H_INCLUDED
unsigned Str_len(const char* str)
 {
    int len=0;
    while(*(str++) !='\0')
     {
       len++;
     }
   return len;
 }

bool Str_equal(const char* str1,const char* str2)
 {
    int len_1=Str_len(str1) ,len_2=Str_len(str2) ;
    if(len_1!=len_2) return false;
    while((len_1--) !=0)
     {
        if(*str1!=*str2) return false;
     }

    return true;
 }

void Str_cpy(char *destination,const char *source)
 {
    while(*(source) !='\0')
     {
        *(destination++) =*(source++) ;
     }
    *(destination) ='\0';
 }

unsigned int PRNG(int s)
 {
    // using static to remember value mod 32768 for the next function call
    static unsigned int seed=s;

    seed = 8253729 * seed + 2396403;

    // Take the seed and return a value between 0 and 32767
    return seed % 32768;
 }

int Get_random_number(int MIN, int MAX)
 {
    double fraction = (1.0 / (32767 + 1.0) ) ;  // static so we calculate it once only, constexpr so it does not change
    // evenly distribute the random number across our range
    return MIN + ((MAX - MIN + 1) * (PRNG(std::time(nullptr)) * fraction));
 }

void Dictionary_show(const char dictionary[][100],unsigned dim)
 {
    for(unsigned i=0;i<dim;i++)
     {
        if(!Str_equal(dictionary[i],""))
         {
            std::cout<<dictionary[i]<<"\n";

         }
        else return;
     }
 }

void Show_array(const char *arr,unsigned dim)
 {
    for(unsigned i=0;i<dim;i++)
     {
        std::cout<<arr[i]<<" ";
     }
    std::cout<<"\n";
 }

void Add_word_in_dictionary(char* word,char dictionary[][100],const unsigned dim)
 {
    for(unsigned i=0;i<dim;i++)
     {
        if(Str_equal(dictionary[i],"") )
         {
            Str_cpy(dictionary[i],word) ;
            return;
         }
        else continue;
     }
    std::cout<<"Sorry,you have exceeded the maximum length of 100!";

 }

unsigned short Number_words(const char dictionary[][100],unsigned dim)
 {
    unsigned short number=0;
    for(unsigned i=0;i<dim;i++)
     {
        if(!Str_equal(dictionary[i],"") ) number++;
     }

    return number;
 }

bool Revealed(const char* str,unsigned dim)
 {
    for(unsigned i=0;i<dim;i++)
    if(str[i]=='_') return false;
    return true;
 }

bool Is_valid(char &let)
 {
    std::cin>>let;
    return (let>='A' && let<='z');
 }

unsigned short pos_let(char let)
 {
    return (let-97) ;
 }

bool Reveal_letters(const char* orig,char* cloak,char let,unsigned dim)
 {
    bool revealed=0;
    for(unsigned i=0;i<dim;i++)
    if(orig[i]==let)
     {
        cloak[i]=let;
        revealed=1;
     }

    return revealed;
 }

bool Is_there_word(const char dictionary[][100],unsigned Size,unsigned min_let,unsigned max_let)
 {
    for(unsigned i=0;i<Size;i++)
     {
        if((Str_len(dictionary[i]) ) >=min_let && (Str_len(dictionary[i]) ) <=max_let) return true;
     }

    return false;
 }

void Game(const char dictionary[][100],unsigned attempts,unsigned Size,unsigned min_let,unsigned max_let,unsigned dim)
 {
    unsigned index;
    char guess;
    char dummy;
    if(!Is_there_word(dictionary,Size,min_let,max_let) )
     {
        std::cout<<"Sorry there was no word that fits your min length and max length conditions\n";
        std::cout<<"Returning to the menu...\nPress any key and enter...";
        std::cin>>dummy;
        system("CLS") ;
        return;

     }
    do
     {
        index=Get_random_number(0,Number_words(dictionary,dim)-1) ;
     }while(Str_len(dictionary[index])<min_let || Str_len(dictionary[index])>max_let) ;

    char* cloak=new char[Str_len(dictionary[index])] ;
    bool checked[26];
    for(unsigned i=0;i<26;i++)
     {
        checked[i]=0;
     }
    unsigned cloak_len=Str_len(dictionary[index]) ;
    for(unsigned i=0;i<cloak_len;i++)
     {
        cloak[i]='_';
     }
    Show_array(cloak,cloak_len) ;
    Show_array(dictionary[index],Str_len(dictionary[index])) ;

    while(!Revealed(cloak,cloak_len) && attempts>0)
     {
        std::cout<<"Attempts left:"<<attempts<<". Guess the word ";
        Show_array(cloak,cloak_len);
        if(!Is_valid(guess) )
         {
            std::cout<<"Invalid letter.\n";
            continue;
         }
        if(guess<'a') guess+=32;
        if(checked[pos_let(guess) ])
         {
            continue;
         }
        if(!Reveal_letters(dictionary[index],cloak,guess,cloak_len)) attempts--;
        checked[pos_let(guess) ]=1;
     }
    if(Revealed(cloak,cloak_len)) std::cout<<"Congratulations for guessing the word!!!\n";
    else std::cout<<"Sorry the word was: ";
    Show_array(*(dictionary+index),cloak_len) ;
    std::cout<<"\n";
    std::cout<<"Returning to the menu...\nPress any key and enter...";
    std::cin>>dummy;
    system("CLS") ;


    delete[] cloak;
 }

bool Is_there_word(const char dictionary[][100],unsigned length)
 {
    for(unsigned i=0;i<length;i++)
     {
        if(Str_len(dictionary[i]) >=length) return true;
     }

    return false;
 }

void Check_invalid_input(bool problem,unsigned short &var2)
 {
    while(problem)
     {
        std::cin.clear() ;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n') ;
        std::cout<<"Sorry, you have entered an incorrect input, so type a valid one... \n";
        std::cin>>var2;
        problem=std::cin.fail() ;
     }
 }


unsigned short Settings()
 {
    unsigned short state=0;
    std::cout<<"[Settings:]\n 1.Add a word[enter 1]\n 2.Change attempts[enter 2]\n 3.Change word length[enter 3]\n 4.Show available words[enter 4]";
    std::cin>>state;
    Check_invalid_input(std::cin.fail(),state) ;

    return state;
 }

bool Is_valid(char* word)
 {
    unsigned len=Str_len(word) ;
    for(unsigned i=0;i<len;i++)
     {
        if(word[i]<'A' || word[i]>'z') return false;
     }

    return true;
 }




#endif // HELP_FILES_H_INCLUDED
