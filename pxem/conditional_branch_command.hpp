namespace pxem
{

template
	<class InputIterator
	,class UnaryPredicateLeft
	,class UnaryPredicateRight
	>
constexpr InputIterator matching_position
	(InputIterator begin
	,InputIterator end
	,UnaryPredicateLeft pred_left
	,UnaryPredicateRight pred_right
	)
{
	for(int n=0;begin!=end;++begin){
		if(pred_left(*begin))
			++n;

		else if(pred_right(*begin)){
			--n;
			if(!n) return begin;
		}
	}

	return end;
}

struct equal_in
{
	template<class T,class...U>
	constexpr bool operator()(T a,T first,U...args)const
	{ return a==first ? true : operator()(a,args...); }

	template<class T>
	constexpr bool operator()(T a)const
	{ return false; }
};

namespace ph=sprout::placeholders;

COMMAND_APPEND("a")
{
	typedef typename interpreter
		<Stack
		,Tmp
		,iidx
		,matching_position
			(code.rbegin()+(code.size()-idx-1)
			,code.rend()
			,sprout::cbind
				(sprout::equal_to<>{}
				,ph::_1
				,'a'
				)
			,sprout::cbind
				(equal_in{}
				,ph::_1
				,'w','x','y','z'
				)
			).base()-code.begin()-1
		>::type type;
};

template<class Stack,class Tmp,int iidx,int idx,bool>
struct branch
{
	typedef typename interpreter
		<Stack
			,Tmp
			,iidx
			,arginterp<idx>::next
		>::type type;
};

template<class Stack,class Tmp,int iidx,int idx>
struct branch<Stack,Tmp,iidx,idx,true>
{
	static constexpr int matching_a=matching_position
		(code.begin()+idx
		,code.end()
		,sprout::cbind
			(equal_in{}
			,ph::_1
			,'w','x','y','z'
			)
		,sprout::cbind
			(sprout::equal_to<>{}
			,ph::_1
			,'a'
			)
		)-code.begin();

	typedef typename interpreter
		<Stack
		,Tmp
		,iidx
		,arginterp<matching_a>::next
		>::type type;
};

COMMAND_APPEND("w")
{
	typedef typename branch
		<typename mpl::pop_back<Stack>::type
		,Tmp,iidx,idx
		,mpl::back<Stack>::type::value==0
		>::type type;
};

#define CONDITIONAL_BRANCH_COMMAND(command,op) \
COMMAND_APPEND(command) \
{ \
	typedef last2<Stack> tmp; \
	typedef typename branch \
		<typename tmp::pop2::type \
		,Tmp,iidx,idx \
		,mpl::op \
			<typename tmp::second_popped::type \
			,typename tmp::first_popped::type \
			>::type::value \
		>::type type; \
};

CONDITIONAL_BRANCH_COMMAND("x",greater);
CONDITIONAL_BRANCH_COMMAND("y",less);
CONDITIONAL_BRANCH_COMMAND("z",equal_to);

#undef CONDITIONAL_BRANCH_COMMAND

} //namespace pxem

