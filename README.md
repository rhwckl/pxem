# pxem
compile-time interpreter of pxem

compile: (Boost and Sprout library are needed)
```
$ clang++ -std=c++14 example/hello_world/*.hpp
```
or
```
$ g++ -std=c++14 example/hello_world/*.hpp
```
output:
```
In file included from example/hello_world/p.'Hello, World!'.hpp:5:
In file included from example/hello_world/../../pxem/interpreter.hpp:234:
example/hello_world/../../pxem/output_command.hpp:23:45: error: no type named 'have_fun' in 'pxem::stupid_print<boost::mpl::v_item<mpl_::char_<'!'>, boost::mpl::v_item<mpl_::char_<' '>, boost::mpl::v_item<mpl_::char_<'d'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'r'>, boost::mpl::v_item<mpl_::char_<'o'>, boost::mpl::v_item<mpl_::char_<'W'>, boost::mpl::v_item<mpl_::char_<' '>, boost::mpl::v_item<mpl_::char_<','>, boost::mpl::v_item<mpl_::char_<'o'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'e'>, boost::mpl::v_item<mpl_::char_<'H'>, boost::mpl::vector<mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, char>::XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
<'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>'
        typedef typename SIGN<seq2enum(Sequence)>::have_fun print;
                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
                       ^

(etc,etc...)

example/hello_world/p.'Hello, World!'.hpp:7:1: error: static_assert failed "pxem end"
static_assert(false,"pxem end");
^             ~~~~~
2 errors generated.

```

Have fun!

