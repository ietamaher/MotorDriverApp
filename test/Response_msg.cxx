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
 * @file Response_msg.cpp
 * This source file contains the implementation of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "Response_msg.h"

#include <fastcdr/Cdr.h>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>




Response_msg::Response_msg()
{
}

Response_msg::~Response_msg()
{
}

Response_msg::Response_msg(
        const Response_msg& x)
{
    m_data = x.m_data;
    m_slave_id = x.m_slave_id;
    m_func_code = x.m_func_code;
}

Response_msg::Response_msg(
        Response_msg&& x) noexcept
{
    m_data = std::move(x.m_data);
    m_slave_id = x.m_slave_id;
    m_func_code = x.m_func_code;
}

Response_msg& Response_msg::operator =(
        const Response_msg& x)
{

    m_data = x.m_data;
    m_slave_id = x.m_slave_id;
    m_func_code = x.m_func_code;
    return *this;
}

Response_msg& Response_msg::operator =(
        Response_msg&& x) noexcept
{

    m_data = std::move(x.m_data);
    m_slave_id = x.m_slave_id;
    m_func_code = x.m_func_code;
    return *this;
}

bool Response_msg::operator ==(
        const Response_msg& x) const
{
    return (m_data == x.m_data &&
           m_slave_id == x.m_slave_id &&
           m_func_code == x.m_func_code);
}

bool Response_msg::operator !=(
        const Response_msg& x) const
{
    return !(*this == x);
}

/*!
 * @brief This function copies the value in member data
 * @param _data New value to be copied in member data
 */
void Response_msg::data(
        const std::array<uint32_t, 64>& _data)
{
    m_data = _data;
}

/*!
 * @brief This function moves the value in member data
 * @param _data New value to be moved in member data
 */
void Response_msg::data(
        std::array<uint32_t, 64>&& _data)
{
    m_data = std::move(_data);
}

/*!
 * @brief This function returns a constant reference to member data
 * @return Constant reference to member data
 */
const std::array<uint32_t, 64>& Response_msg::data() const
{
    return m_data;
}

/*!
 * @brief This function returns a reference to member data
 * @return Reference to member data
 */
std::array<uint32_t, 64>& Response_msg::data()
{
    return m_data;
}


/*!
 * @brief This function sets a value in member slave_id
 * @param _slave_id New value for member slave_id
 */
void Response_msg::slave_id(
        uint32_t _slave_id)
{
    m_slave_id = _slave_id;
}

/*!
 * @brief This function returns the value of member slave_id
 * @return Value of member slave_id
 */
uint32_t Response_msg::slave_id() const
{
    return m_slave_id;
}

/*!
 * @brief This function returns a reference to member slave_id
 * @return Reference to member slave_id
 */
uint32_t& Response_msg::slave_id()
{
    return m_slave_id;
}


/*!
 * @brief This function sets a value in member func_code
 * @param _func_code New value for member func_code
 */
void Response_msg::func_code(
        uint32_t _func_code)
{
    m_func_code = _func_code;
}

/*!
 * @brief This function returns the value of member func_code
 * @return Value of member func_code
 */
uint32_t Response_msg::func_code() const
{
    return m_func_code;
}

/*!
 * @brief This function returns a reference to member func_code
 * @return Reference to member func_code
 */
uint32_t& Response_msg::func_code()
{
    return m_func_code;
}


// Include auxiliary functions like for serializing/deserializing.
#include "Response_msgCdrAux.ipp"

