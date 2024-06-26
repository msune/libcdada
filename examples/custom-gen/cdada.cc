/*****************************************************************************/
/*                      BEGIN libcdada AUTOGENERATED C++ file                */
/*****************************************************************************/
// File autogenerated from cmd: ['../../tools/cdada-gen', 'list:foo_t', 'map:bar_t', '-o', 'cdada.cc']
// Add your header includes for types {'bar_t', 'foo_t'} here

#include "foo.h"
#include "bar.h"

///////////////////////////////////////////////////////////////////////////////
///                       DO NOT MODIFY AFTER THIS LINE                     ///
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdint.h>
#include <cdada/list_custom_cc.h>
#include <cdada/map_custom_cc.h>
#include <cdada/queue_custom_cc.h>
#include <cdada/set_custom_cc.h>
#include <cdada/stack_custom_cc.h>

//C++ comparison operators for user stypes (memcmp)

inline bool operator<(const bar_t & a1, const bar_t & a2){
    return memcmp((const void*)&a1, (const void*)&a2,
                                        sizeof( bar_t )) < 0;
}
inline bool operator==(const bar_t & a1, const bar_t & a2){
    return memcmp((const void*)&a1, (const void*)&a2,
                                        sizeof( bar_t )) == 0;
}

inline bool operator<(const foo_t & a1, const foo_t & a2){
    return memcmp((const void*)&a1, (const void*)&a2,
                                        sizeof( foo_t )) < 0;
}
inline bool operator==(const foo_t & a1, const foo_t & a2){
    return memcmp((const void*)&a1, (const void*)&a2,
                                        sizeof( foo_t )) == 0;
}

//cdada wrappers

//BEGIN list for foo_t (std::list<foo_t>)


//Operator
void __cdada_list_autogen_create_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	s->list.custom = (void*)new std::list<foo_t>();
}
void __cdada_list_autogen_destroy_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	delete p;
}
void __cdada_list_autogen_clear_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	p->clear();
}
bool __cdada_list_autogen_empty_foo_t (const void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return p->empty();
}
uint32_t __cdada_list_autogen_size_foo_t (const void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return p->size();
}
int __cdada_list_autogen_insert_foo_t (void* m, const void* val,
						const uint32_t pos){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_insert_u<foo_t> (s, p, val, pos);
}
int __cdada_list_autogen_get_foo_t (const void* m, const uint32_t pos,
						void* val){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_get_u<foo_t> (s, p, pos, val);
}
int __cdada_list_autogen_first_last_foo_t (const void* m, bool first,
						void* key){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_first_last_u<foo_t> (s, p, first, key);
}
int __cdada_list_autogen_erase_foo_t (void* m, const uint32_t pos){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_erase_u<foo_t> (s, p, pos);
}
int __cdada_list_autogen_remove_foo_t (void* m, const void* val){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_remove_u<foo_t> (s, p, val);
}
int __cdada_list_autogen_push_foo_t (void* m, const void* val,
							bool front){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_push_u<foo_t> (s, p, val, front);
}
int __cdada_list_autogen_pop_foo_t (void* m, bool front){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_pop_u<foo_t> (s, p, front);
}
void __cdada_list_autogen_sort_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	p->sort();
}
void __cdada_list_autogen_reverse_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	p->reverse();
}
void __cdada_list_autogen_unique_foo_t (void* m){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	p->unique();
}
void __cdada_list_autogen_traverse_foo_t (const void* m,
						cdada_list_it f,
						void* opaque){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_traverse_u<foo_t> (s, p, f, opaque);
}
void __cdada_list_autogen_rtraverse_foo_t (const void* m,
						cdada_list_it f,
						void* opaque){
	__cdada_list_int_t* s = (__cdada_list_int_t*)m;
	std::list<foo_t>* p =
			(std::list<foo_t>*)s->list.custom;
	return cdada_list_rtraverse_u<foo_t> (s, p, f, opaque);
}
void __cdada_list_autogen_dump_foo_t (const void* m,
                                                std::stringstream& ss){
        __cdada_list_int_t* s = (__cdada_list_int_t*)m;
        std::list<foo_t>* p =
                        (std::list<foo_t>*)s->list.custom;
        return cdada_list_dump_u< foo_t > (s, p, ss);
}
__cdada_list_ops_t __cdada_list_autogen_foo_t = {
	__cdada_list_autogen_create_foo_t,
	__cdada_list_autogen_destroy_foo_t,
	__cdada_list_autogen_clear_foo_t,
	__cdada_list_autogen_empty_foo_t,
	__cdada_list_autogen_size_foo_t,
	__cdada_list_autogen_insert_foo_t,
	__cdada_list_autogen_get_foo_t,
	__cdada_list_autogen_first_last_foo_t,
	__cdada_list_autogen_erase_foo_t,
	__cdada_list_autogen_remove_foo_t,
	__cdada_list_autogen_push_foo_t,
	__cdada_list_autogen_pop_foo_t,
	__cdada_list_autogen_sort_foo_t,
	__cdada_list_autogen_reverse_foo_t,
	__cdada_list_autogen_unique_foo_t,
	__cdada_list_autogen_traverse_foo_t,
	__cdada_list_autogen_rtraverse_foo_t,
	__cdada_list_autogen_dump_foo_t,
};

