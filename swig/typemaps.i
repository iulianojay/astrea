
%typemap(out) long double {
    $result = PyFloat_FromDouble($1);
}
