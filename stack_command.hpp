template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'c'>
{
	typedef typename interpreter
		<typename mpl::push_back
			<Stack
			,typename mpl::back<Stack>::type
			>::type
		,Tmp
		,iidx
		,idx+1
		>::type type;
};

template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'s'>
{
	typedef typename interpreter
		<typename mpl::pop_back<Stack>::type
		,Tmp
		,iidx
		,idx+1
		>::type type;
};

template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'v'>
{
	typedef typename interpreter
		<typename mpl::reverse<Stack>::type
		,Tmp
		,iidx
		,idx+1
		>::type type;
};

