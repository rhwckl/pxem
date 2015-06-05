#define INPUT_COMMAND(command,type_) \
template<class Stack,class Tmp,int iidx,int idx> \
struct interpreter<Stack,Tmp,iidx,idx,command> \
{ \
	typedef typename interpreter \
		<typename mpl::push_back \
			<Stack,mpl::type_<input[iidx]>>::type \
		,Tmp \
		,iidx+1 \
		,idx+1 \
		>::type type; \
};

INPUT_COMMAND('l',char_);
INPUT_COMMAND('_',int_);

