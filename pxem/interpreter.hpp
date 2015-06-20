#ifdef __clang__
char*gets(char*);
#endif

#include <boost/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
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
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/transform.hpp>

#include <sprout/functional.hpp>
#include <sprout/string.hpp>
#include <sprout/weed.hpp>

namespace pxem
{

namespace mpl=boost::mpl;
namespace weed=sprout::weed;

constexpr auto code=sprout::to_string(code_origin);
constexpr auto pos=code.rfind('/');
constexpr auto start_pos= pos==sprout::npos ? 0 : pos+1;
constexpr auto end_pos=code.rfind('.')+1;
constexpr auto code_len=end_pos-start_pos;

constexpr int argc_max
	= code_len < 20 ? code_len : 20;
constexpr int command_max
	= code_len < 20 ? code_len : 20;

constexpr auto command_usable_
	= weed::alpha_
	| '+' | '-' | '!' | '_' ;

static constexpr auto command_
	= +weed::lim<command_max>(command_usable_);

constexpr char strmark_='\'';
constexpr auto strmark=weed::char_(strmark_);
constexpr int strlit_max= code_len < 100 ? code_len : 100;
constexpr auto string_literal
	= strmark
	>> +(weed::lim<strlit_max> (weed::char_ - strmark_))
	>> strmark_;

constexpr auto literal= string_literal;

template <class String>
constexpr auto at(const String&str,unsigned int i) -> decltype(str.size(),'\0')
{ return i>=str.size() ? '\0' : str[i]; }

template <typename T,int N>
constexpr char at(T(&str)[N],unsigned int i)
{ return i>=N ? '\0' : str[i]; }

template<class Sequence,char c,bool>
struct char_push_back : mpl::push_back<Sequence,mpl::char_<c>> {};
 
template<class Sequence,char c>
struct char_push_back<Sequence,c,true> : Sequence {};

#define DECL1(z,n,u) typename char_push_back<
#define DECL2(z,n,str) , at(str,n),(n>=sprout::size(str)) >::type
#define STRLIT_MAX 60

#define str2seq(Sequence,str) \
	BOOST_PP_REPEAT(STRLIT_MAX,DECL1,~) \
		Sequence \
	BOOST_PP_REPEAT(STRLIT_MAX,DECL2,str)

constexpr bool isiden(char c){
	const char t[1]{c};
	return weed::parse(t,command_usable_).success();
}

template<int idx>
struct arginterp
{
	static constexpr long _next()
	{
		for(auto start=code.begin()+idx;;++start)
		{
			auto tmp=sprout::find
				(start
				,code.end()+end_pos
				,'.'
				);
			if(isiden(*(tmp+1)))
				return tmp-code.begin();

		#ifdef __clang__
			start=tmp;
		#else
			while(tmp!=start)++start;
		#endif
		}
	}
	static constexpr auto next=_next()+1;

	static constexpr auto command_with_arg
		= command_ >> '.'
		>> *weed::lim<argc_max> (weed::as_tuple[literal] >> '.');

	static constexpr auto parser=command_with_arg;
	static constexpr auto result=weed::parse
		(code.begin()+idx
		,code.begin()+next
		,parser
		);
	static_assert(result.success(),"syntax error");
	static constexpr auto _argv=result.attr();

	static constexpr int _argc()
	{
		int ret=0;
		for(auto i=_argv.begin();i!=_argv.end();++i,++ret)
			if(sprout::get<0>(*i)[0]=='\0')
				return ret;
		return ret;
	}
	typedef typename mpl::int_<_argc()> argc;

	static constexpr int argmark(int i) {
		auto mark=sprout::get<0>(result.attr()[i])[0];
		if(mark=='\'') return '\'';

		return -1;
	}

	template<class Int,int argmark_=argmark(Int::value)> struct argve
	{ static_assert((argmark_,false),"invalid arguments"); };

	template<class Int> struct argve<Int,'\''>{
		typedef typename mpl::pop_front
			<str2seq
				(mpl::vector<>
				,sprout::get<0>(result.attr()[Int::value])
				)
			>::type type;
	};

	template<class Int>
	struct argv{
		typedef typename argve<Int>::type type;
	};

};

#define DEFPARAM_(type1,type2) type1 Stack,type1 Tmp,type2 iidx,type2 idx
#define DEFPARAM DEFPARAM_(,)
#define DEFTEMPLPARAM DEFPARAM_(class,int)
#define COMMAND_APPEND(command) \
	template<DEFTEMPLPARAM> \
	struct interpreter<DEFPARAM,com2hash(command)>

template<class T> struct alias_argc { typedef T argc; };

template<class T>
constexpr auto com2hash(const T&s) 
{	return sprout::to_hash(sprout::to_string(s)); }

template
	<DEFTEMPLPARAM
	,decltype(com2hash("")) command
		= sprout::to_hash(sprout::string<command_max>
				(code.begin()+idx
				,sprout::find
					(code.begin()+idx
					,code.begin()+end_pos
					,'.'
					)
				)
			)
	>
struct interpreter
{ static_assert((command,false),"unrecognized command"); };

//exit
COMMAND_APPEND("d")
{ typedef Stack type; };

//end of code
template<class Stack,class Tmp,int iidx>
struct interpreter<Stack,Tmp,iidx,end_pos>
{ typedef Stack type; };

template<class Sequence>
struct last2
{
	typedef typename mpl::pop_back<Sequence> pop1;
	typedef typename mpl::pop_back<typename pop1::type> pop2;
	typedef typename mpl::back<Sequence> first_popped;
	typedef typename mpl::back<typename pop1::type> second_popped;
};

template
	<class Sequence1
	,class Sequence2
	,int size=mpl::size<Sequence2>::value
	>
struct push_back : push_back
		<typename mpl::push_back
			<Sequence1
			,typename mpl::front<Sequence2>::type
			>::type
		,typename mpl::pop_front<Sequence2>::type
		>
{};

template<class Sequence1,class Sequence2>
struct push_back<Sequence1,Sequence2,0>
{ typedef Sequence1 type; };

template<class Sequence1,class Sequence2>
struct joint
	: mpl::copy<Sequence2,mpl::back_inserter<Sequence1>> {};

} //namespace pxem

#include "input_command.hpp"
#include "output_command.hpp"
#include "stack_command.hpp"
#include "conditional_branch_command.hpp"
#include "temporary_memory_command.hpp"
#include "arithmetic_command.hpp"

#undef STRLIT_MAX
#undef DECL1
#undef DECL2
#undef str2seq
#undef DEFPARAM_
#undef DEFPARAM
#undef DEFTEMPLPARAM
#undef COMMAND_APPEND

