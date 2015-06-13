namespace pxem
{

template<class iarg,class lambda,class BinaryOp>
struct fold : BinaryOp::template apply
	<typename fold
		<typename mpl::prior<iarg>::type
		,lambda,BinaryOp
		>::type
	,typename lambda::template apply<iarg>::type
	> {};

template<class lambda,class BinaryOp>
struct fold<mpl::int_<0>,lambda,BinaryOp>
	: lambda::template apply<mpl::int_<0>> {};


template<DEFTEMPLPARAM,class BinaryOp,class argc>
struct arithmetic_arg
{
	typedef typename mpl::lambda
		<mpl::fold
			<typename arginterp<idx>::template argv<mpl::_1>
			,mpl::int_<0>
			,typename mpl::lambda<mpl::plus<mpl::_1,mpl::_2>>::type
			>
		>::type lam;

	typedef typename fold
		<typename mpl::prior<typename arginterp<idx>::argc>::type
		,lam
		,BinaryOp
		>::type result;

	typedef typename interpreter
		<typename mpl::push_back<Stack,result>::type
		,Tmp,iidx,arginterp<idx>::next
		>::type type;
};

template<DEFTEMPLPARAM,class BinaryOp>
struct arithmetic_arg<DEFPARAM,BinaryOp,mpl::int_<1>>
{
	typedef typename interpreter
		<typename mpl::push_back
			<typename mpl::pop_back<Stack>::type
			,typename BinaryOp::template apply
				<typename mpl::back<Stack>::type
				,typename mpl::fold
					<typename arginterp<idx>::template argv<mpl::int_<0>>::type
					,mpl::int_<0>
					,mpl::plus<mpl::_1,mpl::_2>
					>::type
				>::type
			>::type
		,Tmp,iidx,arginterp<idx>::next
		>::type type;
};

template<DEFTEMPLPARAM,class BinaryOp>
struct arithmetic_arg<DEFPARAM,BinaryOp,mpl::int_<0>>
{
	typedef typename interpreter
		<typename mpl::push_back
			<typename last2<Stack>::pop2::type
			,typename BinaryOp::template apply
				<typename last2<Stack>::second_popped::type
				,typename last2<Stack>::first_popped::type
				>::type
			>::type
		,Tmp,iidx,arginterp<idx>::next
		>::type type;
};

COMMAND_APPEND("+")
{
	typedef typename arithmetic_arg
		<DEFPARAM
		,typename mpl::lambda<mpl::plus<mpl::_1,mpl::_2>>::type
		,typename arginterp<idx>::argc
		>::type type;
};

COMMAND_APPEND("-")
{
	typedef typename arithmetic_arg
		<DEFPARAM
		,typename mpl::lambda<mpl::minus<mpl::_1,mpl::_2>>::type
		,typename arginterp<idx>::argc
		>::type type;
};

COMMAND_APPEND("!")
{
	typedef typename arithmetic_arg
		<DEFPARAM
		,typename mpl::lambda<mpl::multiplies<mpl::_1,mpl::_2>>::type
		,typename arginterp<idx>::argc
		>::type type;
};

} //namespace pxem

