# embedded.pyx

# The following two lines are for test purposed only, please ignore them.
# distutils: sources = embedded_main.c
# tag: py3only

# reference url https://cython.readthedocs.io/en/latest/src/userguide/external_C_code.html


TEXT_TO_SAY = 'Hello from Python!'

cdef extern from "h.h":
    ctypedef struct Person:
        char* name;
        int age;
    cdef struct Source:
        char* sourcename;
        int score;
    
    cdef struct foo1:
        pass
    # ctypedef foo1 Foo #optional
    #ctypedef struct Foo1:
      #  pass;

    cdef struct Foo2:
        pass

cdef public int say_hello_from_python((Person*) p) except -1:
    print(TEXT_TO_SAY)
    p.age += 1;
    return 0