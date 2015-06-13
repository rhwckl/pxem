namespace pxem
{

COMMAND_APPEND("c")
{
	typedef typename interpreter
		<typename mpl::push_back
			<Stack
			,typename mpl::back<Stack>::type
			>::type
		,Tmp
		,iidx
		,arginterp<idx>::next
		>::type type;
};

COMMAND_APPEND("s")
{
	typedef typename interpreter
		<typename mpl::pop_back<Stack>::type
		,Tmp
		,iidx
		,arginterp<idx>::next
		>::type type;
};

COMMAND_APPEND("v")
{
	typedef typename interpreter
		<typename mpl::reverse<Stack>::type
		,Tmp
		,iidx
		,arginterp<idx>::next
		>::type type;
};

} //namespace pxem

