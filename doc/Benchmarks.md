# Benchmarks

This section compares the performance of `libcdada` to native `libstdc++`
code, to measure the overhead it adds. The benchmarking code is here:

* [benchmark.cc](../test/benchmark.cc)

Please note:

* The benchmarking is not exhaustive, but just wants to highlight tha the
  the library is roughly equivalent to the underlying `libstdc++`, and that
  for aligned types or custom `libcdada` containers this overhead is negligible
* If you have _hard_ performance requirements to meet, consider writing your
  own data structures.

#### Conditions

* Tested in Linux
* Standard Debian10 `libstdc++` package
* `libcdada` configured with `../configure` (`-O3`)
* All lcores have been tuned to, to avoid CPU scaling during the test

```
~/ sudo cpufreq-set -c 0 -g performance
#...
~/ sudo cpufreq-set -c 7 -g performance
```

* Intel(R) Core(TM) i7-8565U CPU @ 1.80GHz/4.6GHz
* 16GB DDR4 2667 MHz

## Results

The results of a random execution of `./benchmark`:

```d

====================================================================
Type: uint32_t
====================================================================

SET                                insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ set<uint32_t>                  752                  698
C cdada_set(uint32_t)              746                  743
C cdada_set_custom(uint32_t)       758                  744


MAP                                insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ map<uint32_t, void*>           830                  722
C cdada_map(uint32_t)              809                  1009
C cdada_map_custom(uint32_t)       818                  1017


LIST                               insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ list<uint32_t>                 20                   17
C cdada_list(uint32_t)             28                   20
C cdada_list_custom(uint32_t)      27                   20


====================================================================
Type: test_u552_t (69 bytes)
(Note: cdada non-custom containers will pad to 128bytes)
====================================================================

SET                                insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ set<test_u552_t>               1410                 1082
C cdada_set(test_u552_t)           1623                 1311
C cdada_set_custom(test_u552_t)    1433                 1098


MAP                                insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ map<test_u552_t, void*>        1593                 1148
C cdada_map(test_u552_t)           1646                 1768
C cdada_map_custom(test_u552_t)    1605                 1631


LIST                               insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ list<test_u552_t>              42                   22
C cdada_list(test_u552_t)          67                   40
C cdada_list_custom(test_u552_t)   44                   25


====================================================================
Type: test_u3552_t (444 bytes)
(Note: cdada non-custom containers don't support >256 bytes)
====================================================================

SET                                insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ set<test_u3552_t>              1991                 1465
C cdada_set_custom(test_u3552_t)   2005                 1479


MAP                                insert(ticks)        erase(ticks)
-------------------------------------------------------------------
C++ map<test_u3552_t, void*>       1993                 1472
C cdada_map_custom(test_u3552_t)   1988                 2021


LIST                               insert(ticks)        erase(ticks)
--------------------------------------------------------------------
C++ list<test_u3552_t>             178                  76
C cdada_list_custom(test_u3552_t)  175                  79

```
