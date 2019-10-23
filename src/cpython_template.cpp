#include <Python.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
#include <string>
#include <assert.h>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif


void extend_repeats(char *dna, std::vector<int>  (&allrepeats)[HASH_LEN], repeat &R, vector<repeat> &rep)
{
	int i;
}

static PyObject* get_repeats (PyObject* self, PyObject* args, PyObject *kwargs)
{
	char *somestring;
	int i,j;
        //var is not used, its just a placeholder in case we add an extra feature
	int var = 1;

	const Py_ssize_t tuple_length = 4;
	PyObject *repeat_list = PyList_New(0);
	
	static char *kwlist[] = {(char *)"dna", (char *)"gap", (char *)"var", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|ii", kwlist, &dna, &gap, &var)) 
	{
		return NULL;
	}
		extend_gapped_repeat(rep, gap+1);
	}
	// create the return list of tuples that will hold the pairs of repeats
	j = (int)rep.size();
	for(i=0;i<j;i++){
		if(rep[i].visited==0 && rep[i].len>= REPEAT_LEN){
			PyObject *the_tuple = PyTuple_New(tuple_length);
			PyTuple_SET_ITEM(the_tuple, 0, PyLong_FromLong(rep[i].fst));
			PyTuple_SET_ITEM(the_tuple, 1, PyLong_FromLong(rep[i].fst+rep[i].len-1));
			if(rep[i].sec>-1){
				PyTuple_SET_ITEM(the_tuple, 2, PyLong_FromLong(rep[i].sec));
				PyTuple_SET_ITEM(the_tuple, 3, PyLong_FromLong(rep[i].sec+rep[i].seclen-1));
			}
			else{
				PyTuple_SET_ITEM(the_tuple, 2, PyLong_FromLong(rep[i].sec*(-1)));
				PyTuple_SET_ITEM(the_tuple, 3, PyLong_FromLong((rep[i].sec+rep[i].seclen-1)*(-1)));
			}
			PyList_Append(repeat_list, the_tuple);
		}
	}

	return repeat_list;
}

// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
static PyMethodDef repeatfinder_methods[] = {
	{ "get_repeats", (PyCFunction) get_repeats, METH_VARARGS | METH_KEYWORDS, "Finds the repeats in a sequence" },
	{ NULL, NULL, 0, NULL }
};
#ifdef PY3K
// module definition structure for python3
static struct PyModuleDef RepeatFinder = {
	 PyModuleDef_HEAD_INIT,
	"RepeatFinder",
	"mod doc",
	-1,
	repeatfinder_methods
};
// module initializer for python3
PyMODINIT_FUNC PyInit_repeatfinder(void)
{
	return PyModule_Create(&RepeatFinder);
}
#else
// module initializer for python2
PyMODINIT_FUNC initrepeatfinder() {
	Py_InitModule3("RepeatFinder", repeatfinder_methods, "mod doc");
}
#endif

int
main(int argc, char *argv[])
{
	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL) {
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}

	/* Add a built-in module, before Py_Initialize */
	PyImport_AppendInittab("repeatfinder", PyInit_repeatfinder);

	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(program);

	/* Initialize the Python interpreter.  Required. */
	Py_Initialize();

	/* Optionally import the module; alternatively,
           import can be deferred until the embedded script
           imports it. */
	PyImport_ImportModule("repeatfinder");

	PyMem_RawFree(program);
	return 0;
}
