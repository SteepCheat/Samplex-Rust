#pragma once
#include "math.hpp"
#include "../Encrypt/lazy_importer.hpp"
namespace il2cpp
{
	namespace methods
	{
		using il2cpp_domain_get = uintptr_t(*)();
		static auto domain_get = LI_FIND_DEF(il2cpp_domain_get);

		using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

		using il2cpp_method_get_param_count = int (*)(uintptr_t);
		static auto method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

		using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);
		static auto assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

		using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);
		static auto domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

		using il2cpp_object_new = uintptr_t(*)(uintptr_t);
		static auto object_new = LI_FIND_DEF(il2cpp_object_new);

		using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);
		static auto class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

		using il2cpp_resolve_icall = uintptr_t(*)(const char*);
		static auto resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

		using il2cpp_class_get_field_from_name = uintptr_t(*)(uintptr_t, const char*);
		static auto class_get_field_from_name = LI_FIND_DEF(il2cpp_class_get_field_from_name);

		using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

		using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

		using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);
		static auto field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

		using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);
		static auto runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

		

		using  il2cpp_class_get_method_from_name = uintptr_t(*)(uintptr_t, const char*, int);
		static auto class_get_method_from_name = LI_FIND_DEF(il2cpp_class_get_method_from_name);
		
		using  il2cpp_type_get_object = uintptr_t(*)(uintptr_t);
		static auto type_get_object = LI_FIND_DEF(il2cpp_type_get_object);
		
		using  il2cpp_class_get_type = uintptr_t(*)(uintptr_t);
		static auto class_get_type = LI_FIND_DEF(il2cpp_class_get_type);
	}

	inline uintptr_t init_class(const char* name, const char* name_space)
	{
		uintptr_t domain = methods::domain_get();

		if (!domain)
		{
			return NULL;
		}

		uintptr_t nrofassemblies;
		uintptr_t* assemblies;
		assemblies = methods::domain_get_assemblies((void*)domain, &nrofassemblies);

		for (int i = 0; i < nrofassemblies; i++)
		{
			uintptr_t img = methods::assembly_get_image(assemblies[i]);

			uintptr_t kl = methods::class_from_name(img, name_space, name);
			if (!kl)
				continue;

			return kl;
		}

		return NULL;
	}

	inline bool m_strcmp(char* a, char* b) {
		if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
			return false;
		if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
			return false;

		if (!a || !b) return !a && !b;

		int ret = 0;
		unsigned char* p1 = (unsigned char*)a;
		unsigned char* p2 = (unsigned char*)b;
		while (!(ret = *p1 - *p2) && *p2)
			++p1, ++p2;

		return ret == 0;
	}
	inline uintptr_t typeObject(const char* name_space, const char* name) {
		auto klass = init_class(name, name_space);
		return methods::type_get_object(methods::class_get_type(klass));
	}

	inline uintptr_t method(const char* kl, const char* name, const char* name_space = (""), int argument_number = -1, char* arg_name = _(""), int selected_argument = -1)
	{
		uintptr_t iter = 0;
		uintptr_t f;
		auto klass = init_class(kl, name_space);

		while (f = methods::class_get_methods(klass, &iter)) {

			char* st = *reinterpret_cast<char**>(f + 0x10);

			if (m_strcmp(st, (char*)name)) {
				if (selected_argument >= 0 && arg_name) {
					uintptr_t args = M::read<uintptr_t>(f + 0x28);
					int method_count = methods::method_get_param_count(f);
					if (selected_argument > method_count || (argument_number >= 0 && method_count != argument_number)) continue;

					char* argname;
					if (method_count > 0) {
						argname = *reinterpret_cast<char**>(args + (selected_argument - 1) * 0x18);
					}
					else
						argname = (char*)_("-");

					if (!argname || !m_strcmp(argname, arg_name)) continue;
				}

				return f;
			}
		}
		return 0;
	}

	uintptr_t hook(void* our_func, const char* function_to_hook, const char* class_to_hook, const char* name_space = _(""), int argument_number = -1, char* argument_name = _("")) {
		auto il2cpp_method = method(class_to_hook, function_to_hook, name_space, argument_number, argument_name);

		*reinterpret_cast<void**>(il2cpp_method) = our_func;
		return M::read<uintptr_t>(il2cpp_method);
	}

	inline uintptr_t hookVFunc(const char* classname, const char* function_to_hook, void* our_func, int param_count = -1, const char* name_space = _(""))
	{
		auto method = il2cpp::method(classname, function_to_hook, name_space, param_count);
		if (!method)
		{
			return NULL;
		}
		uintptr_t search = *reinterpret_cast<uintptr_t*>(method);
		uintptr_t table = init_class(classname, name_space);

		if (search == (uintptr_t)our_func)
		{
			return (uintptr_t)our_func;
		}

		for (uintptr_t i = table; i <= table + 0x10000; i += 0x1) {
			uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);
			if (addr == search)
			{
				*reinterpret_cast<uintptr_t*>(i) = (uintptr_t)our_func;
				return addr;
			}
		}
		return NULL;
	}

	inline uintptr_t field(uintptr_t klass, const char* name)
	{
		return methods::class_get_field_from_name(klass, name);
	}

	inline uintptr_t value(const char* kl, const char* name, bool get_offset = true, const char* name_space = "")
	{
		uintptr_t klass = init_class(kl, name_space);

		if (!klass)
			return NULL;

		auto field = il2cpp::field(klass, name);
		if (get_offset)
		{
			uintptr_t out = 0;
			uintptr_t il2cpp_field;
			uintptr_t field_offset = NULL;

			while (il2cpp_field = methods::class_get_fields(klass, &out))
			{
				char* char_name = (char*)*reinterpret_cast<uintptr_t*>(il2cpp_field);
				if (!char_name)
					continue;

				uintptr_t offset = methods::field_get_offset(il2cpp_field);
				std::string field_name = std::string(char_name);
				if (name == field_name)
				{
					field_offset = offset;
					break;
				}
			}
			return field_offset;
		}

		uintptr_t static_value;
		methods::field_static_get_value(field, &static_value);
		if (static_value)
			return static_value;

		return NULL;
	}


}