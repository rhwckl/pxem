namespace pxem
{

COMMAND_APPEND("t")
{
	typedef typename interpreter
		<typename mpl::pop_back<Stack>::type
		,typename mpl::push_back
			<Tmp
			,typename mpl::back<Stack>::type
			>::type
		,iidx
		,arginterp<idx>::next
		>::type type;
};

COMMAND_APPEND("m")
{
	typedef typename interpreter
		<typename mpl::push_back
			<Stack
			,typename mpl::back<Tmp>::type
			>::type
		,Tmp
		,iidx
		,arginterp<idx>::next
		>::type type;
};

} //namespace pxem

