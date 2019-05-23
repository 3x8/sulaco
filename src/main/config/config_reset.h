#pragma once

#ifndef __UNIQL
# define __UNIQL_CONCAT2(x,y) x ## y
# define __UNIQL_CONCAT(x,y) __UNIQL_CONCAT2(x,y)
# define __UNIQL(x) __UNIQL_CONCAT(x,__LINE__)
#endif

// overwrite _name with data passed as arguments. This version forces GCC to really copy data
// It is not possible to use multiple RESET_CONFIGs on single line (__UNIQL limitation)
#define RESET_CONFIG(_type, _name, ...)                                 \
    static const _type __UNIQL(_reset_template_) = {                    \
        __VA_ARGS__                                                     \
    };                                                                  \
    memcpy((_name), &__UNIQL(_reset_template_), sizeof(*(_name)));      \
    /**/

// overwrite _name with data passed as arguments. GCC is allowed to set structure field-by-field
#define RESET_CONFIG_2(_type, _name, ...)                 \
    *(_name) = (_type) {                                  \
        __VA_ARGS__                                       \
    };                                                    \
    /**/
