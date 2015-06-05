template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'t'>
{
	typedef typename interpreter
		<typename mpl::pop_back<Stack>::type
		,typename mpl::push_back
			<Tmp
			,typename mpl::back<Stack>::type
			>::type
		,iidx
		,idx+1
		>::type type;
};

template<class Stack,class Tmp,int iidx,int idx>
struct interpreter<Stack,Tmp,iidx,idx,'m'>
{
	typedef typename interpreter
		<typename mpl::push_back
			<Stack
			,typename mpl::back<Tmp>::type
			>::type
		,Tmp
		,iidx
		,idx+1
		>::type type;
};

