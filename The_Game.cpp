#include <iostream>

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

void Dictionary_init(char** dictionary,unsigned dim)
{
    for(unsigned i=0;i<dim;i++)
    Str_cpy(dictionary[i],"");
}

void Dictionary_show(const char*const *dictionary,unsigned dim)
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

void Dictionary_cpy(char** NEW,const char* const *OLD,unsigned dim)
{
    for(unsigned i=0;i<dim;i++)
    {
        Str_cpy(NEW[i],OLD[i]);
    }
}

void Extend_dictionary(char **&dictionary,unsigned &dim)
{
    dim++;
    char **temp=new char*[dim];
    for(int i=0;i<dim;i++)
    {temp[i]=new char[100];}
    Dictionary_cpy(temp,dictionary,dim);
    delete[]dictionary;
    dictionary=temp;

}

void Add_word_in_dictionary(const char* word,char** dictionary,unsigned &dim)
{
    for(unsigned i=0;i<dim;i++)
    {
        if(Str_equal(dictionary[i],""))
        {
            Str_cpy(dictionary[i],word);
            return;
        }
        else break;
    }
    Extend_dictionary(dictionary,dim);
    Add_word_in_dictionary(word,dictionary,dim);

}


int main()
{
    unsigned current_max=100;
    char **dictionary;
    dictionary=new char*[100];
    for(unsigned i=0;i<current_max;i++)
    {dictionary[i]=new char[current_max];}
    Dictionary_init(dictionary,current_max);
    Add_word_in_dictionary("cat",dictionary,current_max);
    Dictionary_show(dictionary,current_max);




    ///deleting the dictionary
    for(int i=0;i<current_max;i++)
    {delete[]dictionary[i];}
    delete[]dictionary;


    return 0;
}
