#ifdef __clang__
char*gets(char*);
#endif

#include <boost/mpl/vector.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/equal_to.hpp>

#include <sprout/functional.hpp>
#include <sprout/string.hpp>

namespace pxem
{

namespace mpl=boost::mpl;

constexpr auto code=sprout::to_string(code_origin);
constexpr auto pos=code.rfind('/');
constexpr auto start_pos= pos==sprout::npos ? 0 : pos+1;
constexpr auto end_pos=code.rfind('.');

template<class,class,int,int idx,char command=code[idx]>
struct interpreter
{ static_assert((command,false),"unrecognized command"); };

//ignore
template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'.'>
{ typedef typename interpreter<Stack,Tmp,iidx,idx+1>::type type; };

//exit
template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'d'>
{ typedef Stack type; };

//end of code
template<class Stack,class Tmp,int iidx>
struct interpreter<Stack,Tmp,iidx,end_pos>
{ typedef Stack type; };

template<class Sequence>
struct last2
{
	typedef typename mpl::pop_back<Sequence>::type pop1;
	typedef typename mpl::pop_back<pop1>::type pop2;
	typedef typename mpl::back<Sequence>::type first_popped;
	typedef typename mpl::back<pop1>::type second_popped;
};

#include "stack_command.hpp"
#include "input_command.hpp"
#include "output_command.hpp"
#include "conditional_branch_command.hpp"
#include "temporary_memory_command.hpp"
#include "arithmetic_command.hpp"

}//namespace pxem