//END list for foo_t (std::list<foo_t>)

//BEGIN map for bar_t (std::map<bar_t>)

void __cdada_map_autogen_create_bar_t (void* m){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	s->map.custom = (void*)new std::map<bar_t, void*>();
}
void __cdada_map_autogen_destroy_bar_t (void* m){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	delete p;
}
void __cdada_map_autogen_clear_bar_t (void* m){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	p->clear();
}
bool __cdada_map_autogen_empty_bar_t (const void* m){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return p->empty();
}
uint32_t __cdada_map_autogen_size_bar_t (const void* m){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return p->size();
}
int __cdada_map_autogen_insert_bar_t (void* m, const void* key,
						void* val,
						const bool replace,
						void** prev_val){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_insert_u<bar_t> (s, p, key, val, replace, prev_val);
}
int __cdada_map_autogen_erase_bar_t (void* m, const void* key){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_erase_u<bar_t> (s, p, key);
}
int __cdada_map_autogen_find_bar_t (const void* m, const void* key,
						void** val){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_find_u<bar_t> (s, p, key, val);
}
int __cdada_map_autogen_get_pos_bar_t (const void* m, const uint32_t pos,
                        void* key,
						void** val){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_get_pos_u<bar_t> (s, p, pos, key, val);
}
int __cdada_map_autogen_first_last_bar_t (const void* m, bool first,
						void* key,
						void** val){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_first_last_u<bar_t> (s, p, first, key, val);
}
void __cdada_map_autogen_traverse_bar_t (const void* m,
						cdada_map_it f,
						void* opaque){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_traverse_u<bar_t> (s, p, f, opaque);
}
void __cdada_map_autogen_rtraverse_bar_t (const void* m,
						cdada_map_it f,
						void* opaque){
	__cdada_map_int_t* s = (__cdada_map_int_t*)m;
	std::map<bar_t, void*>* p =
			(std::map<bar_t, void*>*)s->map.custom;
	return cdada_map_rtraverse_u<bar_t> (s, p, f, opaque);
}
void __cdada_map_autogen_dump_bar_t (const void* m,
                                                std::stringstream& ss){
        __cdada_map_int_t* s = (__cdada_map_int_t*)m;
        std::map<bar_t, void*>* p =
                        (std::map<bar_t, void*>*)s->map.custom;
        return cdada_map_dump_u< bar_t > (s, p, ss);
}
__cdada_map_ops_t __cdada_map_autogen_bar_t = {
	__cdada_map_autogen_create_bar_t,
	__cdada_map_autogen_destroy_bar_t,
	__cdada_map_autogen_clear_bar_t,
	__cdada_map_autogen_empty_bar_t,
	__cdada_map_autogen_size_bar_t,
	__cdada_map_autogen_insert_bar_t,
	__cdada_map_autogen_erase_bar_t,
	__cdada_map_autogen_find_bar_t,
	__cdada_map_autogen_get_pos_bar_t,
	__cdada_map_autogen_first_last_bar_t,
	__cdada_map_autogen_traverse_bar_t,
	__cdada_map_autogen_rtraverse_bar_t,
	__cdada_map_autogen_dump_bar_t,
};

//END map for bar_t (std::map<bar_t>)

/*****************************************************************************/
/*                       END libcdada AUTOGENERATED C++ file                 */
/*****************************************************************************/
