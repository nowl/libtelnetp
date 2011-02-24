lib_LTLIBRARIES = libtelnetp.la

libtelnetp_la_SOURCES = \
	telnetp.c \
	ansi_p_codes.c \
	utils.c

libtelnetp_la_CFLAGS = -I../include
libtelnetp_la_LDFLAGS = -lz

noinst_PROGRAMS = test
test_CFLAGS = -I../include
test_SOURCES = test.c
test_LDFLAGS = -L. -ltelnetp -lz