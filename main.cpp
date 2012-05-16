template<int a0=0,int a1=0,int a2=0,int a3=0,int a4=0,int a5=0,int a6=0,int a7=0,int a8=0>
struct List
{
    static const int _0=a0,_1=a1,_2=a2,_3=a3,_4=a4,_5=a5,_6=a6,_7=a7,_8=a8;
    static const int size=List<a1,a2,a3,a4,a5,a6,a7,a8,0>::size+1;
};

template<>
struct List<0,0,0,0,0,0,0,0>
{
    static const int _0=0,_1=0,_2=0,_3=0,_4=0,_5=0,_6=0,_7=0,_8=0;
    static const int size=0;
};

template<int Offset,typename L>
struct ListGet
{
    static const int n=ListGet<Offset-1,List<L::_1,L::_2,L::_3,L::_4,L::_5,L::_6,L::_7,L::_8> >::n;
};

template<typename L>
struct ListGet<0,L>
{
    static const int n=L::_0;
};

template<bool comp,int T,int F>
struct If
{
    static const int n=T;
};
template<int T,int F>
struct If<false,T,F>
{
    static const int n=F;
};


template<int Where,int Append,typename L,int R=0>
struct ListSet
{
    typedef typename ListSet<Where-1,Append,L,R+1>::type type;
};

template<int A,typename L,int R>
struct ListSet<0,A,L,R>
{
    typedef typename List<If<0==R,A,ListGet<0,L>::n>::n,
                 If<1==R,A,ListGet<1,L>::n>::n,
                 If<2==R,A,ListGet<2,L>::n>::n,
                 If<3==R,A,ListGet<3,L>::n>::n,
                 If<4==R,A,ListGet<4,L>::n>::n,
                 If<5==R,A,ListGet<5,L>::n>::n,
                 If<6==R,A,ListGet<6,L>::n>::n,
                 If<7==R,A,ListGet<7,L>::n>::n > type;
};



const int Fizz=3;
const int Buzz=5;
const int FizzBuzz=Fizz*Buzz;

template<int N,typename L,int Size,int Offset=0,bool a=0==N%Fizz,bool b=0==N%Buzz>
struct FizzBuzzList{
    typedef typename FizzBuzzList<N+1,L,Size,Offset>::t t;
    static const int end=FizzBuzzList<N+1,L,Size,Offset>::end;
};
template<int N,typename L,int Size,int Offset>
struct FizzBuzzList<N,L,Size,Offset,true,false>{
    typedef typename FizzBuzzList<N+1,typename ListSet<Offset,Fizz,L>::type,Size,Offset+1>::t t;
    static const int end=FizzBuzzList<N+1,typename ListSet<Offset,Fizz,L>::type,Size,Offset+1>::end;
};
template<int N,typename L,int Size,int Offset>
struct FizzBuzzList<N,L,Size,Offset,false,true>{
    typedef typename FizzBuzzList<N+1,typename ListSet<Offset,Buzz,L>::type,Size,Offset+1>::t t;
    static const int end=FizzBuzzList<N+1,typename ListSet<Offset,Buzz,L>::type,Size,Offset+1>::end;
};
template<int N,typename L,int Size,int Offset>
struct FizzBuzzList<N,L,Size,Offset,true,true>{
    typedef typename FizzBuzzList<N+1,typename ListSet<Offset,FizzBuzz,L>::type,Size,Offset+1>::t t;
    static const int end=FizzBuzzList<N+1,typename ListSet<Offset,FizzBuzz,L>::type,Size,Offset+1>::end;
};
//stop specialize
template<int N,typename L,int Size>struct FizzBuzzList<N,L,Size,Size,false,false>{
    static const int end=N;
    typedef typename L t;
};
template<int N,typename L,int Size>struct FizzBuzzList<N,L,Size,Size,true,false>{
    static const int end=N;
    typedef typename L t;
};
template<int N,typename L,int Size>struct FizzBuzzList<N,L,Size,Size,false,true>{
    static const int end=N;
    typedef typename L t;
};
template<int N,typename L,int Size>struct FizzBuzzList<N,L,Size,Size,true,true>{
    static const int end=N;
    typedef typename L t;
};


template<typename Pattern,int N=1,typename Expect=FizzBuzzList<N,List<>,Pattern::size>::t >
struct FizzBuzzCompare
{
    static const int begin=FizzBuzzCompare<Pattern,N+1>::begin;
};
template<int N,typename Expect>
struct FizzBuzzCompare<Expect,N,Expect>
{
    static const int begin=FizzBuzzList<N,List<>,1>::end;
};

#include <stdio.h>

template<typename L>
struct DeFizzBuzz
{
    static const int begin=FizzBuzzCompare<L>::begin-1;
    static const int end=FizzBuzzList<begin,List<>,L::size>::end-1;

    static void print(){
        printf("%d...%d\n",begin,end);
    }
};


int main()
{
    DeFizzBuzz<List<Buzz,Fizz,Fizz> >::print();
    DeFizzBuzz<List<Buzz,Fizz,FizzBuzz,Fizz> >::print();
    DeFizzBuzz<List<Fizz,Buzz,Fizz> >::print();
    DeFizzBuzz<List<Fizz,Fizz,Buzz,Fizz> >::print();
    DeFizzBuzz<List<FizzBuzz,Fizz> >::print();
    DeFizzBuzz<List<Buzz,Fizz,FizzBuzz,Fizz,Buzz> >::print();
    //DeFizzBuzzList<List<FizzBuzz,FizzBuzz> >::print();
    //DeFizzBuzzList<List<Fizz,Fizz,Fizz> >::print();
}


