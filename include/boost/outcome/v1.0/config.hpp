/* config.hpp
Configure Boost.Outcome with Boost.APIBind
(C) 2015 Niall Douglas http://www.nedprod.com/
File Created: August 2015


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

//! \file config.hpp Configures a compiler environment for Outcome header code

//! \defgroup config Configuration macros

#define BOOST_OUTCOME_CONFIGURED

// Pull in detection of __MINGW64_VERSION_MAJOR
#ifdef __MINGW32__
#include <_mingw.h>
#endif

#include "../boost-lite/include/config.hpp"

#ifndef __cpp_attributes
#error Boost.Outcome needs attributes support in the compiler
#endif
#ifndef __cpp_variadic_templates
#error Boost.Outcome needs variadic template support in the compiler
#endif
#ifndef __cpp_constexpr
#error Boost.Outcome needs constexpr (C++ 11) support in the compiler
#endif
#ifndef __cpp_variable_templates
#error Boost.Outcome needs variable template support in the compiler
#endif
#ifndef __cpp_generic_lambdas
#error Boost.AFIO needs generic lambda support in the compiler
#endif


#include "../boost-lite/include/import.h"
#undef BOOST_OUTCOME_V1_STL11_IMPL
#undef BOOST_OUTCOME_V1_ERROR_CODE_IMPL
#undef BOOST_OUTCOME_V1
#undef BOOST_OUTCOME_V1_NAMESPACE
#undef BOOST_OUTCOME_V1_NAMESPACE_BEGIN
#undef BOOST_OUTCOME_V1_NAMESPACE_END

// Default to the C++ 11 STL for atomic, chrono, mutex and thread except on Mingw32
#if(defined(BOOST_OUTCOME_USE_BOOST_THREAD) && BOOST_OUTCOME_USE_BOOST_THREAD) || (defined(__MINGW32__) && !defined(__MINGW64__) && !defined(__MINGW64_VERSION_MAJOR))
#define BOOST_OUTCOME_V1_STL11_IMPL boost
#ifndef BOOST_THREAD_VERSION
#define BOOST_THREAD_VERSION 3
#endif
#if BOOST_THREAD_VERSION < 3
#error Boost.Outcome requires that Boost.Thread be configured to v3 or later
#endif
#else
//! \brief The C++ 11 STL to use (std|boost). Defaults to std. \ingroup config
#define BOOST_OUTCOME_V1_STL11_IMPL std
#ifndef BOOST_OUTCOME_USE_BOOST_THREAD
//! \brief Whether to use Boost.Thread instead of the C++ 11 STL `std::thread`. Defaults to the C++ 11 STL thread. \ingroup config
#define BOOST_OUTCOME_USE_BOOST_THREAD 0
#endif
#endif
#if BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#define BOOST_OUTCOME_V1_ERROR_CODE_IMPL boost
#else
//! \brief The C++ 11 `error_code` to use (std|boost). Defaults to std. \ingroup config
#define BOOST_OUTCOME_V1_ERROR_CODE_IMPL std
#endif

#ifdef BOOST_OUTCOME_UNSTABLE_VERSION
#include "../revision.hpp"
#define BOOST_OUTCOME_V1 (boost), (outcome), (BOOSTLITE_BIND_NAMESPACE_VERSION(, BOOST_OUTCOME_NAMESPACE_VERSION, BOOST_OUTCOME_V1_STL11_IMPL, BOOST_OUTCOME_V1_ERROR_CODE_IMPL, BOOST_OUTCOME_PREVIOUS_COMMIT_UNIQUE), inline)
#elif BOOST_OUTCOME_LATEST_VERSION == 1
#define BOOST_OUTCOME_V1 (boost), (outcome), (BOOSTLITE_BIND_NAMESPACE_VERSION(, BOOST_OUTCOME_NAMESPACE_VERSION, BOOST_OUTCOME_V1_STL11_IMPL, BOOST_OUTCOME_V1_ERROR_CODE_IMPL), inline)
#else
#define BOOST_OUTCOME_V1 (boost), (outcome), (BOOSTLITE_BIND_NAMESPACE_VERSION(, BOOST_OUTCOME_NAMESPACE_VERSION, BOOST_OUTCOME_V1_STL11_IMPL, BOOST_OUTCOME_V1_ERROR_CODE_IMPL))
#endif
/*! \def BOOST_OUTCOME_V1
\ingroup config
\brief The namespace configuration of this Boost.Outcome v1. Consists of a sequence
of bracketed tokens later fused by the preprocessor into namespace and C++ module names.
*/
#if DOXYGEN_SHOULD_SKIP_THIS
//! The Boost namespace
namespace boost
{
  //! The Outcome namespace
  namespace outcome
  {
    //! Inline namespace for this version of Outcome
    inline namespace v1_xxx
    {
    }
  }
}
/*! \brief The namespace of this Boost.Outcome v1 which will be some unknown inline
namespace starting with `v1_` inside the `boost::afio` namespace.
\ingroup config
*/
#define BOOST_OUTCOME_V1_NAMESPACE boost::outcome::v1_xxx
/*! \brief Expands into the appropriate namespace markup to enter the Outcome v1 namespace.
\ingroup config
*/
#define BOOST_OUTCOME_V1_NAMESPACE_BEGIN                                                                                                                                                                                                                                                                                       \
  namespace boost                                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    namespace outcome                                                                                                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                                                                                          \
      inline namespace v1_xxx                                                                                                                                                                                                                                                                                                  \
      {
/*! \brief Expands into the appropriate namespace markup to enter the C++ module
exported Outcome v1 namespace.
\ingroup config
*/
#define BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN                                                                                                                                                                                                                                                                                \
  export namespace boost                                                                                                                                                                                                                                                                                                       \
  {                                                                                                                                                                                                                                                                                                                            \
    namespace outcome                                                                                                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                                                                                          \
      inline namespace v1_xxx                                                                                                                                                                                                                                                                                                  \
      {
/*! \brief Expands into the appropriate namespace markup to exit the Outcome v1 namespace.
\ingroup config
*/
#define BOOST_OUTCOME_V1_NAMESPACE_END                                                                                                                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  }                                                                                                                                                                                                                                                                                                                            \
  }
#elif defined(GENERATING_OUTCOME_MODULE_INTERFACE)
#define BOOST_OUTCOME_V1_NAMESPACE BOOSTLITE_BIND_NAMESPACE(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_BEGIN BOOSTLITE_BIND_NAMESPACE_BEGIN(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN BOOSTLITE_BIND_NAMESPACE_EXPORT_BEGIN(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_END BOOSTLITE_BIND_NAMESPACE_END(BOOST_OUTCOME_V1)
#else
#define BOOST_OUTCOME_V1_NAMESPACE BOOSTLITE_BIND_NAMESPACE(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_BEGIN BOOSTLITE_BIND_NAMESPACE_BEGIN(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN BOOSTLITE_BIND_NAMESPACE_BEGIN(BOOST_OUTCOME_V1)
#define BOOST_OUTCOME_V1_NAMESPACE_END BOOSTLITE_BIND_NAMESPACE_END(BOOST_OUTCOME_V1)
#endif

#undef BOOST_OUTCOME_NEED_DEFINE
#undef BOOST_OUTCOME_NEED_DEFINE_DESCRIPTION
#if !BOOST_OUTCOME_USE_BOOST_THREAD && !BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#ifndef BOOST_OUTCOME_NEED_DEFINE_00
#define BOOST_OUTCOME_NEED_DEFINE_DESCRIPTION "BOOST_OUTCOME_USE_BOOST_THREAD=0 BOOST_OUTCOME_USE_BOOST_ERROR_CODE=0"
#define BOOST_OUTCOME_NEED_DEFINE_00
#define BOOST_OUTCOME_NEED_DEFINE 1
#endif
#elif BOOST_OUTCOME_USE_BOOST_THREAD && !BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#ifndef BOOST_OUTCOME_NEED_DEFINE_10
#define BOOST_OUTCOME_NEED_DEFINE_DESCRIPTION "BOOST_OUTCOME_USE_BOOST_THREAD=1 BOOST_OUTCOME_USE_BOOST_ERROR_CODE=0"
#define BOOST_OUTCOME_NEED_DEFINE_10
#define BOOST_OUTCOME_NEED_DEFINE 1
#endif
#elif !BOOST_OUTCOME_USE_BOOST_THREAD && BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#ifndef BOOST_OUTCOME_NEED_DEFINE_01
#define BOOST_OUTCOME_NEED_DEFINE_DESCRIPTION "BOOST_OUTCOME_USE_BOOST_THREAD=0 BOOST_OUTCOME_USE_BOOST_ERROR_CODE=1"
#define BOOST_OUTCOME_NEED_DEFINE_01
#define BOOST_OUTCOME_NEED_DEFINE 1
#endif
#elif BOOST_OUTCOME_USE_BOOST_THREAD && BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#ifndef BOOST_OUTCOME_NEED_DEFINE_11
#define BOOST_OUTCOME_NEED_DEFINE_DESCRIPTION "BOOST_OUTCOME_USE_BOOST_THREAD=1 BOOST_OUTCOME_USE_BOOST_ERROR_CODE=1"
#define BOOST_OUTCOME_NEED_DEFINE_11
#define BOOST_OUTCOME_NEED_DEFINE 1
#endif
#endif

#ifdef BOOST_OUTCOME_NEED_DEFINE
#undef BOOST_OUTCOME_MONAD_H
#undef BOOST_OUTCOME_VALUE_STORAGE_H

#if BOOST_OUTCOME_USE_BOOST_ERROR_CODE
#include "../boost-lite/include/bind/stl11/boost/system_error"
BOOST_OUTCOME_V1_NAMESPACE_BEGIN
namespace stl11
{
  using namespace boost_lite::bind::boost::system_error;
}
BOOST_OUTCOME_V1_NAMESPACE_END
#else
#include "../boost-lite/include/bind/stl11/std/system_error"
BOOST_OUTCOME_V1_NAMESPACE_BEGIN
namespace stl11
{
  using namespace boost_lite::bind::std::system_error;
}
BOOST_OUTCOME_V1_NAMESPACE_END
#endif

// For some odd reason, VS2015 really hates to do much inlining unless forced
#if defined(_MSC_VER) && !defined(__c2__)
//# pragma inline_depth(255)
//# pragma inline_recursion(on)
#define BOOST_OUTCOME_CONSTEXPR BOOSTLITE_FORCEINLINE
#define BOOST_OUTCOME_CONVINCE_MSVC BOOSTLITE_FORCEINLINE
#elif defined(__c2__) || defined(__clang__) || defined(__GNUC__)
// On clang and GCC we now require C++ 14 constexpr
#define BOOST_OUTCOME_CONSTEXPR constexpr
#define BOOST_OUTCOME_CONVINCE_MSVC
#else
#define BOOST_OUTCOME_CONSTEXPR BOOSTLITE_CONSTEXPR
#define BOOST_OUTCOME_CONVINCE_MSVC
#endif

#include <cassert>  // for asserting :)
#include <ostream>  // for printing

#ifndef BOOST_OUTCOME_THROW
#ifdef __cpp_exceptions
#define BOOST_OUTCOME_THROW(expr) throw expr
#else
#include <stdio.h>
#ifdef _WIN32
#include "../boost-lite/include/execinfo_win64.h"
#else
#include <execinfo.h>
#endif
BOOST_OUTCOME_V1_NAMESPACE_BEGIN
namespace detail
{
  BOOSTLITE_NORETURN inline void do_fatal_exit(const char *expr)
  {
    void *bt[16];
    size_t btlen = backtrace(bt, sizeof(bt) / sizeof(bt[0]));
    fprintf(stderr, "FATAL: Boost.Outcome throws exception %s with exceptions disabled\n", expr);
    char **bts = backtrace_symbols(bt, btlen);
    if(bts)
    {
      for(size_t n = 0; n < btlen; n++)
        fprintf(stderr, "  %s\n", bts[n]);
      free(bts);
    }
    std::terminate();
  }
}
BOOST_OUTCOME_V1_NAMESPACE_END
//! Redefine to have something else occur when Outcome throws an exception
#define BOOST_OUTCOME_THROW(expr) BOOST_OUTCOME_V1_NAMESPACE::detail::do_fatal_exit(#expr)
#endif
#endif

#ifndef BOOST_OUTCOME_THROW_DESERIALISATION_FAILURE
//! Predefine to have something else occur when Outcome throws an exception due to a deserialisation failure
#define BOOST_OUTCOME_THROW_DESERIALISATION_FAILURE(m, expr) BOOST_OUTCOME_THROW(expr)
#endif

#ifndef BOOST_OUTCOME_THROW_MONAD_ERROR
//! Predefine to have something else occur when Outcome throws a monad_error due to being asked to do something not possible
#define BOOST_OUTCOME_THROW_MONAD_ERROR(ec, expr) BOOST_OUTCOME_THROW(expr)
#endif

#ifndef BOOST_OUTCOME_THROW_SYSTEM_ERROR
//! Predefine to have something else occur when Outcome throws a system_error with an error_code from the monad
#define BOOST_OUTCOME_THROW_SYSTEM_ERROR(ec, expr) BOOST_OUTCOME_THROW(expr)
#endif

#ifndef BOOST_OUTCOME_RETHROW_EXCEPTION
#ifdef __cpp_exceptions
#define BOOST_OUTCOME_RETHROW_EXCEPTION(ex) std::rethrow_exception(ex)
#else
//! Predefine to have something else occur when Outcome rethrows an exception_ptr from the monad
#define BOOST_OUTCOME_RETHROW_EXCEPTION(ex) BOOST_OUTCOME_THROW(std::rethrow_exception(ex))
#endif
#endif


#endif  // BOOST_OUTCOME_NEED_DEFINE
