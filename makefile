#Windows 7:
#RM=del /y

#Windows 8.1, 10:
#RM=del /S

OUTDIR=out
OUT=$(addprefix $(OUTDIR)/,Cardbase)

all: $(OUTDIR)
	$(MAKE) -C src

debug: export CXXFLAGS+=-g
debug: clean all

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
ifeq ($(OS),Windows_NT)
	del /S *.o *.a *.exe
else ifeq ($(shell uname), Linux)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	rm -f -v $(OUT)
endif

rebuild: clean all
