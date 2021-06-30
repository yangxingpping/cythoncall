/* None */
#include "h.h"

#include "embedded.h"


#if PY_MAJOR_VERSION < 3
int main(int argc, char** argv) 
#else
int main(int argc, wchar_t** argv) 
#endif
{
    
    Person p;
    p.name = "alqaz";
    p.age = 12;

    if (argc && argv)
        Py_SetProgramName(argv[0]);
    #if PY_MAJOR_VERSION < 3
    if (PyImport_AppendInittab("embedded", initembedded) < 0) return 1;
    #else
    if (PyImport_AppendInittab("embedded", PyInit_embedded) < 0) return 1;
    #endif
    Py_Initialize();
  
    {
      PyObject* m = NULL;
      m = PyImport_ImportModule("embedded");
      if (!m && PyErr_Occurred()) {
          PyErr_Print();
          #if PY_MAJOR_VERSION < 3
          if (Py_FlushLine()) PyErr_Clear();
          #endif
          return 1;
      }
      Py_XDECREF(m);
    }
    printf("%d\n", p.age);
    say_hello_from_python(&p);
    printf("%d\n", p.age);

    Movice mov[10];
    memset(mov, 0, sizeof(mov));

    parse_xml_data("movies.xml", mov, 10);

#if PY_VERSION_HEX < 0x03060000
    Py_Finalize();
#else
    if (Py_FinalizeEx() < 0)
        return 2;
#endif
    return 0;
}