/* None */
#include "embedded.h"

#ifdef __FreeBSD__
#include <floatingpoint.h>
#endif
#if PY_MAJOR_VERSION < 3
int main(int argc, char** argv) {
#elif defined(_WIN32) || defined(WIN32) || defined(MS_WINDOWS)
int wmain(int argc, wchar_t **argv) {
#else
static int __Pyx_main(int argc, wchar_t **argv) {
#endif
    /* 754 requires that FP exceptions run in "no stop" mode by default,
     * and until C vendors implement C99's ways to control FP exceptions,
     * Python requires non-stop mode.  Alas, some platforms enable FP
     * exceptions by default.  Here we disable them.
     */
#ifdef __FreeBSD__
    fp_except_t m;
    m = fpgetmask();
    fpsetmask(m & ~FP_X_OFL);
#endif
    if (argc && argv)
        Py_SetProgramName(argv[0]);
    #if PY_MAJOR_VERSION < 3
    if (PyImport_AppendInittab("embedded", initembedded) < 0) return 1;
    #else
    if (PyImport_AppendInittab("embedded", PyInit_embedded) < 0) return 1;
    #endif
    Py_Initialize();
    if (argc && argv)
        PySys_SetArgv(argc, argv);
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

    say_hello_from_python();

#if PY_VERSION_HEX < 0x03060000
    Py_Finalize();
#else
    if (Py_FinalizeEx() < 0)
        return 2;
#endif
    return 0;
}