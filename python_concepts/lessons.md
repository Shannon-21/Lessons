remenber for interview

- attributes in python clases can be taken from params or being assinged to nothing in their initializacion.
- we can use threading module with Lock() as a att of the class and the use `with self.lock`: over the code that will crud over shared memory on the class.
- threading.Thread() specify a funtion target and daemon bool to kill it when stop the program. we must start the daemon with start() over the att thread oject.
- the thread will run in paralell and we must conditionate inside the function the execution model (by time or event) to ensure deamon keep running not only for the initialization.
- expose the stop of daemons in the api with flags in the object, so the daemon funcion definition will return when flag is deactivated. join() method of a Thread object will wait until thread finish on stop.
- validate input and when to use raise exceptions or logging-errors-only on crud operations.
- reusable code of the class add them as private functions.
- cannot modify an itarable object during the iteration: the strategy is iterate and record the values to modify. then modify then in other loop apart when the principal was finished.
- items() is method of dicts to split each kv pairs on key and value. enumerate() is a function to split the idex from the value of the iterable.
- validate datatype conversions at least we are sure we have extracted the excat datatype we want.
- for unit teting impor unittest and create a Testclass with inherit from unittest.TestCase with the a setUp method, and then test methods wjich provide self.assert funtions.
- we can run debugging mode with pdb, putting breakpoint() functions above the code to debug and navigate with c, n, s the code and seeing their values and steps.
- set data type of arguments in funtion with syntax like (num: int) and the return value like def (...)-> int: