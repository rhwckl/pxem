#define ARITHMETIC_COMMAND(command,expr1,expr2) \
template<class Stack,class Tmp,int iidx,int idx> \
struct interpreter<Stack,Tmp,iidx,idx,command> \
{ \
	typedef last2<Stack> tmp; \
	typedef typename interpreter \
		<typename mpl::push_back \
			<typename tmp::pop2 \
			,expr1,expr2 \
			>::type \
		,Tmp \
		,iidx \
		,idx+1 \
		>::type type; \
};

ARITHMETIC_COMMAND
	('+'
	,typename mpl::plus
		<typename tmp::second_popped
		,typename tmp::first_popped
		>::type
	);

ARITHMETIC_COMMAND
	('-'
	,typename mpl::minus
		<typename tmp::second_popped
		,typename tmp::first_popped
		>::type
	);

ARITHMETIC_COMMAND
	('!'
	,typename mpl::multiplies
		<typename tmp::second_popped
		,typename tmp::first_popped
		>::type
	);

