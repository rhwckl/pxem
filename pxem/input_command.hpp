#include <boost/mpl/joint_view.hpp>

namespace boost{ namespace mpl{
template<>
struct clear_impl<aux::joint_view_tag>{
	template<typename T>
	struct apply { typedef boost::mpl::vector<> type; };
};
}}

namespace pxem
{

template<class argc,class argv,class iarg=mpl::int_<0>>
struct joint_arg : mpl::joint_view
	<typename argv::template apply<iarg>::type
	,typename joint_arg
		<argc,argv
		,typename mpl::next<iarg>::type
		>::type
	> {};

template<class argc,class argv>
struct joint_arg<argc,argv,argc> : mpl::vector<> {};

template<DEFTEMPLPARAM,class to_type,class argc>
struct when_arg
{
	typedef typename interpreter
		<typename joint
			<Stack
			,typename mpl::transform
				<typename joint_arg
					<argc
					,typename mpl::lambda
						<typename arginterp<idx>::template argv<mpl::_1>>::type
					>::type
				,typename to_type::template apply<mpl::_1>
				>::type
			>::type
		,Tmp,iidx,arginterp<idx>::next
		>::type type;
};

template<class T>
struct to_char_ : mpl::char_<T::value> {};

template<class T>
struct to_int_ : mpl::int_<T::value> {};

#define INPUT_COMMAND(command,input_type) \
template<DEFTEMPLPARAM> \
struct interpreter<DEFPARAM,com2hash(command)> \
{ \
	typedef typename arginterp<idx>::argc argc; \
\
	typedef typename mpl::eval_if \
		<mpl::equal_to<argc,mpl::int_<0>> \
\
		,interpreter \
			<typename mpl::push_back \
				<Stack,mpl::input_type##_<input[iidx]>>::type \
			,Tmp \
			,iidx+1 \
			,arginterp<idx>::next \
			> \
\
		,when_arg \
			<Stack,Tmp,iidx,idx \
			,typename mpl::lambda \
				<to_##input_type##_<mpl::_1>>::type \
			,argc> \
		>::type type; \
};

INPUT_COMMAND("l",char);
INPUT_COMMAND("_",int);

#undef INPUT_COMMAND

} //namespace pxem

