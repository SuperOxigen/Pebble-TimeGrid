COMPILER = pebble
PHONE = 10.137.134.96
SOURCE = src
HDRTYPE = h
SRCTYPE = c
BINARY = build
CFLAGS =

all: $(BINARY)

force:
	$(COMPILER) build $(CFLAGS)

$(BINARY): $(SOURCE)/*.$(SRCTYPE) $(SOURCE)/*.$(HDRTYPE)
	$(MAKE) force

clean:
	rm -r $(BINARY)/*

install: $(BINARY)
	$(COMPILER) install --phone $(PHONE)

logs:
	$(COMPILER) logs --phone $(PHONE) 
