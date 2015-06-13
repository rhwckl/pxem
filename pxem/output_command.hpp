namespace pxem
{

#define PRINT_LIMIT 150
#define DECL_VAL(z,n,seq) vat<seq,mpl::int_<n>>::value
#define DECL_TYPE(z,n,seq) decltype(vat<seq,mpl::int_<n>>::value)
#define seq2enum(seq) BOOST_PP_ENUM(PRINT_LIMIT,DECL_VAL,seq)
#define seq2type(seq) BOOST_PP_ENUM(PRINT_LIMIT,DECL_TYPE,seq)

template<class Sequence,class N,class mpl_at=typename mpl::at<Sequence,N>::type>
struct vat : mpl_at {};

template<class Sequence,class N>
struct vat<Sequence,N,mpl::void_>
{ static constexpr int value=0; };

#define SIGN XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

template<class Sequence,typename PrintType>
struct stupid_print
{
	template<PrintType...> struct SIGN{};
	typedef typename SIGN<seq2enum(Sequence)>::have_fun print;
};

template<class Sequence>
struct stupid_print<Sequence,void>
{
#if !defined(__clang__) && defined(__GNUC__)
	static_assert
		((sizeof(Sequence),false)
		,"auto print may not work properly with gcc"
		);
#endif
	template<seq2type(Sequence)> struct SIGN{};
	typedef typename SIGN<seq2enum(Sequence)>::have_fun print;
};

template<class argc,class argv,typename PrintType,class iarg=mpl::int_<0>>
struct output_arg
	: stupid_print<typename argv::template apply<iarg>::type,PrintType>
	, output_arg<argc,argv,PrintType,typename mpl::next<iarg>::type>
{};

template<class argc,class argv,typename PrintType>
struct output_arg<argc,argv,PrintType,argc>
{};

#define PRINT_COMMAND(command,PrintType) \
template<DEFTEMPLPARAM> \
struct interpreter<DEFPARAM,com2hash(command)> \
	:mpl::if_ \
		<mpl::equal_to<typename arginterp<idx>::argc,mpl::int_<0>> \
 \
		,stupid_print<Stack,PrintType> \
 \
		,output_arg \
			<typename arginterp<idx>::argc \
			,typename mpl::lambda \
				<typename arginterp<idx>::template argv<mpl::_1>>::type \
			,PrintType \
			> \
		>::type \
{ \
	typedef typename interpreter \
		<Stack,Tmp,iidx,arginterp<idx>::next \
		>::type type; \
};

PRINT_COMMAND("p",char);
PRINT_COMMAND("pc",char);
PRINT_COMMAND("pa",void);
PRINT_COMMAND("pi",int);

#define OPRINT_COMMAND(command,PrintType) \
template<class Stack,class Tmp,int iidx,int idx> \
struct interpreter<Stack,Tmp,iidx,idx,com2hash(command)> \
{ \
	template<PrintType> struct a{}; \
	typedef typename a<mpl::back<Stack>::type::value>::have_fun print; \
	typedef typename interpreter \
		<typename mpl::pop_back<Stack>::type \
		,Tmp,iidx,arginterp<idx>::next \
		>::type type; \
};

OPRINT_COMMAND("o",char);
OPRINT_COMMAND("oc",char);
//OPRINT_COMMAND("oa",void);
OPRINT_COMMAND("oi",int);

#undef DECL
#undef PRINT_LIMIT
#undef DECL_VAL
#undef DECL_TYPE
#undef seq2enum
#undef seq2type
#undef SIGN
#undef OPRINT_COMMAND
#undef PRINT_COMMAND

} //namespace pxem

