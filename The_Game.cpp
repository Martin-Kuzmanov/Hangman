#include <iostream>
#include <ctime>

int Str_len(const char* str)
{
    int len=0;
    while(*(str++)!='\0')
   {
     len++;
   }
   return len;
}

bool Str_equal(const char* str1,const char* str2)
{
    int len_1=Str_len(str1),len_2=Str_len(str2);
    if(len_1!=len_2) return false;
    while((len_1--)!=0)
    {
        if(*str1!=*str2) return false;
    }

    return true;
}

void Str_cpy(char *destination,const char *source)
{
    while(*(source)!='\0')
    {
      *(destination++)=*(source++);
    }
    *(destination)='\0';
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
    static constexpr double fraction = (1.0 / (32767 + 1.0)) ;  // static so we calculate it once only, constexpr so it does not change
    // evenly distribute the random number across our range
    return MIN + static_cast<int>((MAX - MIN + 1) * (PRNG(std::time(nullptr)) * fraction));
}

void Dictionary_show(const char dictionary[][100],unsigned dim)
{
    for(unsigned i=0;i<dim;i++)
    {
        if(!Str_equal(dictionary[i],""))
        {
            std::cout<<dictionary[i]<<"\n";

        }
        else
            return;
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

void Add_word_in_dictionary(const char* word,char** dictionary,const unsigned dim)
{
    for(unsigned i=0;i<dim;i++)
    {
        if(Str_equal(dictionary[i],""))
        {
            Str_cpy(dictionary[i],word);
            return;
        }
        else continue;
    }
    std::cout<<"Sorry,you have exceeded the maximum length !";

}

unsigned short Number_words(const char dictionary[][100],unsigned dim)
{
    unsigned short number=0;
    for(unsigned i=0;i<dim;i++)
    {
        if(!Str_equal(dictionary[i],"")) number++;
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
    return (let-97);
}

bool Reveal_letters(const char* orig,char* cloak,char let,unsigned dim)
{
    bool revealed=0;
    for(unsigned i=1;i<dim+1;i++)
    if(orig[i]==let)
    {
        cloak[i-1]=let;
        revealed=1;
    }

    return revealed;
}

void Game(const char dictionary[][100],unsigned attempts,unsigned min_let,unsigned max_let,unsigned dim)
{
    unsigned index;
    char guess;
    do
    {
        index=Get_random_number(0,Number_words(dictionary,dim)-1);
    }while(Str_len(dictionary[index])<min_let || Str_len(dictionary[index])>max_let);

    char* cloak=new char[Str_len(dictionary[index])];
    bool checked[25];
    for(unsigned i=0;i<25;i++)
    {
        checked[i]=0;
    }
    unsigned cloak_len=Str_len(dictionary[index])-1;
    for(unsigned i=0;i<cloak_len;i++)
    {
        cloak[i]='_';
    }
    Show_array(cloak,cloak_len);
    Show_array(dictionary[index],Str_len(dictionary[index]));

    while(Revealed(cloak,cloak_len) || attempts>0)
    {
        std::cout<<"Attempts left:"<<attempts<<". Guess the word ";
        Show_array(cloak,cloak_len);
        if(!Is_valid(guess))
        {
           // system("CLS");
            std::cout<<"Invalid letter.\n";
            continue;
        }
        if(guess<'a') guess+=32;
        if(checked[pos_let(guess)])
        {
            continue;
            // system("CLS");
        }
        if(!Reveal_letters(dictionary[index],cloak,guess,cloak_len))  attempts--;
        checked[pos_let(guess)]=1;
       //  system("CLS");

    }


    delete[] cloak;
}

int main()
{
    const unsigned current_max=100;
    unsigned attempts=5,min_let=5,max_let=7;
    unsigned short state=0;
    char dictionary[current_max][100]={"Eabyss","Ebubbly","Ebuzz","Efluff","Efluffy","Efizz","Elucky","Epuffy","Epuzzle","Eshabby","Ezippy","Hantidisestablishmentarianism","Hchutzpah","Hdiphthong","Hkitschy","Hlarynx","Hnaphtha","Hrhythmic","Hsynthetic","Hzwieback"};

  //  Dictionary_init(dictionary,current_max);
   // Dictionary_show(dictionary,current_max);
  while(state!=3)
    {
    std::cout<<"Start a new game![type 1]\nSettings[type 2]\nExit[type 3]\n";
    std::cin>>state;
    switch(state)
    {
        case 1: Game(dictionary,attempts,min_let,max_let,current_max);break;

    }
    }
    std::cout<<"It has been a pleasure!";



    return 0;
}
