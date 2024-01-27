// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file Response_msg.i
 * This header file contains the SWIG interface of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

%module Response_msg

// SWIG helper modules
%include "stdint.i"
%include "std_array.i"
%include "std_map.i"
%include "std_string.i"
%include "std_vector.i"
%include "typemaps.i"

// Assignemt operators are ignored, as there is no such thing in Python.
// Trying to export them issues a warning
%ignore *::operator=;

// Macro declarations
// Any macro used on the Fast DDS header files will give an error if it is not redefined here
#define RTPS_DllAPI
#define eProsima_user_DllExport


%{
#include "Response_msg.h"

#include <fastdds/dds/core/LoanableSequence.hpp>
%}

%include <fastcdr/config.h>
#if FASTCDR_VERSION_MAJOR > 1
%import(module="fastdds") "fastcdr/xcdr/optional.hpp"
#endif
%import(module="fastdds") "fastdds/dds/core/LoanableCollection.hpp"
%import(module="fastdds") "fastdds/dds/core/LoanableTypedCollection.hpp"
%import(module="fastdds") "fastdds/dds/core/LoanableSequence.hpp"

%define %traits_penumn(Type...)
  %fragment(SWIG_Traits_frag(Type),"header",
        fragment="StdTraits") {
namespace swig {
  template <> struct traits< Type > {
    typedef value_category category;
    static const char* type_name() { return  #Type; }
  };
}
}
%enddef



////////////////////////////////////////////////////////
// Binding for class Response_msg
////////////////////////////////////////////////////////

// Ignore overloaded methods that have no application on Python
// Otherwise they will issue a warning
%ignore Response_msg::Response_msg(Response_msg&&);

// Overloaded getter methods shadow each other and are equivalent in python
// Avoid a warning ignoring all but one
%ignore Response_msg::data(std::array<uint32_t, 64>&&);


// Overloaded getter methods shadow each other and are equivalent in python
// Const accesors produced constant enums instead of arrays/dictionaries when used
// We ignore them to prevent this
%ignore Response_msg::data() const;
%template(uint32_t_64_array) std::array<uint32_t,64>;
%extend std::array<uint32_t, 64>
{
    const uint32_t* get_buffer() const
    {
        return self->data();
    }
}


%ignore Response_msg::slave_id(uint32_t&&);


// Overloaded getter methods shadow each other and are equivalent in python
// Const accesors produced constant enums instead of arrays/dictionaries when used
// We ignore them to prevent this
%ignore Response_msg::slave_id();
%rename("%s") Response_msg::slave_id() const;



%ignore Response_msg::func_code(uint32_t&&);


// Overloaded getter methods shadow each other and are equivalent in python
// Const accesors produced constant enums instead of arrays/dictionaries when used
// We ignore them to prevent this
%ignore Response_msg::func_code();
%rename("%s") Response_msg::func_code() const;



%template(_Response_msgSeq) eprosima::fastdds::dds::LoanableTypedCollection<Response_msg, std::false_type>;
%template(Response_msgSeq) eprosima::fastdds::dds::LoanableSequence<Response_msg, std::false_type>;
%extend eprosima::fastdds::dds::LoanableSequence<Response_msg, std::false_type>
{
    size_t __len__() const
    {
        return self->length();
    }

    const Response_msg& __getitem__(size_t i) const
    {
        return (*self)[i];
    }
}


// Include the class interfaces
%include "Response_msg.h"
// Include the corresponding TopicDataType
%include "Response_msgPubSubTypes.i"

