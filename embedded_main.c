/* None */
#include "embedded.h"

char chname[] = "hello.world yy";

int main(int argc, char** argv) {
    /* 754 requires that FP exceptions run in "no stop" mode by default,
     * and until C vendors implement C99's ways to control FP exceptions,
     * Python requires non-stop mode.  Alas, some platforms enable FP
     * exceptions by default.  Here we disable them.
     */

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

    say_hello_from_python(chname);

#if PY_VERSION_HEX < 0x03060000
    Py_Finalize();
#else
    if (Py_FinalizeEx() < 0)
        return 2;
#endif
    return 0;
}