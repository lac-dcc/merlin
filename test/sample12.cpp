void foo(char *buf, unsigned fd) {
	unsigned i, j;
	for (; fd; fd/=10) buf[--i] = '0' + fd%10;
}