#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map <std::string, int> mp;
struct Assembler_instruction {
   std::string smov = "mov";
   std::string sadd = "add";
   std::string ssub = "sub";
   std::string smul = "mul";
   std::string sdiv = "div";
   std::string sand = "and";
   std::string sor = "or";
} opcode;
struct sregisters {
   std::string r1 = "r1";
   std::string r2 = "r2";
   std::string r3 = "r3";
}sreg;
int string_int(std::string str)
{

   int sum=0, j = 0;
   bool fl = false;
   if(str[j]=='-'){
   j++;
   fl = true;
   }
    while(j!= str.size())
    {
      sum = sum*10 + (str[j]-'0');
      j++;
    }
 return !fl ? sum : (-1*sum);

}
int cut_string(std::string str,int i)
{
   std::string m;
   bool fl =false;
   int sum=0, j = 0;
   if(str[i] == 'r')
      {
         while(i < str.size())
         {
            m += str[i];
            i++;
         }
         return mp[m];
      }
   if(str[i]=='-'){
   i++;
   fl = true;
   }
   while(i!=str.size())
   {
     m+=str[i];
     i++;
   }
   
    while(j!= m.size())
    {
      sum = sum*10 + (m[j]-'0');
      j++;
    }
 return !fl ? sum : (-1*sum);

}
void mull(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
      mp[r1] *= mp[r2];
    }
    else
    {
      mp[r1] *= string_int(r2);
    }
    
}
void andd(std::string str, int i)
{
   std::string r1,r2;
   while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
      mp[r1] &= mp[r2];
    }
    else
    {
      mp[r1] &= string_int(r2);
    }
    
}
void orr(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
      mp[r1] |= mp[r2];
    }
    else
    {
      mp[r1] |= string_int(r2);
    }
    
}
void divv(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
      if(mp[r2] == 0)
      std::cout << "Error " << std::endl;
      else
      mp[r1] /= mp[r2];
    }
    else
    {
       if(string_int(r2))
      mp[r1] /= string_int(r2);
      else
      std::cout << "Error " << std::endl;
    }
    
}
void subb (std::string str,int i)
{

std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
mp[r1] -= mp[r2];
    }
    else
    {
      mp[r1] -= string_int(r2);
    }
    
}
void addi(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }

   if(r2[0]=='r')
    {
      mp[r1] += mp[r2];
    }
    else
    {
      mp[r1] += string_int(r2);
    }
    
}
void cmp_reg(std::string str,int i)
{
   std::string m;
   while(str[i]!=',')
   {
     m+=str[i];
     i++;
   }
    if (m == sreg.r1) {
        mp[m] = cut_string(str, i+1);
         return;
      }
      if (m == sreg.r2) {
        mp[m] = cut_string(str, i+1);
         return;
      }
      if (m == sreg.r3) {
         
          mp[m] = cut_string(str, i+1);
         return;
         
      }


}
void dec(std::string str)
{
   std::string str1;
   for(int i = 0; i < str.size();i++)
   {
      while(str[i] != ' '){
        str1 += str[i];
        i++;
      }
      if (str1 == opcode.smov) {
            cmp_reg(str, i+1);
         return;
      }
      if (str1 == opcode.sadd) {
          addi(str, i+1);
         return;  
      }
      if (str1 == opcode.ssub) {
          subb(str, i+1);
         return;  
      }
      if (str1 == opcode.smul) {
          mull(str, i+1);
         return;  
      }
      if (str1 == opcode.sdiv) {
          divv(str, i+1);
         return;  
      }
      if (str1 == opcode.sand) {
          andd(str, i+1);
         return;  
      }
      if (str1 == opcode.sor) {
          orr(str, i+1);
         return;  
      }
     
   }
}


int main()
{
  std::ifstream text("myCPU.txt");
  std::string str;
   
  if(!text.is_open())
  {
    std::cout << "File open error " << std::endl;
  }
 else
 {
   while(!text.eof())
   {
      getline(text,str);
      dec(str);
   }
 }
  text.close();
 return 0;
}
