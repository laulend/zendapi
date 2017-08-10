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
// Created by softboy on 2017/08/08.

#ifndef ZAPI_DS_INTERNAL_STRING_VARIANT_PRIVATE_H
#define ZAPI_DS_INTERNAL_STRING_VARIANT_PRIVATE_H

#include "zapi/ds/Variant.h"
#include "php/Zend/zend_smart_str.h"

namespace zapi
{
namespace ds
{

class ZAPI_DECL_EXPORT StringVariant final: public Variant
{
public:
   using SizeType = size_t;
   using Reference = char &;
   using ConstReference = const char &;
public:
   StringVariant();
   StringVariant(const std::string &value);
   StringVariant(const char *value, size_t length);
   StringVariant(const char *value);
   StringVariant &operator=(char value);
   StringVariant &operator=(const std::string &value);
   StringVariant &operator=(const char *value);
   virtual bool toBool() const ZAPI_DECL_NOEXCEPT override;
   virtual std::string toString() const ZAPI_DECL_NOEXCEPT override;
   // access method
   Reference at(SizeType pos);
   ConstReference at(SizeType pos) const;
   const char *getCStr() const ZAPI_DECL_NOEXCEPT;
   SizeType getSize() const ZAPI_DECL_NOEXCEPT;
   SizeType getLength() const ZAPI_DECL_NOEXCEPT;
   SizeType getCapacity() const ZAPI_DECL_NOEXCEPT;
   virtual ~StringVariant() ZAPI_DECL_NOEXCEPT;
protected:
   zend_string *getZendStringPtr();
   constexpr size_t calculateNewStrSize(size_t length);
   void strStdRealloc(zend_string *&str, size_t length);
   void strPersistentRealloc(zend_string *&str, size_t length);
   size_t strAlloc(zend_string *&str, size_t length, bool persistent);
};

} // ds
} // zapi

#endif // ZAPI_DS_INTERNAL_STRING_VARIANT_PRIVATE_H