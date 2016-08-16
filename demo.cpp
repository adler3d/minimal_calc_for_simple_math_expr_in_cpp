#include <iostream>
#include <vector>
#include <string>
using std::string;using std::vector;
vector<string> split(const string&s,const string&needle){
  vector<string> arr;if(s.empty())return arr;size_t p=0;
  for(;;){auto pos=s.find(needle,p);if(pos==string::npos){arr.push_back(s.substr(p));return arr;}
  arr.push_back(s.substr(p,pos-p));p=pos+needle.size();}return arr;
}
string join(const vector<string>&arr,const string&glue){
  string out;size_t c=0;size_t dc=glue.size();for(size_t i=0;i<arr.size();i++){if(i)c+=dc;c+=arr[i].size();}
  for(size_t i=0;i<arr.size();i++){if(i)out+=glue;out+=arr[i];}return out;
}
string StrReplace(const string&input,const string&sub,const string&now){return join(split(input,sub),now);}
double SToF(const string&S){double r;sscanf(S.c_str(),"%lf",&r);return r;}
int SToI(const string&S){int i;sscanf(S.c_str(),"%i",&i);return i;}
string escape(const string&s){auto&f=StrReplace;return f(f(f(f(s,"*-","*`"),"/-","/`"),"/+","/"),"*+","*");}
string unescape(const string&s){return StrReplace(s,"`","-");}
#define RET_LINE(real,SToF,OPER,fromstr_LD,fromstr_LN)real fromstr_LD(const string&s,const real&ref){\
  if(s.empty())return 0;\
  auto a=split(s,#OPER);real v=fromstr_LN(a[0],ref);for(int i=1;i<a.size();i++)(v)OPER##=fromstr_LN(a[i],ref);return v;\
}
#define EXPR_FROM_STR(real,SToF)\
real fromstr_LN(const string&s,const real&ref){return s.empty()?0:SToF(unescape(s));}\
RET_LINE(real,SToF,/,fromstr_LD,fromstr_LN);\
RET_LINE(real,SToF,*,fromstr_LM,fromstr_LD);\
RET_LINE(real,SToF,-,fromstr_LS,fromstr_LM);\
RET_LINE(real,SToF,+,fromstr_LA,fromstr_LS);\
void fromstr(real&ref,const string&s){ref=fromstr_LA(escape(s),ref);}
//---
EXPR_FROM_STR(double,SToF);
EXPR_FROM_STR(int,SToI);
#undef EXPR_FROM_STR
#undef RET_LINE
int main(){
  string s;std::getline(std::cin,s);double d;fromstr(d,s);std::cout<<d;return 0;
}
