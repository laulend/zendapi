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
// Created by softboy on 2017/08/01.

#ifndef ZAPI_LANG_CLASS_H
#define ZAPI_LANG_CLASS_H

#include "zapi/vm/AbstractClass.h"
#include "zapi/vm/ClassMagicMethodInvoker.h"

namespace zapi
{
namespace lang
{

using zapi::vm::AbstractClass;
using zapi::vm::ClassMagicMethodInvoker;

class Constant;

template <typename T>
class ZAPI_DECL_EXPORT Class : public AbstractClass
{
public:
   Class(const char *name, ClassType classType = ClassType::Regular);
   Class(const Class<T> &other);
   Class(Class<T> &&other) ZAPI_DECL_NOEXCEPT;
   virtual ~Class();
   Class<T> &operator=(const Class<T> &other);
   Class<T> &operator=(Class<T> &&other);
public:
   Class<T> &registerProperty(const char *name, std::nullptr_t value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, int16_t value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, int32_t value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, int64_t value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, char value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, const char *value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, const std::string &value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, bool value, Modifier flags = Modifier::Public);
   Class<T> &registerProperty(const char *name, double value, Modifier flags = Modifier::Public);
   
   Class<T> &registerConstant(const char *name, std::nullptr_t value);
   Class<T> &registerConstant(const char *name, int16_t value);
   Class<T> &registerConstant(const char *name, int32_t value);
   Class<T> &registerConstant(const char *name, int64_t value);
   Class<T> &registerConstant(const char *name, char value);
   Class<T> &registerConstant(const char *name, const char *value);
   Class<T> &registerConstant(const char *name, const std::string &value);
   Class<T> &registerConstant(const char *name, bool value);
   Class<T> &registerConstant(const char *name, double value);
   Class<T> &registerConstant(const Constant &constant);
   
private:
   virtual StdClass *construct() const override;
   virtual StdClass *clone() const override;
   virtual void callDestruct(StdClass *nativeObject) const override;
   template <typename X = T>
   typename std::enable_if<std::is_default_constructible<X>::value, StdClass *>::type
   static doConstructObject();
   
   template <typename X = T>
   typename std::enable_if<!std::is_default_constructible<X>::value, StdClass *>::type
   static doConstructObject();
   
private:
   std::unique_ptr<ClassMagicMethodInvoker<T>> m_magicInvoker;
};

template <typename T>
Class<T>::Class(const char *name, ClassType classType)
   : AbstractClass(name, classType)
{}

template <typename T>
Class<T>::Class(const Class<T> &other)
   : AbstractClass(other)
{}

template <typename T>
Class<T>::Class(Class<T> &&other) ZAPI_DECL_NOEXCEPT
   : AbstractClass(std::move(other))
{}

template <typename T>
StdClass *Class<T>::construct() const
{
   return doConstructObject<T>();
}

template <typename T>
template <typename X>
typename std::enable_if<std::is_default_constructible<X>::value, StdClass *>::type
Class<T>::doConstructObject()
{
   return new X();
}

template <typename T>
template <typename X>
typename std::enable_if<!std::is_default_constructible<X>::value, StdClass *>::type
Class<T>::doConstructObject()
{
   return nullptr;
}
template <typename T>
void Class<T>::callDestruct(StdClass *nativeObject) const
{
   T *object = dynamic_cast<T *>(nativeObject);
   return object->__destruct();
}

template <typename T>
StdClass *Class<T>::clone() const
{
   return nullptr;
}

template <typename T>
Class<T>::~Class()
{}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, std::nullptr_t value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}
template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, int16_t value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, int32_t value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, int64_t value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, char value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, const char *value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, const std::string &value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, bool value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerProperty(const char *name, double value, Modifier flags)
{
   AbstractClass::registerProperty(name, value, flags);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, std::nullptr_t value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, int16_t value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, int32_t value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, int64_t value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, char value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, const char *value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, const std::string &value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, bool value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const char *name, double value)
{
   AbstractClass::registerProperty(name, value, Modifier::Const);
   return *this;
}

template <typename T>
Class<T> &Class<T>::registerConstant(const Constant &constant)
{
   AbstractClass::registerConstant(constant);
   return *this;
}

} // lang
} // zapi

#endif //ZAPI_LANG_CLASS_H
