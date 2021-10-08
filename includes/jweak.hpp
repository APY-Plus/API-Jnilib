#ifndef __JWEAK_H__
#define __JWEAK_H__

#include "jobject.hpp"

#define jweak_Val(x) ((jweak)jobject_Val(x))
#define jweak_Check(x) PyType_IsSubtype(Py_TYPE(x), &jweak_Type)
#define jweak_CheckExact(x) (Py_TYPE(x) == &jweak_Type)

struct jweakObject : jobjectObject {};

extern PyTypeObject jweak_Type;

jweakObject* jweak_FromValue(jweak);

#endif /* __JWEAK_H__ */