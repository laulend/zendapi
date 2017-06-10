// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by zzu_softboy on 05/06/2017.

#ifndef ZAPI_UTILS_STRING_H
#define ZAPI_UTILS_STRING_H

#include <string>

#include "zapi/Global.h"

namespace zapi
{
namespace ds{

class ZAPI_DECL_EXPORT String
{
private:
   /**
    * The string we are wrapping
    * @var    zend_string*
    */
   zend_string *m_string;
public:
   /**
    * Constructor
    *
    * @param  string  The string to wrap
    */
   String(zend_string *string)
         : m_string(string)
   {
      zend_string_addref(string);
   }

   /**
    * Constructor
    *
    * @param string The string to wrap
    */
   String(const std::string &string)
         : m_string(zend_string_init(string.data(), string.size(), 1))
   {}

   /**
    * Constructor
    *
    * @param  string  The string to wrap
    */
   String(const char *string)
         : m_string(zend_string_init(string, std::strlen(string), 1))
   {}

   /**
    * Constructor
    *
    * @param  string  The string to wrap
    * @param  size    Number of bytes in the string
    */
   String(const char *string, size_t size)
         : m_string(zend_string_init(string, size, 1))
   {}

   /**
    *  Constructor
    *
    *  @param  string  The string to wrap
    */
   template <size_t size>
   String(const char (&string)[size])
         : m_string(zend_string_init(string, size - 1, 1))
   {}

   /**
    * Move constructor
    *
    * @param other The string to move
    */
   String(const String &other)
         : m_string(other.m_string)
   {
      zend_string_addref(m_string);
   }

   /**
    * Move constructor
    *
    * @param  that    The string to move
    */
   String(String &&other)
         : m_string(other.m_string)
   {
      other.m_string = nullptr;
   }

   /**
    * Destructor
    */
   virtual ~String()
   {
      // release the reference, freeing the
      // string if we are the last referee
      if (m_string) {
         zend_string_release(m_string);
      }
   }

   /**
    * Retrieve the data for the string
    *
    * @return Pointer to the string data
    */
   char *getData()
   {
      return ZSTR_VAL(m_string);
   }

   /**
    * Retrieve the data for the string
    *
    * @return Pointer to the string data
    */
   const char *getData() const
   {
      return ZSTR_VAL(m_string);
   }

   /**
    * Retrieve number of characters in the string
    *
    * @return Number of characters, not including the terminating null
    */
   size_t getSize() const
   {
      return ZSTR_LEN(m_string);
   }

   /**
    * Retrieve the underlying string
    *
    * @return The zend string
    */
   operator zend_string * ()
   {
      return m_string;
   }

   /**
    * Retrieve the underlying string
    *
    * @return The zend string
    */
   zend_string *operator->()
   {
      return m_string;
   }
};

} // ds
} // zapi

#endif // ZAPI_UTILS_STRING_H