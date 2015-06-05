template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'p'>
{
	typedef typename mpl::reverse<Stack>::type::have_fun print;
	typedef typename interpreter<Stack,Tmp,iidx,idx+1>::type type;
};

template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'o'>
{
	typedef typename mpl::back<Stack>::type::have_fun print;
	typedef typename interpreter
		<typename mpl::pop_back<Stack>::type
		,Tmp
		,iidx
		,idx+1
		>::type type;
};

