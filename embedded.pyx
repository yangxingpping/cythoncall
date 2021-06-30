# embedded.pyx

# The following two lines are for test purposed only, please ignore them.
# distutils: sources = embedded_main.c
# tag: py3only

# reference url https://cython.readthedocs.io/en/latest/src/userguide/external_C_code.html


import xml.sax
from xml.dom.minidom import parse
import xml.dom.minidom

TEXT_TO_SAY = 'Hello from Python!'

cdef extern from "h.h":
    ctypedef struct Person:
        char* name;
        int age;
    ctypedef struct Movice:
        char* title;
        char* type;
        int year;
        char* rating;
        int stars;
        char* desc;

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
    print(p.name);
    print(p.age);
    p.age += 1;
    return 0;

cdef public int parse_xml_data(char* filex , (Movice*)p, int allocSize):
    encoding = 'utf-8'
    filepath = str(filex, encoding);
    DOMTree = xml.dom.minidom.parse(filepath);
    collection = DOMTree.documentElement
    
    movies = collection.getElementsByTagName("movie")
    
    for movie in movies:
        if movie.hasAttribute("title"):
            type = movie.getElementsByTagName('type')[0]
            #print "Type: %s" % type.childNodes[0].data
            format = movie.getElementsByTagName('format')[0]
            #print "Format: %s" % format.childNodes[0].data
            rating = movie.getElementsByTagName('rating')[0]
            #print "Rating: %s" % rating.childNodes[0].data
            description = movie.getElementsByTagName('description')[0]
            #print "Description: %s" % description.childNodes[0].data
