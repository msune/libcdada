## Changelog

```
Legend:

- [+] New/improved feature
- [B] Bug fixed
- [K] Known issue
- [O] Other
```

### v0.3.5 (20th April 2021)

- [+] Improved public API documentation
- [+] build: add --without-tests --without-examples build options
- [B] Fix `E_EMPTY` return codes set/map/list/stack/queue
- [B] Fix `make check` when valgrind is not installed

### v0.3.4 (14th January 2021)

- [B] Fix several build errors on old GCC versions (GCC4.2)
- [O] Replace travis-ci.com/org with Github Actions

### v0.3.3 (27th November 2020)

- [B] Fix several issues with documentation

### v0.3.2 (3d November 2020)

- [+] Add version and build MACROs and API calls
- [B] Fix build when Python3 is not present by disabling gen tests

### v0.3.1 (22th July 2020)

- [B] Fix benchmark compilation error due to rdtsc for non x86/amd64 archs (e.g. PowerPC)

### v0.3.0 (17th July 2020)

- [+] Support for `cdada_queue`, FIFO queue
- [+] Add support for get/set `max_capacity()` for `cdada_queue` and `cdada_stack`

### v0.2.2 (4th July 2020)

- [B] cdada.h: add missing cdada container includes. Added coverage.

### v0.2.1 (7th June 2020)

- [B] cdada-gen: fix incorrect parsing of container list input
- [B] cdada-gen: fix missing implementation for dump() leading to SEGFAULT
- [O] cdada-gen: added full coverage for cdada-gen generated code

### v0.2.0 (6th June 2020)

- [+] Support for `cdada_bbitmap`, big bitmaps
- [+] Support for `cdada_str`, strings
- [+] Support for `cdada_stack`, LIFO queue
- [+] Add `dump()` and `print()` support for all containers

### v0.1.0 (23d May 2020)

- [+] Support for `cdada_list`, `cdada_map`, `cdada_set`
