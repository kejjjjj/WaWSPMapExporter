#include "dvar.hpp"
#include "utils/engine.hpp"

dvar_s* Dvar_FindMalleableVar(const char* name)
{
    return ((dvar_s* (__cdecl*)(const char* name))0x5EDE30)(name);
}
dvar_s* Dvar_RegisterNew(const char* name, dvar_type type, int flags, const char* description, dvar_value defaultValue, dvar_limits domain)
{
    dvar_s* dvar = Dvar_FindMalleableVar(name);

    if (dvar) {
        return Dvar_Reregister(dvar, name, type, flags, description, defaultValue, domain);
    }

    return ((dvar_s * (*)(const char*, dvar_type, int, const char*, dvar_value, dvar_limits))0x5EEB50)(name, type, flags, description, defaultValue, domain);
}
dvar_s* Dvar_Reregister(dvar_s* dvar, const char* name, dvar_type type, int flags, const char* description, dvar_value defaultValue, dvar_limits domain)
{
    return ((dvar_s * (*)(dvar_s*, const char*, dvar_type, int, const char*, dvar_value, dvar_limits))0x5EEA20)(dvar, name, type, flags, description, defaultValue, domain);
}