# pxem
compile-time interpreter of pxem

compile: (Boost and Sprout library are needed)
```
$ clang++ -std=c++14 hello_world/*.hpp
```
output:
```
In file included from hello_world/lllllllllllllp.hpp:5:
In file included from hello_world/../interpreter.hpp:61:
examples/../output_command.hpp:4:46: error: no type named 'have_fun' in 'boost::mpl::v_item<mpl_::char_<'h'>, boost::mpl::v_item<mpl_::char_<'e'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'o'>, boost::mpl::v_item<mpl_::char_<','>, boost::mpl::v_item<mpl_::char_<' '>, boost::mpl::v_item<mpl_::char_<'w'>, boost::mpl::v_item<mpl_::char_<'o'>, boost::mpl::v_item<mpl_::char_<'r'>, boost::mpl::v_item<mpl_::char_<'l'>, boost::mpl::v_item<mpl_::char_<'d'>, boost::mpl::v_item<mpl_::char_<'!'>, boost::mpl::vector0<mpl_::na>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>, 0>'
        typedef typename mpl::reverse<Stack>::type::have_fun print;
                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
                       ^
etc, etc...

hello_world/lllllllllllllp.hpp:7:1: error: static_assert failed "pxem end"
static_assert(false,"pxem end");
^             ~~~~~
2 errors generated.

```

Have fun!

