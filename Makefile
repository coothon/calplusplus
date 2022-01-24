CC=g++
CFLAGS=-std=c++17 -g0 -Wall -Werror -Wextra -Wshadow -Wfloat-equal -Wunreachable-code -pedantic-errors -O3
LDFLAGS=
IFILE=$(CURDIR)/main.cxx $(CURDIR)/format.cxx $(CURDIR)/cal.cxx $(CURDIR)/ftime.cxx $(CURDIR)/sto.cxx
LDFILE=$(CURDIR)/main.o $(CURDIR)/format.o $(CURDIR)/cal.o $(CURDIR)/ftime.o $(CURDIR)/sto.o
OFILE=$(CURDIR)/cal++

program:
	@rm -f $(OFILE)
	$(CC) -c $(IFILE) $(CFLAGS)
	$(CC) -o $(OFILE) $(LDFILE) $(LDFLAGS)
	@rm -f $(LDFILE)
	@echo "Compilation successful"
	@clear
	@$(OFILE)